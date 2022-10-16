/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 22:44:12 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/16 13:00:28 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// get_path join the cmd with the path in PATH in env arr
// i. e. /bin/ls

char	*get_path(char *s, t_vars *v)
{
	int		i;
	char	**paths;
	char	*path;

	paths = ft_split(get_env("PATH", v), ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_strjoin(paths[i], "/", 1);
		paths[i] = ft_strjoin(paths[i], s, 1);
	}
	paths[i] = 0;
	i = -1;
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

void	exit_status(int status)
{
	if (WIFEXITED(status))
		g_global.status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_global.status = 128 + WTERMSIG(status);
}

int	builtincmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}
