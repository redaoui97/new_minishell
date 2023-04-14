/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 06:27:10 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/14 09:31:16 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_child(int pids)
{
	int	status;
	
	if (pids != -1)
	waitpid(pids, &status, 0);
	while (waitpid(-1, 0, 0) != -1)
		;
	g_gen.exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
			printf("Quit: 3\n");
		g_gen.exit_status = 128 + WTERMSIG(status);
	}
}

int	check_cmd(t_cmd *cmd, int cmd_num)
{
	char	*path;

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
		simple_error(ft_strjoin_adjusted(ft_strdup("Command not found: "),
				cmd->cmd_args[0]));
		free (path);
		return (EXIT_FAILURE);
	}
	else
	{
		free (path);
		return (EXIT_SUCCESS);
	}
}
