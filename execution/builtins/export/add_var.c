/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:11:06 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/19 09:40:10 by ooumlil          ###   ########.fr       */
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

// returns a new allocated array with an extra block for
// the variable we want to add

char	**copy_to_env(char **arr, int arr_size)
{
	char	**env;
	int		i;

	i = 0;
	env = (char **)malloc(sizeof(char *) * (arr_size + 2));
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

void	add_var_to_env(char *var, t_vars *v)
{
	int		arr_size;
	char	**copy;

	arr_size = arr_len(v->env);
	copy = ft_arr_copy(v->env);
	free_array(v->env);
	v->env = copy_to_env(copy, arr_size);
	v->env[arr_size] = ft_strdup(var);
	v->env[arr_size + 1] = 0;
	// free(var);
	free_array(copy);
}

// get_name : gets the name of a variable in the env
// example : HOME=/Users/ooumlil 
// this function returns in this case HOME only

char	*get_name(char *s, int c)
{
	char	*r;
	int		i;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s) - ft_strlen(ft_strchr(s, c));
	r = (char *)malloc(sizeof(char) * (len + 1));
	if (!r)
		return (NULL);
	i = 0;
	while (len--)
	{
		r[i] = s[i];
		i++;
	}
	r[i] = 0;
	return (r);
}

// add_variable checks for the existence of the name in the arr.
// In case of its existence, its ignored. If it isnt in the env
// arr its added

int	add_variable(char *arg, t_vars *v, t_exp *ex)
{
	char	*name;

	ex->check = 1;
	ex->i = -1;
	while (v->env[++ex->i])
	{	
		name = get_name(v->env[ex->i], '=');
		if (name && !ft_strcmp(arg, name))
			return (free(name), 1);
		free(name);
	}
	add_var_to_env(arg, v);
	return (0);
}
