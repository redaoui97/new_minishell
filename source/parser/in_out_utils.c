/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 02:23:50 by ael-yamo          #+#    #+#             */
/*   Updated: 2023/04/14 06:59:23 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_file(t_token **tokens, int type)
{
	int	fd;
	int	status;

	status = 0;
	fd = -1;
	if (type == GREAT)
		fd = open((*tokens)->next->data, O_RDWR | O_CREAT | O_TRUNC, 0777);
	else if (type == LESS)
		fd = open((*tokens)->next->data, O_RDWR, 0777);
	else if (type == DGREAT)
		fd = open((*tokens)->next->data, O_RDWR | O_CREAT | O_APPEND, 0777);
	else if (type == DLESS)
	{
		if ((*tokens)->next->old_data)
			fd = heredoc(ft_strdup((*tokens)->next->old_data), &status);
		else
			fd = heredoc(ft_strdup((*tokens)->next->data), &status);
		if (status)
			fd = status * (-1);
	}
	open_rest_file_err(fd, tokens, status);
	return (fd);
}

int	creat_in_files(t_cmd **cmds, t_token *tokens, int i)
{
	int	fd;

	fd = open_file(&tokens, tokens->type);
	if ((*cmds)[i].infile > -1)
	{
		if (close((*cmds)[i].infile) == -1)
			perror("close : ");
	}
	if (fd <= -1)
		(*cmds)[i].exec = fd * (-1);
	(*cmds)[i].infile = fd;
	return (fd);
}

int	creat_out_files(t_cmd **cmds, t_token *tokens, int i)
{
	int	fd;

	fd = open_file(&tokens, tokens->type);
	if ((*cmds)[i].outfile != -1)
	{
		if (close((*cmds)[i].outfile) == -1)
		{
			perror("close : ");
			exit(3);
		}
	}
	if (fd <= -1)
		(*cmds)[i].exec = fd * (-1);
	(*cmds)[i].outfile = fd;
	return (fd);
}
