/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 05:20:03 by ooumlil           #+#    #+#             */
/*   Updated: 2022/11/02 19:48:34 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

// should i even explain

int	arr_len(char **arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

// checks if its a variable that has value or not
// and returns the index where the value starts

void	has_value(char *arg, t_exp *ex)
{
	ex->index = 0;
	while (arg[ex->index] != '=')
		ex->index++;
	if (arg[ex->index] == '=')
		ex->ptr = 0;
}

// if b is true the variable exists in the env
// so it only updates it
// if b is false it adds it to the env array

void	update_or_add_var(t_exp *ex, char *var, t_vars *v)
{
	if (ex->b)
	{
		free(v->env[ex->ptr]);
		free(var);
		v->env[ex->ptr] = ft_strdup(var);
	}
	else
		add_var_to_env(var, v);
}
