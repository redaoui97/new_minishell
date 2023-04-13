/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 04:28:54 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/13 07:24:15 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	add_exp_env(char *new_env)
{
	char	*new;
	t_list	*tmp;

	if (new_env[0] == '=')
		return (EXIT_FAILURE);
	new = ft_strdup(new_env);
	tmp = ft_lstnew(new);
	tmp->exp = 1;
	ft_lstadd_back(&(g_gen.env), tmp);
	return (EXIT_SUCCESS);
}

void	sort_string(char **strings, int n)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (i < (n - 1))
	{
		j = 0;
		while (j < (n - i - 1))
		{
			if (strcmp(strings[j], strings[j + 1]) > 0)
			{
				temp = strings[j];
				strings[j] = strings[j + 1];
				strings[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_processed_env(char *env)
{
	int	i;
	int	has_eql;

	i = 0;
	has_eql = 0;
	printf("declare -x ");
	while (env[i])
	{
		printf("%c", env[i]);
		if (env[i] == '=' && !has_eql)
		{
			printf("\"");
			has_eql++;
		}
		i++;
	}
	if (has_eql)
		printf("\"");
	printf("\n");
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
				simple_error(ft_strjoin((cmds->cmd_args)[i],
										" not a valid identifier"));
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
