/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 02:31:20 by ael-yamo          #+#    #+#             */
/*   Updated: 2023/04/11 01:26:13 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	write_to_fd(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

int	expand_y_n(char **str)
{
	char	c;

	c = (*str)[0];
	if ((*str)[0] != '\0' && ((*str)[0] == '\'' || (*str)[0] == '\"'))
	{
		*str = rm_quotes(*str, c);
		return (0);
	}
	return (1);
}
