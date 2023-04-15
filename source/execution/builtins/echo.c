/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 04:28:20 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/15 07:11:09 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	has_param(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (!(cmd->cmd_args)[1])
		return (0);
	if ((cmd->cmd_args)[1][0] != '-' || !(cmd->cmd_args)[1][1])
		return (0);
	while ((cmd->cmd_args)[1][i])
	{
		if ((cmd->cmd_args)[1][i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	exec_echo(t_cmd *cmd)
{
	int	i;
	int	param;

	param = 0;
	i = 1;
	if ((cmd->cmd_args)[1] && has_param(cmd))
	{
		i = 2;
		param = 1;
	}
	while (cmd->cmd_args[i])
	{
		printf("%s", cmd->cmd_args[i]);
		i++;
		if (cmd->cmd_args[i])
			printf(" ");
	}
	if (!param)
		printf("\n");
	g_gen.exit_status = 0;
	return (0);
}
