/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 04:28:39 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/15 07:22:33 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	has_value(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	exec_env(t_cmd *cmds)
{
	t_list	*ptr;

	if (check_cmd_nbr(cmds, 1))
	{
		g_gen.exit_status = 127;
		return (EXIT_FAILURE);
	}
	ptr = g_gen.env;
	while (ptr)
	{
		if (has_value((char *)ptr->content))
			printf("%s\n", (char *)ptr->content);
		ptr = ptr->next;
	}
	g_gen.exit_status = 0;
	return (EXIT_SUCCESS);
}
