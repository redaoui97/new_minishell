/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 04:29:07 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/12 21:51:09 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	find_eql(char *env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

int	remove_env(char *env)
{
	char	*env_name;
	t_list	*ptr;

	ptr = g_gen.env;
	while (ptr)
	{
		env_name = ft_substr(ptr->content, 0, find_eql(ptr->content));
		if (!ft_strcmp(env, env_name))
		{
			remove_env_var(ptr);
			return (EXIT_SUCCESS);
		}
		free(env_name);
		ptr = ptr->next;
	}
	return (EXIT_SUCCESS);
}

int	exec_unset(t_cmd *cmds)
{
	int i;

	i = 0;
	while ((cmds->cmd_args)[i])
	{
		remove_env((cmds->cmd_args)[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}