/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 04:28:48 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/13 07:18:37 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	exec_exit(int cmd_num, int ret)
{
	if (cmd_num == 1)
	{
		free_all(g_gen.env);
		free(g_gen.pwd);
		free_envp();
		g_gen.exit_status = 0;
		exit(ret);
	}
	return (0);
}