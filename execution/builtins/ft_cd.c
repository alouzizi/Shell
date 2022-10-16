/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:52:24 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/16 13:02:12 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

// returns the value of a variable from the env array
// i. e. the given str is "HOME"
// it returns its value which is for our situation is 
// /Users/(your_login)
// example for 42 students

char	*get_env(char *str, t_vars *v)
{
	int	i;

	i = -1;
	str = ft_strjoin(str, ft_strdup("="), 2);
	while (v->env[++i])
	{
		if (!ft_strncmp(str, v->env[i], ft_strlen(str)))
			return (free(str), &v->env[i][ft_strlen(str)]);
	}
	return (free(str), NULL);
}

// cd error printing

void	cd_error_printing(char *arg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	perror(arg);
	g_global.status = 1;
}

// ft_cd changes the current directory to the one in the argument
// if it got no arguments it goes directly the value in HOME env var

void	ft_cd(char **cmd, t_vars *v)
{
	char	*home;

	home = get_env("HOME", v);
	if (!cmd[1])
	{
		if (!home)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			g_global.status = 1;
			return ;
		}
		if (chdir(home))
			cd_error_printing(home);
	}
	else
	{
		if (chdir(cmd[1]))
			cd_error_printing(cmd[1]);
	}
}
