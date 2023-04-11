/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 01:52:29 by ael-yamo          #+#    #+#             */
/*   Updated: 2023/04/11 00:38:42 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
t_gen	g_gen;

char	**convert_to_array(t_list **env)
{
	int		index;
	int		size;
	char	**arr;
	t_list	*tmp;

	size = len_list(env);
	tmp = *env;
	arr = (char **)malloc(sizeof(char *) * (size + 1));
	index = 0;
	while (tmp->next)
	{
		arr[index] = tmp->content;
		tmp = tmp->next;
		index++;
	}
	arr[index] = NULL;
	return (arr);
}

void	init_minishell(char **envp)
{
	char	p[PATH_MAX];

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
	(void)argv;
	init_minishell(envp);
	while (1)
	{
		line = readline("minishell> ");
		if (line != NULL)
		{
			add_history(line);
			tokens = tokenize(line);
			free(line);
			if (syntax_err(tokens))
				minishell(&tokens);
			else
				clear_tokens(&tokens);
		}
		else
			ctrld();
	}
	return (0);
}
