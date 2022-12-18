/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 01:50:28 by mfagri            #+#    #+#             */
/*   Updated: 2022/12/17 22:27:05 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//checks if its one of the cmds asked in the subject
//and executes it or else executes it with execve func

int	isbuiltin(char **cmd)
{
	if (!cmd[0])
		return (1);
	else if (!builtincmp(cmd[0], "pwd"))
		return (pwd(), 1);
	else if (!builtincmp(cmd[0], "echo"))
		return (echo(cmd), 1);
	else if (!builtincmp(cmd[0], "env"))
		return (print_env(), 1);
	else if (!builtincmp(cmd[0], "export"))
		return (export(cmd), 1);
	else if (!builtincmp(cmd[0], "unset"))
		return (unset(cmd), 1);
	else if (!builtincmp(cmd[0], "cd"))
		return (cd(cmd[1]), 1);
	else if (!builtincmp(cmd[0], "exit"))
		return (exitt(cmd), 1);
	else
		return (0);
}

int	execute(char **s)
{
	char	*path;

	if (isbuiltin(s))
	{
		g_global.status = 0;
		return (0);
	}
	if (s[0][0] == '.' || s[0][0] == '/')
		path = check_absolute_path(s[0]);
	else
		path = check_access(get_path(s[0]), -1);
	if (!path)
		return (print_cnf_error(s[0]), 127);
	if (commands_execution(path, s))
		return (127);
	return (0);
}

int	arr_len(char **arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
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
