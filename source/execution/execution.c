/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:30:27 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/14 09:30:43 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	child_exec(t_cmd *cmd, int cmd_num, int **pipes)
{
	char	**envp;
	char	*path;

	sig_dfl();
	envp = make_envp();
	path = get_path(cmd->cmd_args[0], find_path_env());
	if (cmd->infile != -1)
	{
		dup2(cmd->infile, 0);
		close (cmd->infile);
		if (cmd->pipe_in)
			close (cmd->pipe_in);
	}
	if (cmd->outfile != -1)
	{
		dup2(cmd->outfile, 1);
		close (cmd->infile);
		if (cmd->pipe_out)
			close (cmd->pipe_out);
	}
	close_pipes(pipes, cmd_num -1);
	execve(path, cmd->cmd_args, envp);
}

static int	execute_command(t_cmd *cmd, int cmd_num, int **pipes)
{
	pid_t	pid;

	if (check_cmd(cmd, cmd_num) == EXIT_FAILURE)
		return (-1);
	(void)pipes;
	pid = fork();
	if (pid == -1)
		return ((void)simple_error("failed to create a child process!"), -1);
	if (pid == 0)
	{
		child_exec(cmd, cmd_num, pipes);
	}
	return (pid);
}

static void	process_pipes(int i, t_cmd *cmds, int **pipes, int pipes_count)
{
	if (i == 0)
		set_pipes(&(cmds[i]), NULL, pipes[i]);
	else if (i == pipes_count)
		set_pipes(&(cmds[i]), pipes[i - 1], NULL);
	else
		set_pipes(&(cmds[i]), pipes[i - 1], pipes[i]);
}

void	execute(t_cmd *cmds, int pipes_count)
{
	int		i;
	int		**pipes;
	pid_t	pid_status;

	i = 0;
	pipes = alloc_pipes(pipes_count);
	if (open_pipes(pipes, pipes_count) == EXIT_FAILURE)
		return ;
	sig_ign();
	while (i <= pipes_count)
	{
		if (pipes_count)
			process_pipes(i, cmds, pipes, pipes_count);
		pid_status = execute_command(&cmds[i], pipes_count + 1, pipes);
		close_files(&cmds[i]);
		i++;
	}
	close_pipes(pipes, pipes_count);
	wait_child(pid_status);
	sig_handler();
}
