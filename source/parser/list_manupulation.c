/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manupulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 01:52:21 by ael-yamo          #+#    #+#             */
/*   Updated: 2023/04/09 17:09:27 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*new_token(unsigned int type, char *data)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->data = data;
	token->old_data = NULL;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	add_at_end(t_token **tokens_head, t_token *token)
{
	t_token	*tmp;

	tmp = *tokens_head;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	token->prev = tmp;
	tmp->next = token;
}

void	add_token_last(t_token **token_head, unsigned int type, char *data)
{
	t_token	*ptr;
	
	ptr = NULL;
	ptr = new_token(type, data);
	if (*token_head == NULL)
		*token_head = ptr;
	else
		add_at_end(token_head, ptr);
}

int	len_list(t_list **list)
{
	t_list	*tmp;
	int		index;

	index = 0;
	tmp = *list;
	while (tmp)
	{
		tmp = tmp->next;
		index++;
	}
	return (index);
}