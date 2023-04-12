/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 04:29:00 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/12 01:24:23 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	exec_pwd()
{
	t_list	*ptr;

	ptr = g_gen.env;
	while (ptr)
	{
		if (!ft_strncmp("PWD", (char *)ptr->content, 3))
		{
			printf("%s\n", ((char *)ptr->content) + 4);
			return (0);
		}
		ptr = ptr->next;
	}
	return (1);
}