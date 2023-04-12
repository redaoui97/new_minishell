/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 01:35:11 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/12 21:51:12 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	simple_error(char *msg)
{
	msg = ft_strjoin_adjusted(msg, "\n");
	write(2, msg, ft_strlen(msg));
	free(msg);
	return (EXIT_FAILURE);
}