/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:11:06 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/16 10:25:57 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

// ft_arr_copy copies an array in another one CTL^C CTL^V :)

char	**ft_arr_copy(char **arr)
{
	char	**copy;
	int		i;

	i = 0;
	copy = (char **)malloc(sizeof(char *) * (arr_len(arr) + 1));
	if (!copy)
		return (NULL);
	while (arr[i])
	{
		copy[i] = ft_strdup(arr[i]);
		i++;
	}
	copy[i] = 0;
	return (copy);
}

char	**copy_to_env(char **arr, int arr_size)
{
	char	**env;
	int		i;

	i = 0;
	env = (char **)malloc(sizeof(char *) * (arr_size + 1));
	if (!env)
		return (NULL);
	while (arr[i])
	{
		env[i] = ft_strdup(arr[i]);
		i++;
	}
	env[i] = 0;
	return (env);
}

// directly adds the var to the env arr

void	add_var_to_env(char *var, char **env)
{
	int		arr_size;
	char	**copy;

	arr_size = arr_len(env);
	copy = ft_arr_copy(env);
	free_array(env);
	env = copy_to_env(copy, arr_size);
	if (!env)
		return ;
	env[arr_size] = ft_strdup(var);
	env[arr_size + 1] = 0;
	free_array(copy);
}

// add_variable checks for the existence of the name in the arr.
// In case of its existence, its ignored. If it isnt in the env
// arr its added

int	add_variable(char *arg, char **env)
{
	char	*name;
	int		i;

	i = -1;
	while (env[++i])
	{	
		name = get_name(env[i], '=');
		if (!ft_strcmp(arg, name))
			return (free(name), 1);
		free(name);
	}
	add_var_to_env(arg, env);
	return (0);
}

char	*get_name(char *s, int c)
{
	char	*r;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s) - ft_strlen(ft_strchr(s, c));
	r = (char *)malloc(sizeof(char) * (len + 1));
	if (!r)
		return (NULL);
	while (len--)
	{
		r[i] = s[i];
		i++;
	}
	r[i] = 0;
	return (r);
}
