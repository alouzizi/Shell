/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 00:38:34 by ooumlil           #+#    #+#             */
/*   Updated: 2022/09/15 04:34:07 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

// shlvl_handling : we enter this function
// only if SHLVL already exists, and we increment
// its value by +1 if its a number between 0 && 999
// if its not a number or its negative we set its value to 0
// if its higher than 999 it gets reseted to 1

void	shlvl_handling(char **env, int i)
{
	char	*tmp;
	char	*s;
	int		t;

	tmp = ft_strdup("SHLVL=");
	s = ft_strrchr(env[i], '=');
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
	env[i] = ft_strjoin(tmp, s);
}

// ft_update_env takes the 3rd variable 
// in the main and allocates each line
// in the array, we also check the existence
// of SHLVL, if it doesnt exist we add it
// and set it to 1

void	ft_update_env(char **env)
{
	int	i;
	int	check;

	check = 0;
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp("SHLVL=", env[i], ft_strlen("SHLVL=")))
		{
			check = 1;
			shlvl_handling(env, i);
		}
		else
			env[i] = ft_strdup(env[i]);
	}
	if (!check)
		env[i] = ft_strdup("SHLVL=1");
	env[i + 1] = NULL;
}

// ft_env prints the variables that have value
// and ignores the rest

// After executing "env" cmd we set exit status
// value to 0

void	ft_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (ft_strchr(env[i], '='))
			ft_putendl_fd(env[i], 1);
	g_global.status = 0;
}
