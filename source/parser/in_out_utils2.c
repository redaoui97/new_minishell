/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 06:54:53 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/14 06:57:40 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	open_file_err(t_token **tokens, int fd, int status)
{
	if ((*tokens)->next->old_data == NULL && (fd == -1 && status != 1))
		perror("minishell");
	else
	{
		if ((ft_strcmp((*tokens)->next->data, "") == 0)
			&& (*tokens)->next->old_data != NULL)
			printf("minishell: %s: ambiguous redirect\n",
				(*tokens)->next->old_data);
		else if ((*tokens)->next->old_data != NULL && status != 1)
			perror("minishelll");
	}
}

static void	open_rest(t_token *token)
{
	int	ingnor;

	while (token)
	{
		if (token->type == DLESS)
		{
			if (token->next->old_data)
				heredoc(ft_strdup(token->next->old_data), &ingnor);
			else
				heredoc(ft_strdup(token->next->data), &ingnor);
		}
		token = token->next;
	}
}

void	open_rest_file_err(int fd, t_token **tokens, int status)
{
	if (fd < 0)
	{
		open_rest((*tokens)->next);
		open_file_err(tokens, fd, status);
	}
}
