/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 12:14:09 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/30 18:50:52 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

void	print_cnf_error(char *cmd)
{
	ft_putstr_fd(PRMPT_ERR, 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(CNF, 2);
	g_global.status = 127;
}

int	commands_execution(char *path, char **cmd, t_vars *v)
{
	int		fd;
	int		status;

	status = 0;
	if (!path)
	{
		print_cnf_error(cmd[0]);
		return (127);
	}
	fd = fork();
	if (!fd)
	{
		if (execve(path, cmd, v->env))
			print_cnf_error(cmd[0]);
	}
	else
	{
		g_global.signal = 1;
		waitpid(fd, &status, 0);
	}
	free(path);
	exit_status(status);
	return (0);
}

// checks if its one of the cmds asked in the subject
// and executes it or else executes it with execve func

int	isbuiltin(char **cmd, t_vars *v)
{
	if (!cmd[0])
		return (1);
	else if (!builtincmp(cmd[0], "pwd"))
		return (ft_pwd(), 1);
	else if (!builtincmp(cmd[0], "echo"))
		return (ft_echo(cmd), 1);
	else if (!builtincmp(cmd[0], "env"))
		return (ft_env(v->env), 1);
	else if (!builtincmp(cmd[0], "export"))
		return (ft_export(cmd, v), 1);
	else if (!builtincmp(cmd[0], "unset"))
		return (ft_unset(cmd, v), 1);
	else if (!builtincmp(cmd[0], "cd"))
		return (ft_cd(cmd, v), 1);
	else if (!builtincmp(cmd[0], "exit"))
		return (ft_exit(cmd), 1);
	else
		return (0);
}

int	execute(char **s, t_vars *v)
{
	char	*path;

	if (isbuiltin(s, v))
		return (0);
	if (s[0][0] == '.' || s[0][0] == '/')
		path = check_absolute_path(s[0]);
	else
		path = check_access(get_path(s[0], v), -1);
	if (!path)
		return (print_cnf_error(s[0]), 127);
	if (commands_execution(path, s, v))
		return (127);
	return (0);
}
