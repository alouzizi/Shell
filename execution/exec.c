/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 12:14:09 by ooumlil           #+#    #+#             */
/*   Updated: 2022/09/15 05:13:34 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// get_path join the cmd with the path in PATH in env arr
// i. e. /bin/ls

char	**get_path(char *s, char **env)
{
	int		i;
	char	**paths;

	paths = ft_split(get_env("PATH=", env), ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], s);
	}
	paths[i] = 0;
	free (s);
	return (paths);
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

// commands_execution checks whether the command
// can be executed or not

void	commands_execution(char **path, char **cmd, char **env)
{
	int		fd;
	int		i;
	int		status;

	i = -1;
	while (path[++i])
		if (!access(path[i], X_OK))
			break ;
	fd = fork();
	if (!fd)
	{
		execve(path[i], cmd, env);
		exit (0);
	}
	else
	{
		g_global.signal = 1;
		waitpid(fd, &status, 0);
	}
	g_global.status = status % 256;
}

// checks if its one of the cmds asked in the subject
// and executes it or else executes it with execve func

int	isbuiltin(char **cmd, char **env)
{
	if (!cmd[0])
		return (1);
	else if (!builtincmp(cmd[0], "minishell"))
		return (ft_minishell(cmd, env), 1);
	else if (!builtincmp(cmd[0], "pwd"))
		return (ft_pwd(), 1);
	else if (!builtincmp(cmd[0], "echo"))
		return (ft_echo(cmd), 1);
	else if (!builtincmp(cmd[0], "env"))
		return (ft_env(env), 1);
	else if (!builtincmp(cmd[0], "export"))
		return (ft_export(cmd, env), 1);
	else if (!builtincmp(cmd[0], "unset"))
		return (ft_unset(cmd, env), 1);
	else if (!builtincmp(cmd[0], "cd"))
		return (ft_cd(cmd, env), 1);
	else if (!builtincmp(cmd[0], "exit"))
		return (ft_exit(cmd), 1);
	else
		return (0);
}

void	execute(char **s, char **env)
{
	char	**path;

	if (!isbuiltin(s, env))
	{
		if (s[0][0] == '/' || s[0][0] == '.')
			path = s;
		else
			path = get_path(s[0], env);
		if (!path)
			return ;
		commands_execution(path, s, env);
	}
}
