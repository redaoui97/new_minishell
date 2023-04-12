/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:13:20 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/12 09:16:00 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_path_env()
{
	t_list	*ptr;

	ptr = g_gen.env;
	while (ptr)
	{
		if (ft_strncmp("PATH", (char *)ptr->content, 4) == 0)
			return ((char *)ptr->content + 5);
		ptr = ptr->next;
	}
	return (NULL);
}

/*gets the right path from a $PATH env*/
char	*get_path(char *cmd, char *env_path)
{
	char	**paths;
	char	*path;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	paths = ft_split_adjusted(env_path, ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin_adjusted(paths[i], "/");
		path = ft_strjoin_adjusted(path, cmd);
		if (access(path, X_OK) == 0)
		{
			while (paths[i])
				free (paths[++i]);
			free (paths);
			return (path);
		}
		free (path);
		i++;
	}
	free (paths);
	return (NULL);
}

int	get_envp_size()
{
	int	size;

	size = 0;
	t_list	*ptr;

	ptr = g_gen.env;
	while (ptr)
	{
		size++;
		ptr = ptr->next;
	}
	return (size);
}

char	**make_envp()
{
	char	**envp;
	t_list	*ptr;
	int		i;

	ptr = g_gen.env;
	i = 0;
	envp = (char **)malloc (sizeof(char *) * (get_envp_size() + 1));
	while (ptr)
	{
		envp[i++] = (char *)ptr->content;
		ptr = ptr->next;
	}
	envp[i] = NULL;
	return (envp);
}	