/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_asign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 01:52:36 by ael-yamo          #+#    #+#             */
/*   Updated: 2023/04/09 05:17:06 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*Could delete this*/
static void	assign_f(t_cmd **cmds, int i, int pipes_num, int **pipes)
{
	if ((*cmds)[i].infile == -1)
		(*cmds)[i].infile = STDIN_FILENO;
	if ((*cmds)[i].outfile == -1)
	{
		if (pipes_num == 0)
		{
			(*cmds)[i].outfile = STDOUT_FILENO;
			return ;
		}
		else
			(*cmds)[i].outfile = pipes[i][1];
	}
}

void	assign_pipes(int **pipes, t_cmd **cmds, int pipes_num)
{
	int	i;

	i = 0;
	while (i <= pipes_num)
	{
		if (i == 0)
			assign_f(cmds, i, pipes_num, pipes);
		if (i == pipes_num)
		{
			if ((*cmds)[i].infile == -1)
				(*cmds)[i].infile = pipes[i - 1][0];
			if ((*cmds)[i].outfile == -1)
				(*cmds)[i].outfile = STDOUT_FILENO;
		}
		if (i < pipes_num)
		{
			if ((*cmds)[i].infile == -1)
				(*cmds)[i].infile = pipes[i - 1][0];
			if ((*cmds)[i].outfile == -1)
				(*cmds)[i].outfile = pipes[i][1];
		}
		i++;
	}
}
