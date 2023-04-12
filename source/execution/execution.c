/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:30:27 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/11 23:12:43 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*find_path_env()
{
	t_list	*ptr;

	ptr = g_gen.env;
	while (ptr)
	{
		if (ft_strncmp("PATH", (char *)ptr->content, 4) == 0)
			return ((char *)ptr->content + 5);
		ptr = ptr->next;
	}
	return (NULL);
}

/*gets the right path from a $PATH env*/
char	*get_path(char *cmd, char *env_path)
{
	char	**paths;
	char	*path;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	paths = ft_split_adjusted(env_path, ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin_adjusted(paths[i], "/");
		path = ft_strjoin_adjusted(path, cmd);
		if (access(path, X_OK) == 0)
		{
			while (paths[++i])
				free (paths[i]);
			free (paths);
			return (path);
		}
		free (path);
		i++;
	}
	return (NULL);
}

//needs to be changed to store last exit status and skip cmds after followed execution
static void	wait_child()
{
	int	wait_return;

	wait_return = wait (NULL);
	while (wait_return > 0)
		wait_return = wait(NULL);
}

static int	check_cmd(t_cmd *cmd, int cmd_num)
{
	if (!cmd)
		return (EXIT_FAILURE);
	if (is_builtin(cmd))
	{
		exec_builtin(cmd, cmd_num);
		return (EXIT_FAILURE);
	}
	else if (get_path(cmd->cmd_args[0], find_path_env()) == NULL)
	{
		simple_error(ft_strjoin_adjusted(ft_strdup("Command not found: "), cmd->cmd_args[0]));
		return (EXIT_FAILURE);
	}
	else
	{
		return (EXIT_SUCCESS);
	}
}

static int	get_envp_size()
{
	int	size;

	size = 0;
	t_list	*ptr;

	ptr = g_gen.env;
	while (ptr)
	{
		size++;
		ptr = ptr->next;
	}
	return (size);
}

static char	**make_envp()
{
	char	**envp;
	t_list	*ptr;
	int		i;

	ptr = g_gen.env;
	i = 0;
	envp = (char **)malloc (sizeof(char *) * (get_envp_size() + 1));
	while (ptr)
	{
		envp[i++] = (char *)ptr->content;
		ptr = ptr->next;
	}
	envp[i] = NULL;
	return (envp);
}	

void	execute_command(t_cmd *cmd, int cmd_num)
{
	pid_t	pid;
	char	*path;
	char	**envp;

	if (check_cmd(cmd, cmd_num) == EXIT_FAILURE)
		return ;
	pid = fork();
	if (pid == -1)
		return ((void)simple_error("failed to create a child process!"));
	//change this; make_envp adds even those env vars that weren't exported; only use on export
	envp = make_envp();
	if (pid == 0)
	{		
		path = get_path(cmd->cmd_args[0], find_path_env());
		if (cmd->infile != -1)
		{
			dup2(cmd->infile, 0);
			close (cmd->infile);
		}
		if (cmd->outfile != -1)
		{
			dup2(cmd->outfile, 1);
			close (cmd->outfile);
		}
		execve(path, cmd->cmd_args, envp);
	}
}

static void	set_pipes(t_cmd *cmd, int (*pipe_in)[2], int (*pipe_out)[2])
{
	if (cmd->infile == -1 && *pipe_in)
		cmd->infile = (*pipe_in)[0];
	if (cmd->outfile == -1 && *pipe_out)
		cmd->outfile = (*pipe_out)[1];
}

static void	close_files(t_cmd *cmd)
{
	if (cmd->infile != -1)
		close (cmd->infile);
	if (cmd->outfile != -1)
		close (cmd->outfile);
}

int open_pipes(int (*pipes)[2], int pipes_count) 
{
	int	i;
	int	j;

	i = 0;
	while (i < pipes_count) 
	{
		j = 0;
		if (pipe(pipes[i]) == -1) 
		{
			simple_error("Failed to create pipe");
            while (j < i) 
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
				j++;
			}
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

// static void	close_pipes(int (*pipes)[2], int pipes_count)
// {
// 	int	i;

// 	i = 0;
// 	while (i < pipes_count)
// 	{
// 		close(pipes[i][0]);
// 		close(pipes[i][1]);
// 		i++;
// 	}
// }

void	execute(t_cmd *cmds, int pipes_count)
{
	int		i;
	int		pipes[pipes_count][2];
	
	i = 0;
	if (open_pipes(pipes, pipes_count) == EXIT_FAILURE)
		return ;
	while (i <= pipes_count)
	{
		if (pipes_count)
		{
			if (i == 0)
				set_pipes(&cmds[i], NULL, &pipes[i]);
			else if (i == pipes_count)
				set_pipes(&cmds[i], &pipes[i - 1], NULL);
			else
				set_pipes(&cmds[i], &pipes[i - 1], &pipes[i]);
		}
		execute_command(&cmds[i], pipes_count + 1);
		wait_child();
		close_files(&cmds[i]);
		i++;
	}
	//some pipes are closed some are not 
	//close_pipes(pipes, pipes_count);
}