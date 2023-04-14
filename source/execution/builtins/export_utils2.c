/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 05:56:32 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/14 06:40:15 by rnabil           ###   ########.fr       */
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
