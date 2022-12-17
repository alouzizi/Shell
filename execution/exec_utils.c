/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 22:44:12 by ooumlil           #+#    #+#             */
/*   Updated: 2022/12/17 18:41:20 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// get_path join the cmd with the path in PATH in env arr
// i. e. /bin/ls

char	**get_path(char *s)
{
	int		i;
	char	**paths;

	if (!g_global.g_env)
		return (NULL);
	paths = ft_split(get_value_from_env("PATH"), ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_strjoin(paths[i], "/", 1);
		paths[i] = ft_strjoin(paths[i], s, 1);
	}
	paths[i] = 0;
	return (paths);
}

// commands_execution checks whether the command
// can be executed or not

char	*check_access(char **paths, int i)
{
	char	*path;

	if (!paths)
		return (NULL);
	path = 0;
	while (paths[++i])
	{
		if (!access(paths[i], X_OK | F_OK))
		{
			path = ft_strdup(paths[i]);
			break ;
		}
	}
	free_array(paths);
	if (!path)
		return (NULL);
	return (path);
}

char	*check_absolute_path(char *s)
{
	char	*path;

	if (!s)
		return (NULL);
	if (!access(s, X_OK | F_OK))
	{
		path = ft_strdup(s);
		return (path);
	}
	return (NULL);
}

void	exit_status(int status)
{
	if (WIFEXITED(status))
		g_global.status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_global.status = 128 + WTERMSIG(status);
}
