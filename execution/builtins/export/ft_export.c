/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:36:25 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/19 09:42:35 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

// add_to_value as the name suggests it adds the value
// to the the already existing variable in the end,
// in case the variable isnt in the array it adds it

void	add_to_value(char *arg, t_exp *ex, t_vars *v)
{
	char	*value;

	has_value(arg, ex);
	value = ft_strchr(arg, '=') + 1;
	while (v->env[++ex->i])
	{
		if (!ft_strncmp(arg, v->env[ex->i], ex->index - 1) && ex->ptr == -1)
		{
			ex->ptr = 1;
			if (value && !ft_strchr(v->env[ex->i], '='))
				v->env[ex->i] = ft_strjoin(v->env[ex->i],
						ft_strjoin("=", value, 0), 1);
			else
				v->env[ex->i] = ft_strjoin(v->env[ex->i], value, 1);
		}
	}
	ex->i = ex->index - 2;
	if (arg[ex->i] == '+')
		ex->i--;
	if (!ex->ptr || ex->ptr == -1)
	{
		arg = ft_strjoin(ft_strchr(arg, '=') + 1,
			ft_strjoin(ft_strdup("="), value, 3), 3);
		add_var_to_env(arg, v);
	}
}

// add_to_env after some error checking ,
// it checks for the existence of the variable,
// if it exists it updates the value of the variable
// if it doesnt it simply adds it to the env arr 

int	add_to_env(char *var, t_exp *ex, t_vars *v)
{
	ex->index = -1;
	while (var[++ex->index] != '=')
	{
		if (!ft_isalnum_export(var[ex->index]))
			return (print_export_error(var), 1);
	}
	ex->i = -1;
	while (v->env[++ex->i])
	{
		if (!ft_strncmp(var, v->env[ex->i], ex->index))
		{
			
			ex->b = 1;
			ex->ptr = ex->i;
		}
	}
	update_or_add_var(ex, var, v);
	return (0);
}

// check_arg_export checks whether to add to a variable
// already existing or add one simply

int	check_arg_export(char *arg, t_vars *v, t_exp *ex)
{
	if (arg[ex->i] == '=')
		return (add_to_env(arg, ex, v), 1);
	else if (arg[ex->i] == '+' && arg[ex->i + 1] == '=')
		return (add_to_value(arg, ex, v), 1);
	return (0);
}

// add_to_export adds argument to env arr if it passes
// some conditions, like 1st letter must be '_' or a 
// character uppercase or lower case if its something else
// returns an error and the name of the var must be alphanumeric
// with '_' included
// in case of error it exits with specified error

// void	puts_env(char **env)
// {
// 	for (size_t z = 0; env[z]; z++)
// 		ft_putendl_fd(env[z], 1);
// }

int	add_to_export(char *arg, t_vars *v)
{
	t_exp	exp;

	exp.i = 0;
	exp.check = 0;
	if (arg[exp.i] == '_' && arg[exp.i + 1] == '=')
		return (0);
	if (!ft_isalpha(arg[exp.i]) && arg[exp.i] != '_')
		return (print_export_error(arg), 1);
	if (check_var_name(arg))
		return (add_variable(arg, v, &exp), 0);
	while (arg[exp.i] && arg[exp.i] != '=' && arg[exp.i] != '+')
	{
		exp.i++;
		exp.check = check_arg_export(arg, v, &exp);
	}
	if (!exp.check)
		return (print_export_error(arg), 1);
	return (0);
}

// ft_export with no args prints the env vars sorted
// alphabetically else checks the arg and adds it to
// the env array

void	ft_export(char **cmd, t_vars *v)
{
	char	**copy;
	int		i;

	i = 0;
	if (!cmd[1])
	{
		copy = ft_arr_copy(v->env);
		sort_array_alphabetically(copy, 0, 0);
		print_export(copy, -1, 0);
		free_array(copy);
	}
	else
		while (cmd[++i])
			add_to_export(cmd[i], v);
}
