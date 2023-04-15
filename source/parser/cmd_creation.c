/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 01:51:12 by ael-yamo          #+#    #+#             */
/*   Updated: 2023/04/15 06:12:25 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_cmds(t_token *tokens)
{
	char	**cmds;
	int		i;

	i = 0;
	cmds = (char **)malloc(sizeof(char *) * (count_tokens(tokens) + 1));
	if (cmds == NULL)
		return (NULL);
	while (tokens)
	{
		if ((tokens->data)[0] < 32 || (tokens->data)[0] > 126)
			cmds[i] = ft_substr(tokens->data, 2, ft_strlen(tokens->data) - 1);
		else
			cmds[i] = ft_strdup(tokens->data);
		tokens = tokens->next;
		i++;
	}
	cmds[i] = NULL;
	return (cmds);
}

void	creat_cmd_args(t_cmd **cmds, int pipe)
{
	int	i;

	i = 0;
	while (i <= pipe)
	{
		(*cmds)[i].cmd_args = get_cmds((*cmds)[i].tokens_cmd);
		clear_tokens(&((*cmds)[i].tokens_cmd));
		i++;
	}
}

t_cmd	*setup_cmds(t_token **tokens, int *pipes)
{
	t_cmd	*cmds;

	cmds = creat_cmds(tokens, &*pipes);
	check_file_direcitons(&cmds, *pipes);
	rm_redirecitons(&cmds, *pipes);
	creat_cmd_args(&cmds, *pipes);
	return (cmds);
}

void	parse_cmds(t_token **toknes)
{
	t_cmd	*cmds;
	int		pipes_num;

	cmds = setup_cmds(toknes, &pipes_num);
	execute(cmds, pipes_num);
	free_cmds(cmds, pipes_num);
}
