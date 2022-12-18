/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 12:14:09 by ooumlil           #+#    #+#             */
/*   Updated: 2022/12/18 02:42:12 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	**envv(char *shlvl)
{
	int		i;
	int		size;
	char	**env;
	t_env	*head;

	head = g_global.g_env;
	i = 0;
	size = lstsize(g_global.g_env) + 1;
	env = (char **)malloc(sizeof(g_global.g_env) * size);
	if (!env)
		return (NULL);
	while (head)
	{
		if (!ft_strcmp(head->key, "SHLVL"))
			head->value = ft_itoa(ft_atoi(shlvl) + 1);
		env[i] = ft_strjoin(ft_strjoin(head->key, "=", 0), head->value, 0);
		i++;
		head = head->next;
	}
	env[i] = NULL;
	return (env);
}

char	**new_env(void)
{
	char	*shlvl;

	shlvl = "1";
	if (!get_value_from_env("SHLVL"))
		add_var_to_env("SHLVL", shlvl);
	else
		shlvl = get_value_from_env("SHLVL");
	return (envv(shlvl));
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
