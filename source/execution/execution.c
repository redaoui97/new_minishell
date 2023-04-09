/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:30:27 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/09 22:01:50 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static char*	find_path_env()
// {
// 	char		*path;
// 	t_env_elem	*ptr;
// 	int		i;

// 	path = NULL;
// 	i = 0;
// 	// ptr = g_data.ev->head;
// 	// while (i < g_data.ev->size)
// 	// {
// 	// 	if (!ft_strcmp(ptr->key, "PATH"))
// 	// 		return (ptr->value);
// 	// 	ptr = ptr->next;
// 	// 	i++;
// 	// }
// 	return (path);
// }

// /*gets the right path from a $PATH env*/
// char	*get_path(char *cmd, char *env_path)
// {
// 	char	**paths;
// 	char	*path;
// 	int		i;

// 	if (access(cmd, X_OK) == 0)
// 		return (cmd);
// 	paths = ft_split_adjusted(env_path, ':');
// 	i = 0;
// 	while (paths[i])
// 	{
// 		path = ft_strjoin_adjusted(paths[i], "/");
// 		path = ft_strjoin_adjusted(path, cmd);
// 		if (access(path, X_OK) == 0)
// 		{
// 			while (paths[++i])
// 				free (paths[i]);
// 			free (paths);
// 			return (path);
// 		}
// 		free (path);
// 		i++;
// 	}
// 	free (paths);
// 	return (NULL);
// }

// static void	execute_child(char **cmd, int fd_in, int fd_out)
// {
// 	pid_t	pid;
// 	char	*path;

// 	if (fd_in < 0 || fd_out < 0 || ft_strlen(cmd[0]) == 0)
// 		return ;
// 	pid = fork();
// 	if (pid == -1)
// 		fatal_error("failed to create a child process!");
// 	if (pid == 0)
// 	{		
// 		path = get_path(cmd[0], find_path_env());
// 		if (fd_in != 0 && fd_out != 1)
// 		{
// 			dup2(fd_out, 1);
// 			dup2(fd_in, 0);
// 			close (fd_out);
// 			close (fd_in);
// 		}
// 		execve(path, cmd, g_data.env);
// 	}
// }

// static void	wait_child()
// {
// 	int	wait_return;

// 	wait_return = wait (NULL);
// 	while (wait_return > 0)
// 		wait_return = wait(NULL);
// }

// static int	check_cmd(char **cmd, int *in_out)
// {
// 	in_out[0] = 0;
// 	in_out[1] = 1;
// 	if (get_path(cmd[0], find_path_env()) == NULL)
// 	{
// 		simple_error(ft_strjoin_adjusted(ft_strdup("Command not found: "), cmd[0]));
// 		return (0);
// 	}
// 	else
// 		return (1);
// }

void	execute(t_cmd *cmds, int pipes_count)
{
	int	i;

	i = 0;
	while ((cmds)[i] != NULL)
	{
		printf("cmd%d:%s\n", i, cmds[i].cmd_args[0]);
		i++;
	}
}