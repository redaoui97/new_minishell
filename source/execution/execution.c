/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:30:27 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/14 01:56:49 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//needs to be changed to store last exit status and skip cmds after followed execution
static void	wait_child(int pids[2])
{
	waitpid(pids[0],&(pids[1]), 0);
	while (waitpid(-1, 0, 0) != -1)
		;
	g_gen.exit_status = WEXITSTATUS(pids[1]);
	if (WIFSIGNALED(pids[1]))
	{
		if (WTERMSIG(pids[1]) == 3)
			printf("Quit: 3\n");
		g_gen.exit_status = 128 + WTERMSIG(pids[1]);
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
	if (pid == 0)
	{
		sig_dfl();
		envp = make_envp();
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
	return (pid);
}

static void	close_pipes(int **pipes, int pipes_count)
{
	int	i;

	i = 0;
	while (i < pipes_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free (pipes);
}

void	execute(t_cmd *cmds, int pipes_count)
{
	int		i;
	int		**pipes;
	int		pid_status[2];
	
	i = 0;
	pipes = alloc_pipes(pipes_count);
	if (open_pipes(pipes, pipes_count) == EXIT_FAILURE)
		return ;
	while (i <= pipes_count)
	{
		if (pipes_count)
		{
			if (i == 0)
				set_pipes(&cmds[i], NULL, pipes[i]);
			else if (i == pipes_count)
				set_pipes(&cmds[i], pipes[i - 1], NULL);
			else
				set_pipes(&cmds[i], pipes[i - 1], pipes[i]);
		}
		pid_status[0] = execute_command(&cmds[i], pipes_count + 1);
		close_files(&cmds[i]);
		i++;
	}
	close_pipes(pipes, pipes_count);
	wait_child(pid_status);
	sig_handler();
}