/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:16:51 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/13 07:34:18 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_pipes(t_cmd *cmd, int (*pipe_in)[2], int (*pipe_out)[2])
{
	if (cmd->infile == -1 && *pipe_in)
		cmd->infile = (*pipe_in)[0];
	if (cmd->outfile == -1 && *pipe_out)
		cmd->outfile = (*pipe_out)[1];
}

void	close_files(t_cmd *cmd)
{
	if (cmd->infile != -1)
		close(cmd->infile);
	if (cmd->outfile != -1)
		close(cmd->outfile);
}

int	open_pipes(int (*pipes)[2], int pipes_count)
{
	int	i;
	int	j;

	i = 0;
	while (i < pipes_count)
	{
		j = 0;
		if (pipe(pipes[i]) == -1)
		{
			simple_error("Failed to create pipe");
			while (j < i)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
				j++;
			}
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
