/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 22:44:12 by ooumlil           #+#    #+#             */
/*   Updated: 2022/09/29 08:41:15 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// get_path join the cmd with the path in PATH in env arr
// i. e. /bin/ls

char	**get_path(char *s)
{
	int		i;
	char	**paths;

	paths = ft_split(get_env("PATH="), ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], s);
	}
	paths[i] = 0;
	return (paths);
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
