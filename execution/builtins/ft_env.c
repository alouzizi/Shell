/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 00:38:34 by ooumlil           #+#    #+#             */
/*   Updated: 2022/09/26 05:29:33 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

// shlvl_handling : we enter this function
// only if SHLVL already exists, and we increment
// its value by +1 if its a number between 0 && 999
// if its not a number or its negative we set its value to 0
// if its higher than 999 it gets reseted to 1

void	shlvl_handling(int i)
{
	char	*tmp;
	char	*s;
	int		t;

	tmp = ft_strdup("SHLVL=");
	s = ft_strrchr(g_global.n_env[i], '=');
	++s;
	t = ft_atoi(s) + 1;
	if (t < 0)
		t = 0;
	else if (t > 1000)
	{
		ft_putstr_fd("minishell: warning: shell level (", 2);
		ft_putstr_fd(ft_itoa(t), 2);
		ft_putendl_fd(") too high, resetting to 1", 2);
		t = 1;
	}
	s = ft_itoa(t);
	g_global.n_env[i] = ft_strjoin(tmp, s);
}

// ft_update_env takes the 3rd variable 
// in the main and allocates each line
// in the array, we also check the existence
// of SHLVL, if it doesnt exist we add it
// and set it to 1

void	ft_update_env(char **env)
{
	int		i;
	int		check;

	check = 0;
	i = -1;
	g_global.n_env = ft_arr_copy(env);
	while (g_global.n_env[++i])
	{
		if (!ft_strncmp("SHLVL=", g_global.n_env[i], ft_strlen("SHLVL=")))
		{
			check = 1;
			shlvl_handling(i);
		}
		else
			g_global.n_env[i] = ft_strdup(g_global.n_env[i]);
	}
	if (!check)
		g_global.n_env[i] = ft_strdup("SHLVL=1");
	g_global.n_env[i + 1] = 0;
}

// ft_env prints the variables that have value
// and ignores the rest

// After executing "env" cmd we set exit status
// value to 0

void	ft_env(void)
{
	int	i;

	i = -1;
	while (g_global.n_env[++i])
		if (ft_strchr(g_global.n_env[i], '='))
			ft_putendl_fd(g_global.n_env[i], 1);
	g_global.status = 0;
}
