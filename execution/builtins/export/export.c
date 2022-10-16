/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:11:06 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/16 03:10:57 by ooumlil          ###   ########.fr       */
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

void	copy_to_env(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		g_global.n_env[i] = ft_strdup(arr[i]);
		i++;
	}
	g_global.n_env[i] = 0;
}

// directly adds the var to the env arr

void	add_var_to_env(char *var)
{
	int		arr_size;
	char	**copy;

	arr_size = arr_len(g_global.n_env);
	copy = ft_arr_copy(g_global.n_env);
	// free_array(g_global.n_env);
	g_global.n_env = (char **)malloc(sizeof(char *) * (arr_size + 1));
	copy_to_env(copy);
	g_global.n_env[arr_size] = ft_strdup(var);
	g_global.n_env[arr_size + 1] = 0;
	free_array(copy);
}

// add_variable checks for the existence of the name in the arr.
// In case of its existence, its ignored. If it isnt in the env
// arr its added

int	add_variable(char *arg)
{
	int	i;

	i = -1;
	while (g_global.n_env[++i])
	{
		if (!ft_strncmp(arg, g_global.n_env[i], ft_strlen(arg)))
			// if (!ft_strncmp(arg, g_global.n_env[i], ft_strlen(g_global.n_env[i])))
				return (1);
	}
	add_var_to_env(arg);
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
