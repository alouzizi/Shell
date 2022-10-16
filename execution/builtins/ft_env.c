/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 00:38:34 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/16 12:56:44 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

// shlvl_handling : we enter this function
// only if SHLVL already exists, and we increment
// its value by +1 if its a number between 0 && 999
// if its not a number or its negative we set its value to 0
// if its higher than 999 it gets reseted to 1

void	shlvl_handling(int i, char **arr)
{
	char	*tmp;
	char	*s;
	int		t;
	char	*tvalue;

	tmp = ft_strdup("SHLVL=");
	s = ft_strrchr(arr[i], '=');
	++s;
	t = ft_atoi(s) + 1;
	if (t < 0)
		t = 0;
	else if (t > 1000)
	{
		tvalue = ft_itoa(t);
		ft_putstr_fd("minishell: warning: shell level (", 2);
		ft_putstr_fd(tvalue, 2);
		ft_putendl_fd(") too high, resetting to 1", 2);
		free(tvalue);
		t = 1;
		g_global.status = 1;
	}
	s = ft_itoa(t);
	arr[i] = ft_strjoin(tmp, s, 3);
}

// ft_update_env takes the 3rd variable 
// in the main and allocates each line
// in the array, we also check the existence
// of SHLVL, if it doesnt exist we add it
// and set it to 1

char	**ft_update_env(char **env)
{
	int		i;
	int		check;
	char	**arr;

	check = 0;
	i = -1;
	arr = ft_arr_copy(env);
	while (arr[++i])
	{
		if (!ft_strcmp("SHLVL", arr[i]))
		{
			check = 1;
			shlvl_handling(i, arr);
		}
	}
	// if (!check)
	// 	arr[i] = ft_strdup("SHLVL=1");
	// // arr[i + 1] = 0;
	return (arr);
}

// ft_env prints the variables that have value
// and ignores the rest

void	ft_env(char **env)
{
	int	i;

	i = -1;
	if (!env)
		return ;
	while (env[++i])
		if (ft_strchr(env[i], '='))
			ft_putendl_fd(env[i], 1);
	g_global.status = 0;
}
