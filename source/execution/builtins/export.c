/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 04:28:54 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/14 05:56:56 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	eql_placemenet(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static int	check_exp_exists(char *exp)
{
	t_list	*ptr;

	ptr = g_gen.env;
	while (ptr)
	{
		if (eql_placemenet(exp) == -1)
		{
			if (!ft_strncmp(exp, ptr->content, ft_strlen(exp)))
				return (1);
		}
		else
		{
			if (!ft_strncmp(exp, ptr->content, eql_placemenet(exp)))
			{
				remove_env_var(ptr);
				return (0);
			}
		}
		ptr = ptr->next;
	}
	return (0);
}

static int	add_exp_env(char *new_env)
{
	char	*new;
	t_list	*tmp;

	if (new_env[0] == '=')
		return (EXIT_FAILURE);
	if (check_exp_exists(new_env))
		return (EXIT_SUCCESS);
	new = ft_strdup(new_env);
	tmp = ft_lstnew(new);
	tmp->exp = 1;
	ft_lstadd_back(&(g_gen.env), tmp);
	return (EXIT_SUCCESS);
}

int	exec_export(t_cmd *cmds)
{
	int	i;

	i = 1;
	if ((cmds->cmd_args)[1])
	{
		while ((cmds->cmd_args)[i])
		{
			if (add_exp_env((cmds->cmd_args)[i]) == EXIT_FAILURE)
			{
				g_gen.exit_status = 1;
				simple_error(ft_strjoin(
						(cmds->cmd_args)[i], " not a valid identifier"));
				return (EXIT_FAILURE);
			}
			i++;
		}
	}
	else
	{
		print_sorted_args();
	}
	g_gen.exit_status = 0;
	return (EXIT_SUCCESS);
}
