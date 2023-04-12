/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 04:46:31 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/12 03:12:49 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_builtin(t_cmd *cmds)
{
	char	*cmd;

	cmd = cmds->cmd_args[0];
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	return (0);
}
static void	exec_builtin_func(t_cmd *cmds, int cmd_num)
{
	char	*cmd;

		cmd = cmds->cmd_args[0];
		if (!ft_strcmp(cmd, "echo"))
			exec_echo(cmds);
		if (!ft_strcmp(cmd, "exit"))
			exec_exit(cmd_num);
		if (!ft_strcmp(cmd, "pwd"))
			exec_pwd();
		if (!ft_strcmp(cmd, "cd"))
			exec_cd(cmds);
		if (!ft_strcmp(cmd, "env"))
			exec_env();
		// if (!ft_strcmp(cmd, "export"))
		// 	exec_export(cmds)s;
		// if (!ft_strcmp(cmd, "unset"))
		// 	exec_unset(cmds);
}

int	exec_builtin(t_cmd *cmds, int cmd_num)
{
	int	std_dir[2];
	
	if (cmds->infile != -1)
	{
		std_dir[0] = dup(0);
		dup2(cmds->infile, 0);
	}
	if (cmds->outfile != -1)
	{
		std_dir[1] = dup(1);
		dup2(cmds->outfile, 1);
	}
	exec_builtin_func(cmds, cmd_num);
	if (cmds->infile != -1)
	{
		close(cmds->infile);
		dup2(std_dir[0], STDIN_FILENO);
		close(std_dir[0]);
	}
	if (cmds->outfile != -1)
	{
		close(cmds->outfile);
		dup2(std_dir[1], STDOUT_FILENO);
		close(std_dir[1]);
	}
	return (0);
}