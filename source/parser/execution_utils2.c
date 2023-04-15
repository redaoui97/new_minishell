/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 01:51:49 by ael-yamo          #+#    #+#             */
/*   Updated: 2023/04/15 06:22:44 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//gotta delete
void	wait_all(int pid, int i, int pipes_num)
{
	int	status;

	if (i == pipes_num + 1)
	{
		waitpid(pid, &status, 0);
	}
	while (waitpid(-1, 0, 0) != -1)
		;
	g_gen.exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
			printf("Quit: 3\n");
		g_gen.exit_status = 128 + WTERMSIG(status);
	}
}
