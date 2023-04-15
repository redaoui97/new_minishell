/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 05:56:32 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/15 12:01:45 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

int	check_exp(char *exp, t_list *ptr)
{
	if (!ft_strncmp(exp, ptr->content, eql_placemenet(exp)))
	{
		if (ft_strlen(exp) > 1 && exp[eql_placemenet(exp)] == '+')
		{
			update_var(ptr, exp + eql_placemenet(exp) + 2);
			return (1);
		}
		else
			remove_env_var(ptr);
		return (0);
	}
	return (-1);
}

void	exec_error(void)
{
	simple_error(ft_strdup("not a valid identifier"));
	g_gen.exit_status = 1;
}
