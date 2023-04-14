/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 01:35:11 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/14 22:44:04 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	simple_error(char *msg)
{
	if (msg)
	{
		msg = ft_strjoin_adjusted(msg, "\n");
		write(2, msg, ft_strlen(msg));
		free(msg);
	}
	return (EXIT_FAILURE);
}

int	fatal_error(char *msg)
{
	simple_error(msg);
	free_all(g_gen.env);
	free(g_gen.pwd);
	free_envp();
	exit(0);
}

int	cd_error(char **dir)
{
	simple_error(ft_strdup("Failed to change directory"));
	free(*dir);
	g_gen.exit_status = 1;
	return (1);
}
