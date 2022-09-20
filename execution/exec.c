/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 12:14:09 by ooumlil           #+#    #+#             */
/*   Updated: 2022/09/20 20:55:31 by ooumlil          ###   ########.fr       */
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

char	*check_access(char	**paths)
{
	char	*path;
	int		i;

	i = 0;
	while (paths[i])
	{
		if (!access(paths[i], X_OK | F_OK))
		{
			path = paths[i];
			break ;
		}
		i++;
	}
	if (!path)
		return (NULL);
	return (path);
}

void	print_cnf_error(char *cmd)
{
	ft_putstr_fd(PRMPT_ERR, 2);
	ft_putstr_fd(CNF, 2);
	ft_putendl_fd(cmd, 2);
	exit(127);
}

void	commands_execution(char **paths, char **cmd, char **env)
{
	char	*path;
	int		fd;
	int		status;

	path = check_access(paths);
	fd = fork();
	if (!fd)
	{
		if (path)
		{
			execve(path, cmd, env);
			exit (0);
		}
		else
			print_cnf_error(cmd[0]);
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
	char	**paths;

	if (!isbuiltin(s, env))
	{
		if (s[0][0] == '/' || s[0][0] == '.')
			paths = s;
		else
			paths = get_path(s[0], env);
		if (!paths)
			return ;
		commands_execution(paths, s, env);
	}
}
