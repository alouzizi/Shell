/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:11:06 by ooumlil           #+#    #+#             */
/*   Updated: 2022/09/24 08:47:16 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

// self-explanatory

void	update_or_add_var(int b, int ptr, char *var, char **env)
{
	if (b)
		env[ptr] = ft_strdup(var);
	else
		add_var_to_env(var, env);
}

// directly adds the var to the env arr

void	add_var_to_env(char *var, char **env)
{
	int	arr_size;

	arr_size = arr_len(env);
	env[arr_size] = ft_strdup(var);
	env[arr_size + 1] = NULL;
}

// add_variable checks for the existence of the name in the arr.
// In case of its existence, its ignored. If it isnt in the env
// arr its added

void	add_variable(char *arg, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(arg, env[i], ft_strlen(arg)))
			return ;
	}
	add_var_to_env(arg, env);
}
