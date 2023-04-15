/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:16:51 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/15 01:25:09 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_pipes(t_cmd *cmd, int *pipe_in, int *pipe_out)
{
	if (cmd->infile == -1 && pipe_in)
	{
		cmd->infile = pipe_in[0];
		cmd->pipe_in = pipe_in[1];
	}
	if (cmd->outfile == -1 && pipe_out)
	{
		cmd->outfile = pipe_out[1];
		cmd->pipe_out = pipe_out[0];
	}
}

void	close_files(t_cmd *cmd)
{
	if (cmd->infile != -1)
		close(cmd->infile);
	if (cmd->outfile != -1)
		close(cmd->outfile);
}

int	**alloc_pipes(int num)
{
	int	**pipes;
	int	i;

	pipes = (int **)malloc(sizeof(int *) * num);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < num)
	{
		pipes[i] = (int *)malloc (sizeof(int) * 2);
		if (pipes[i] == NULL)
		{
			while (i)
			{
				free (pipes[i]);
				i--;
			}
			free (pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

int	open_pipes(int **pipes, int pipes_count)
{
	int	i;
	int	j;

	if (!pipes)
		return (EXIT_FAILURE);
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

void	close_pipes(int **pipes, int pipes_count)
{
	int	i;

	i = 0;
	while (i < pipes_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}
