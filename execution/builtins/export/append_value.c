/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 00:15:47 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/20 01:18:36 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

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

//literally what its named

void	append_to_existing_var(t_vars *v, t_exp *ex)
{
	ex->ptr = 1;
	if (ex->arg_value && !ft_strchr(v->env[ex->i], '='))
	{
		v->env[ex->i] = ft_strjoin(v->env[ex->i],
				ft_strjoin(ft_strdup("="), ex->arg_value, 3), 3);
	}
	else if (ex->arg_value)
		v->env[ex->i] = ft_strjoin(v->env[ex->i], ex->arg_value, 3);
}

// add_to_value as the name suggests it adds the value
// to the the already existing variable in the end,
// in case the variable isnt in the array it adds it

void	add_to_value(char *arg, t_exp *ex, t_vars *v)
{
	ex->var_name = 0;
	ex->arg_name = get_name(arg, '+');
	ex->arg_value = ft_strchr(arg, '=') + 1;
	ex->ptr = 0;
	has_value(arg, ex);
	ex->i = -1;
	while (v->env[++ex->i])
	{
		ex->var_name = get_name(v->env[ex->i], '=');
		if (!ft_strcmp(ex->arg_name, ex->var_name) && !ex->ptr)
			append_to_existing_var(v, ex);
		free(ex->var_name);
	}
	if (!ex->ptr)
	{
		arg = ft_strjoin(get_name(arg, '+'),
				ft_strjoin(ft_strdup("="), ex->arg_value, 3), 3);
		add_var_to_env(arg, v);
	}
	free(ex->arg_name);
}
