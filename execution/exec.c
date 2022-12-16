/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 12:14:09 by ooumlil           #+#    #+#             */
/*   Updated: 2022/12/16 17:21:58 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static int	lstsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
char	**new_env(void)
{
	int		size;
	char	**env;
	t_env	*head;
	char	*shlvl;
	int		i;

	size = lstsize(g_global.g_env) + 1;
	env = (char **)malloc(sizeof(g_global.g_env) * size);
	if (!env)
		return (NULL);
	head = g_global.g_env;
	shlvl = get_value_from_env("SHLVL");
	if (!shlvl)
	{
		add_var_to_env("SHLVL", "1");
		shlvl = "1";
	}
	else
		shlvl = ft_itoa(ft_atoi(shlvl) + 1);
	i = 0;
	while (head)
	{
		if (!ft_strcmp(head->key, "SHLVL"))
			head->value = shlvl;
		if (head->value)
		{
			if (head->value[0] == '=')
				head->value = "";
			env[i] = ft_strjoin(ft_strjoin(head->key, "=", 0), head->value, 0);
			i++;
		}
		head = head->next;
	}
	env[i] = NULL;
	return (env);
}


int	commands_execution(char *path, char **cmd)
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
		
		if (execve(path, cmd, new_env()))
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
	// else if (!builtincmp(cmd[0], "exit"))
	// 	return (ft_exit(cmd), 1);
	else
		return (0);
}

int	execute(char **s)
{
	char	*path;

	if (isbuiltin(s))
		return (0);
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