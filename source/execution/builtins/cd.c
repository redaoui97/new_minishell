/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 03:29:28 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/15 11:40:59 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*get_home_path(void)
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

static char	*get_cwd(void)
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
	char	cwdd[256];

	ptr = g_gen.env;
	if (chdir(*dir) != 0)
		return (cd_error(dir));
	while (ptr)
	{
		if (!ft_strncmp("PWD", (char *)ptr->content, 3))
		{
			free(ptr->content);
			ptr->content = ft_strjoin("PWD=", getcwd(cwdd, sizeof(cwdd)));
		}
		if (!ft_strncmp("OLDPWD", (char *)ptr->content, 6))
		{
			free(ptr->content);
			ptr->content = ft_strjoin("OLDPWD=", cwd);
		}
		ptr = ptr->next;
	}
	free(cwd);
	free(*dir);
	g_gen.exit_status = 0;
	return (EXIT_SUCCESS);
}

static char	*ret_dir(t_cmd *cmds, char *cwd, char *home)
{
	char	*dir;

	if ((cmds->cmd_args)[1] == NULL)
		dir = ft_strdup(home);
	else if ((cmds->cmd_args)[1][0] == '/')
		dir = ft_strdup((cmds->cmd_args)[1]);
	else if ((cmds->cmd_args)[1][0] == '~')
		dir = ft_strjoin(home, (cmds->cmd_args)[1] + 1);
	else
	{
		dir = ft_strjoin(cwd, "/");
		dir = ft_strjoin_adjusted(dir, (cmds->cmd_args)[1]);
	}
	return (dir);
}

int	exec_cd(t_cmd *cmds)
{
	char	*dir;
	char	*home;
	char	*cwd;

	if (check_cmd_nbr(cmds, 2))
		return (1);
	home = get_home_path();
	cwd = get_cwd();
	if (!cwd || !home)
		return (1);
	dir = ret_dir(cmds, cwd, home);
	return (change_dir(&dir, ft_strdup(cwd)));
}
