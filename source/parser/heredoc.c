/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 01:52:11 by ael-yamo          #+#    #+#             */
/*   Updated: 2023/04/13 06:48:14 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	heredoc_p(char *limiter, int *pipe_fd)
{
	int		expand;
	char	*line;

	expand = expand_y_n(&limiter);
	signal(SIGINT, handler1);
	line = readline("> ");
	while (line != NULL && ft_strcmp(line, limiter))
	{
		if (expand)
			line = expander_heredoc(line);
		write_to_fd(pipe_fd[1], line);
		free(line);
		line = readline("> ");
	}
	if (line != NULL)
		free(line);
	exit(0);
}

int	heredoc(char *limiter, int *exit_status)
{
	int	pipe_fd[2];
	int	pid;

	if (pipe(pipe_fd) < 0)
	{
		perror("");
		return (-1);
	}
	pid = fork();
	if (pid == 0)
	{
		heredoc_p(limiter, pipe_fd);
	}
	if (limiter != NULL)
		free(limiter);
	wait_heredoc(exit_status, pid);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}
