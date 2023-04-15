/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 04:28:19 by oufisaou          #+#    #+#             */
/*   Updated: 2023/04/15 00:48:09 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_signals(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &term);
	signal(SIGQUIT, handler);
	signal(SIGINT, handler);
	return (0);
}

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		g_gen.exit_status = 1;
		ft_putstr_fd("\n", 2);
		//rl_replace_line("", 1);
		rl_on_new_line();
	}
	rl_on_new_line();
	rl_redisplay();
}

void	sig_ign(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_dfl(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	sig_handler(void)
{
	signal(SIGQUIT, handler);
	signal(SIGINT, handler);
}
