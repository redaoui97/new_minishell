/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 07:05:55 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/12 21:50:59 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*envs made with export*/
static int	get_exp_envp_size(void)
{
	int		size;
	t_list	*ptr;

	size = 0;
	ptr = g_gen.env;
	while (ptr)
	{
		if (ptr->exp)
			size++;
		ptr = ptr->next;
	}
	return (size);
}

static char	**make_exp_envp(void)
{
	char	**envp;
	t_list	*ptr;
	int		i;

	ptr = g_gen.env;
	i = 0;
	envp = (char **)malloc(sizeof(char *) * (get_exp_envp_size() + 1));
	while (ptr)
	{
		if (ptr->exp)
			envp[i++] = (char *)ptr->content;
		ptr = ptr->next;
	}
	envp[i] = NULL;
	return (envp);
}

/*envs not made with export*/
static int	get_non_exp_envp_size(void)
{
	int		size;
	t_list	*ptr;

	size = 0;
	ptr = g_gen.env;
	while (ptr)
	{
		if (ptr->exp == 0)
			size++;
		ptr = ptr->next;
	}
	return (size);
}

static char	**make_non_exp_envp(void)
{
	char	**envp;
	t_list	*ptr;
	int		i;

	ptr = g_gen.env;
	i = 0;
	envp = (char **)malloc(sizeof(char *) * (get_non_exp_envp_size() + 1));
	while (ptr)
	{
		if (ptr->exp == 0)
			envp[i++] = (char *)ptr->content;
		ptr = ptr->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	print_sorted_args(void)
{
	char **exp_env;
	char **non_exp_env;
	int i;

	i = 0;
	exp_env = make_exp_envp();
	non_exp_env = make_non_exp_envp();
	sort_string(exp_env, get_exp_envp_size());
	sort_string(non_exp_env, get_non_exp_envp_size());
	while (i < get_non_exp_envp_size())
		print_processed_env(non_exp_env[i++]);
	i = 0;
	while (i < get_exp_envp_size())
		print_processed_env(exp_env[i++]);
	free(exp_env);
	free(non_exp_env);
}