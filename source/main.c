/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 01:52:29 by ael-yamo          #+#    #+#             */
/*   Updated: 2023/04/15 10:43:19 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_gen	g_gen;

static int	all_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	init_minishell(char **envp, char **argv)
{
	char	p[PATH_MAX];

	(void)argv;
	getcwd(p, PATH_MAX);
	g_gen.pwd = ft_strdup(p);
	g_gen.env = env_create(envp);
	g_gen.envp = NULL;
	g_gen.exit_status = 0;
	g_gen.exec = 0;
	handle_signals();
}

void	minishell(t_token **tokens)
{
	expander(tokens);
	expander_in_quotes(tokens);
	join_word(tokens);
	rm_spaces(tokens);
	rm_quotes_tokens(tokens);
	g_gen.exec = 0;
	g_gen.skip_all = 0;
	parse_cmds(tokens);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*tokens;

	if (argc != 1)
		return (1);
	init_minishell(envp, argv);
	while (1)
	{
		line = readline("minishell> ");
		if (line)
		{
			if (!ft_strcmp(line, "") || all_spaces(line))
				continue ;
			add_history(line);
			tokens = tokenize(line);
			free(line);
			if (syntax_err(tokens))
				minishell(&tokens);
			else
				clear_tokens(&tokens);
		}
		else
			fatal_error(NULL);
	}
	return (0);
}
