/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:30:27 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/12 21:52:05 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



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
	free (envp);
}

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