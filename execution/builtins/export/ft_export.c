/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:36:25 by ooumlil           #+#    #+#             */
/*   Updated: 2022/09/20 20:38:42 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

// add_to_value as the name suggests it adds the value
// to the the already existing variable in the end,
// in case the variable isnt in the array it adds it

void	add_to_value(char *arg, char **env, int i, int ptr)
{
	int		index;
	char	*value;

	index = has_value(arg, &ptr);
	value = ft_strchr(arg, '=') + 1;
	while (env[++i])
	{
		if (!ft_strncmp(arg, env[i], index - 1) && ptr == -1)
		{
			ptr = 1;
			if (value && !ft_strchr(env[i], '='))
				env[i] = ft_strjoin(env[i], ft_strjoin("=", value));
			else
				env[i] = ft_strjoin(env[i], value);
		}
	}
	i = index - 2;
	if (arg[i] == '+')
		i--;
	if (!ptr || ptr == -1)
	{
		arg = ft_strjoin(ft_substr(arg, 0, i + 1), \
			ft_strjoin(ft_strdup("="), value));
		add_var_to_env(arg, env);
	}
}

// add_to_env after some error checking ,
// it checks for the existence of the variable,
// if it exists it updates the value of the variable
// if it doesnt it simply adds it to the env arr 

void	add_to_env(char *var, char **env)
{
	int	i;
	int	index;
	int	b;
	int	ptr;

	index = -1;
	while (var[++index] != '=')
	{
		if (!ft_isalnum_export(var[index]))
		{
			print_export_error(var);
			return ;
		}
	}
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(var, env[i], index))
		{
			b = 1;
			ptr = i;
		}
	}
	update_or_add_var(b, ptr, var, env);
}

// check_arg_export checks whether to add to a variable
// already existing or add one simply

int	check_arg_export(char *arg, int i, char **env)
{
	if (arg[i] == '=')
		return (add_to_env(arg, env), 1);
	else if (arg[i] == '+' && arg[i + 1] == '=')
		return (add_to_value(arg, env, -1, 0), 1);
	return (0);
}

// add_to_export adds argument to env arr if it passes
// some conditions, like 1st letter must be '_' or a 
// character uppercase or lower case if its something else
// returns an error and the name of the var must be alphanumeric
// with '_' included
// in case of error it exits with specified error

void	add_to_export(char **env, char *arg)
{
	int	i;
	int	check;

	i = 0;
	if (arg[i] == '_' && arg[i + 1] == '=')
		return ;
	if (!ft_isalpha(arg[0]))
	{
		print_export_error(arg);
		return ;
	}
	if (check_var_name(arg))
	{
		check = 1;
		add_variable(arg, env);
		return ;
	}
	while (arg[i] && arg[i] != '=' && arg[i] != '+')
	{
		i++;
		check = check_arg_export(arg, i, env);
	}
	if (!check)
		print_export_error(arg);
}

// ft_export with no args prints the env vars sorted
// alphabetically else checks the arg and adds it to
// the env array

void	ft_export(char **cmd, char **env)
{
	char	**copy;
	int		i;

	i = 0;
	if (!cmd[1])
	{
		copy = ft_arr_copy(env);
		print_export(copy);
	}
	else
		while (cmd[++i])
			add_to_export(env, cmd[i]);
}
