/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 00:38:34 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/21 04:36:51 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	shlvl_reset(t_vars *v)
{
	char	*value;

	v->t = 1;
	value = ft_itoa(v->t);
	ft_putstr_fd("minishell: warning: shell level (", 2);
	ft_putstr_fd(value, 2);
	ft_putendl_fd(") too high, resetting to 1", 2);
	free(value);
}

// shlvl_handling : we enter this function
// only if SHLVL already exists, and we increment
// its value by +1 if its a number between 0 && 999
// if its not a number or its negative we set its value to 0
// if its higher than 999 it gets reseted to 1

void	shlvl_handling(t_vars *v)
{
	v->check = 1;
	v->tmp = ft_strdup("SHLVL=");
	v->s = ft_strchr(v->env[v->i], '=') + 1;
	if (!arg_isdigit(v->s))
	{
		free(v->env[v->i]);
		v->env[v->i] = ft_strjoin(v->tmp, "1", 1);
		return ;
	}	
	v->t = ft_atoi(v->s) + 1;
	if (v->t < 0)
		v->t = 0;
	else if (v->t == 1000)
	{
		free(v->env[v->i]);
		v->env[v->i] = ft_strjoin(v->tmp, "", 1);
		return ;
	}
	else if (v->t > 1000)
		shlvl_reset(v);
	v->s = ft_itoa(v->t);
	free(v->env[v->i]);
	v->env[v->i] = ft_strjoin(v->tmp, v->s, 3);
}

// ft_update_env takes the 3rd variable 
// in the main and allocates each line
// in the array, we also check the existence
// of SHLVL, if it doesnt exist we add it
// and set it to 1

void	ft_update_env(char **env, t_vars *v)
{
	char	*name;

	v->check = 0;
	name = 0;
	v->env = ft_arr_copy(env);
	v->i = -1;
	while (v->env[++v->i])
	{
		name = get_name(v->env[v->i], '=');
		if (!ft_strcmp("SHLVL", name))
			shlvl_handling(v);
		free(name);
	}
	v->i = arr_len(v->env);
	if (!v->check)
	{
		v->env[v->i] = ft_strdup("SHLVL=1");
		v->env[v->i + 1] = 0;
	}
}

// ft_env prints the variables that have value
// and ignores the rest

void	ft_env(char **env)
{
	int	i;

	if (!env)
		return ;
	i = -1;
	while (env[++i])
		if (ft_strchr(env[i], '='))
			ft_putendl_fd(env[i], 1);
	g_global.status = 0;
}
