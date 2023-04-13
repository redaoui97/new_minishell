/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:30:27 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/13 10:24:17 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



//needs to be changed to store last exit status and skip cmds after followed execution
static void	wait_child(int (*pids)[2], int size)
{
	// int	wait_return;

	// wait_return = wait (NULL);
	// while (wait_return > 0)
	// 	wait_return = wait(NULL);
	int i;

    i = 0;
    while (i < size)
    {
        waitpid(pids[i][0], &(pids[i][1]), 0);
        if (i == size - 1)
        {
            while (i)
            {
                kill(pids[i][0], SIGTERM);
                i--;
            }
            return;
        }
        i++;
    }
	
}

static int	check_cmd(t_cmd *cmd, int cmd_num)
{
	char *path;

	if (!cmd)
		return (EXIT_FAILURE);
	path = get_path(cmd->cmd_args[0], find_path_env());
	if (is_builtin(cmd))
	{
		exec_builtin(cmd, cmd_num);
		free (path);
		return (EXIT_FAILURE);
	}
	else if (!path)
	{
		simple_error(ft_strjoin_adjusted(ft_strdup("Command not found: "), cmd->cmd_args[0]));
		free (path);
		return (EXIT_FAILURE);
	}
	else
	{
		free (path);
		return (EXIT_SUCCESS);
	}
}

static int	execute_command(t_cmd *cmd, int cmd_num)
{
	pid_t	pid;
	char	*path;
	char	**envp;

	if (check_cmd(cmd, cmd_num) == EXIT_FAILURE)
		return (-1);
	pid = fork();
	if (pid == -1)
		return ((void)simple_error("failed to create a child process!"), -1);
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
	return (pid);
}

static void	close_pipes(int (*pipes)[2], int pipes_count)
{
	int	i;

	i = 0;
	while (i < pipes_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	execute(t_cmd *cmds, int pipes_count)
{
	int		i;
	int		pipes[pipes_count][2];
	int		pid_status[pipes_count + 1][2];
	
	i = 0;
	(void)pid_status;
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
		pid_status[i][0] = execute_command(&cmds[i], pipes_count + 1);
		close_files(&cmds[i]);
		i++;
	}
	wait_child(pid_status, pipes_count + 1);
	close_pipes(pipes, pipes_count);
}