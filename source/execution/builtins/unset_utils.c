/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 08:05:29 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/14 06:14:16 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	remove_env_var_middle(t_list *ptr)
{
	t_list	*ptr2;

	ptr2 = g_gen.env;
	while (ptr2)
	{
		if (ptr2->next == ptr)
		{
			ptr2->next = ptr->next;
			return ;
		}
		ptr2 = ptr2->next;
	}
}

static void	free_env(t_list *ptr)
{
	free(ptr->content);
	free(ptr);
}

void	remove_env_var(t_list *ptr)
{
	t_list	*ptr2;

	ptr2 = g_gen.env;
	if (ptr == g_gen.env)
		g_gen.env = ptr->next;
	else if (ptr->next == NULL)
	{
		while (ptr2)
		{
			if (ptr2->next == ptr)
			{
				ptr2->next = NULL;
				break ;
			}
			ptr2 = ptr2->next;
		}
	}
	else
		remove_env_var_middle(ptr);
	free_env(ptr);
}
