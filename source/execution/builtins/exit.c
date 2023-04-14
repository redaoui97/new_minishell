/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 04:28:48 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/14 22:43:35 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	exec_exit(t_cmd *cmd, int cmds, int ret)
{
	int	cmd_num;

	cmd_num = 0;
	while ((cmd->cmd_args)[cmd_num])
		cmd_num++;
	if (cmd_num > 1)
	{
		simple_error(ft_strdup("too many arguments"));
		g_gen.exit_status = 2;
	}
	if (cmd_num == 1 && cmds == 1)
	{
		free_all(g_gen.env);
		free(g_gen.pwd);
		free_envp();
		g_gen.exit_status = 0;
		exit(ret);
	}
	return (0);
}
