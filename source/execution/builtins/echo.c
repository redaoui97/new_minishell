/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 04:28:20 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/14 08:42:54 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	exec_echo(t_cmd *cmd)
{
	int	i;
	int	param;

	param = 0;
	i = 1;
	if ((cmd->cmd_args)[1] && !ft_strcmp((cmd->cmd_args)[1], "-n"))
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
