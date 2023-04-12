/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 04:28:39 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/12 05:34:53 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	exec_env()
{
	t_list	*ptr;

	ptr = g_gen.env;
	while (ptr)
	{
		if (ptr->exp == 0)
			printf("%s\n", (char *)ptr->content);
		ptr = ptr->next;
	}
	return (EXIT_SUCCESS);
}