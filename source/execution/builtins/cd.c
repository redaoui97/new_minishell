/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 03:29:28 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/12 02:39:13 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*get_home_path()
{
	char	*home;
	t_list	*ptr;

	home = NULL;
	ptr = g_gen.env;
	while (ptr)
	{
		if (!ft_strncmp("HOME", (char *)ptr->content, 4))
			return (((char *)ptr->content) + 5);
		ptr = ptr->next;
	}
	return (home);
}

static char	*get_cwd()
{
	t_list	*ptr;

	ptr = g_gen.env;
	while (ptr)
	{
		if (!ft_strncmp("PWD", (char *)ptr->content, 3))
		{
			return (((char *)ptr->content) + 4);
		}
		ptr = ptr->next;
	}
	return (NULL);
}

static int	change_dir(char **dir, char *cwd)
{
	t_list	*ptr;

	ptr = g_gen.env;
	while (ptr)
	{
		if (!ft_strncmp("PWD", (char *)ptr->content, 3))
		{
			free (ptr->content);
			ptr->content = ft_strjoin("PWD=", *dir);
		}
		if (!ft_strncmp("OLDPWD", (char *)ptr->content, 6))
		{
			free (ptr->content);
			ptr->content = ft_strjoin("PWD=", cwd);
		}
		ptr = ptr->next;
	}
	if (chdir(*dir) != 0)
	{
		simple_error(ft_strdup("Failed to change direcoty"));
		free (*dir);
		return (EXIT_FAILURE);
	}
	free(*dir);
	return (EXIT_SUCCESS);
}

static int	cd_to_dir(char **dir, char *cmd_dir, char *cwd)
{
	struct stat	st;
	
    if (!(stat(*dir, &st) == 0 && S_ISDIR(st.st_mode)))
	{
		simple_error(ft_strjoin("no such file or directory: ", cmd_dir));
		return (EXIT_FAILURE);
	}
	return (change_dir(dir, cwd));
}

int		exec_cd(t_cmd *cmds)
{
	char	*dir;
	char	*home;
	char	*cwd;
	
	home = get_home_path();
	cwd = get_cwd();
	if ((cmds->cmd_args)[1] == NULL)
		dir = ft_strdup(home);
	else if ((cmds->cmd_args)[1][0] == '/')
		dir = ft_strdup((cmds->cmd_args)[1]);
	else if ((cmds->cmd_args)[1][0] == '~')
		dir = ft_strjoin(home, (cmds->cmd_args)[1] + 1);
	else if ((cmds->cmd_args)[1][0] == '.')
		dir = ft_strjoin(cwd, (cmds->cmd_args)[1] + 1);
	else
	{
		dir = ft_strjoin(cwd, "/");
		dir = ft_strjoin_adjusted(dir, (cmds->cmd_args)[1]);
	}
	return (cd_to_dir(&dir, (cmds->cmd_args)[1], cwd));
}