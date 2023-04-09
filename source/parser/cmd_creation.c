/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 01:51:12 by ael-yamo          #+#    #+#             */
/*   Updated: 2023/04/09 19:45:37 by rnabil           ###   ########.fr       */
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
	int		status;
	
	cmds = creat_cmds(tokens);
	*pipes = count_pipes(*tokens);
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
	//if ((get_cmds_path(&cmds, pipes_num) == 0) &&\(g_gen.skip_all == 0))
		//execution(cmds, pipes_num);
	printf("'%s'\n",cmds[0].cmd_args[0]);
	free_cmds(cmds, pipes_num);
}
