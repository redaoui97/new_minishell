/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 01:51:46 by ael-yamo          #+#    #+#             */
/*   Updated: 2023/04/12 09:28:57 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_envp(void)
{
	int	i;

	i = 0;
	if (g_gen.envp != NULL)
	{
		while (g_gen.envp[i] != NULL)
		{
			free(g_gen.envp[i]);
			i++;
		}
		free(g_gen.envp);
	}
}

char	*str_to_lower(char *str)
{
	char	*new_str;
	int		i;

	i = 0;
	if (str != NULL)
	{
		new_str = malloc(sizeof(char) * ft_strlen(str) + 1);
		while (str[i] != '\0')
		{
			new_str[i] = ft_tolower(str[i]);
			i++;
		}
		new_str[i] = '\0';
		return (new_str);
	}
	return (NULL);
}

void	free_cmds(t_cmd *cmds, int pipes_num)
{
	int	i;
	int	j;

	i = 0;
	if (cmds != NULL)
	{
		while (i <= pipes_num)
		{
			j = 0;
			if (cmds[i].cmd_args != NULL)
			{
				while (cmds[i].cmd_args[j] != NULL)
				{
					free(cmds[i].cmd_args[j]);
					j++;
				}
				free(cmds[i].cmd_args);
			}
			if (cmds[i].cmd_path != NULL)
				free(cmds[i].cmd_path);
			i++;
		}
		free(cmds);
	}
}
