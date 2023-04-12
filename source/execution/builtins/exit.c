/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 04:28:48 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/11 23:18:09 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	exec_exit(int cmd_num)
{
	printf("cmds:%d\n", cmd_num);
	if (cmd_num == 1)
	{
		free_all(g_gen.env);
		free(g_gen.pwd);
		free_envp();
		exit (0);
	}
	return (0);
}