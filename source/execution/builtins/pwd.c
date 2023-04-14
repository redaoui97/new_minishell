/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 04:29:00 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/14 06:13:46 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	exec_pwd(void)
{
	t_list	*ptr;

	ptr = g_gen.env;
	while (ptr)
	{
		if (!ft_strncmp("PWD", (char *)ptr->content, 3))
		{
			printf("%s\n", ((char *)ptr->content) + 4);
			g_gen.exit_status = 0;
			return (0);
		}
		ptr = ptr->next;
	}
	simple_error(ft_strdup("'cwd' not found"));
	g_gen.exit_status = 1;
	return (1);
}
