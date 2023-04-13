/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 04:28:39 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/13 08:12:38 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	exec_env(t_cmd *cmds)
{
	t_list	*ptr;

	if (check_cmd_nbr(cmds, 1))
		return (EXIT_FAILURE);
	ptr = g_gen.env;
	while (ptr)
	{
		if (ptr->exp == 0)
			printf("%s\n", (char *)ptr->content);
		ptr = ptr->next;
	}
	g_gen.exit_status = 0;
	return (EXIT_SUCCESS);
}
