/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 04:28:07 by oufisaou          #+#    #+#             */
/*   Updated: 2023/04/14 05:11:10 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quotes(t_token *token)
{
	while (token != NULL)
	{
		printf("hna\n");
		if (token->type == QUOTE || token->type == DQUOTE)
		{
			printf("hna:%d\n",(int)ft_strlen(token->data));
			if (token->data[0] == token->data[(int)ft_strlen(token->data) - 1]
				&& ft_strlen(token->data) != 1)
				printf("hna3\n");
			else
				return (0);
		}
		token = token->next;
	}
	return (1);
}

int	check_pipe(t_token *token)
{
	int	found;

	found = 0;
	if (token && token->type == PIPE)
		return (0);
	while (token != NULL)
	{
		if (token->type == PIPE)
		{
			if (found == 1)
				return (0);
			found = 1;
		}
		else if (token->type == WORD || token->type == QUOTE
				|| token->type == DQUOTE || token->type == DOLLAR)
			found = 0;
		token = token->next;
	}
	if (found == 1)
		return (0);
	return (1);
}

int	check_directions(t_token *token)
{
	int	found;

	found = 0;
	while (token != NULL)
	{
		if (token->type == GREAT || token->type == LESS || token->type == DGREAT
			|| token->type == DLESS)
		{
			if (found == 1)
				return (0);
			found = 1;
		}
		else if (token->type == PIPE && found == 1)
			return (0);
		else if (token->type == WORD || token->type == QUOTE
				|| token->type == DQUOTE || token->type == DOLLAR)
			found = 0;
		token = token->next;
	}
	if (found == 1)
		return (0);
	return (1);
}

int	syntax_err(t_token *token)
{
	if (check_quotes(token) && check_pipe(token) && check_directions(token))
		return (1);
	ft_putstr_fd("syntax error\n", 2);
	g_gen.exit_status = 258;
	return (0);
}