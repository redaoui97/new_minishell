/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:30:27 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/10 05:52:04 by rnabil           ###   ########.fr       */
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
	free (paths);
	return (NULL);
}


static void	wait_child()
{
	int	wait_return;

	wait_return = wait (NULL);
	while (wait_return > 0)
		wait_return = wait(NULL);
}

// static int	check_cmd(char **cmd)
// {
// 	if (get_path(cmd[0], find_path_env()) == NULL)
// 	{
// 		simple_error(ft_strjoin_adjusted(ft_strdup("Command not found: "), cmd[0]));
// 		return (0);
// 	}
// 	else
// 		return (1);
// }
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

void	execute_command(t_cmd *cmd)
{
	pid_t	pid;
	char	*path;
	char	**envp;

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

static void	set_pipes(t_cmd *cmd, int **pipes)
{
	
}

static void	close_files(t_cmd *cmd)
{
	//add error protection for close 
	if (cmd->infile != -1)
		close (cmd->infile);
	if (cmd->outfile != -1)
		close (cmd->outfile);
	//close pipes
}

void	execute(t_cmd *cmds, int pipes_count)
{
	int		i;
	t_list	*ptr;
	char	**envp;
	int		pipes[pipes_count][2];
	
	i = 0;
	while (i <= pipes_count)
	{
		set_pipes(&cmds[i], &pipes[i]);
		execute_command(&cmds[i]);
		close_files(&cmds[i]);
		wait_child();
		i++;
	}
}