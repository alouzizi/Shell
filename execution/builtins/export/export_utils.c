/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 23:38:41 by ooumlil           #+#    #+#             */
/*   Updated: 2022/09/15 02:00:24 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

// same as ft_isalnum but include '_'

int	ft_isalnum_export(int c)
{
	if (((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		|| ((c >= '0') && (c <= '9')) || c == '_')
		return (1);
	return (0);
}

// print_export_error self-explanatory

void	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	g_global.status = 1;
}

// checks the whole name for imposter chars
// anything other than numbers letters and _

int	check_var_name(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isalnum_export(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

// self-explanatory

void	update_or_add_var(int b, int ptr, char *var, char **env)
{
	if (b)
		env[ptr] = ft_strdup(var);
	else
		add_var_to_env(var, env);
}

// prints env arr value sorted with some extra stuff 

void	print_export(char **copy)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	sort_array_alphabetically(copy);
	while (copy[++i])
	{
		j = 0;
		n = 0;
		ft_putstr_fd("declare -x ", 1);
		while (copy[i][j])
		{
			ft_putchar_fd(copy[i][j], 1);
			if (copy[i][j] == '=' && n == 0)
			{
				ft_putchar_fd('\"', 1);
				n++;
			}
			if (!copy[i][j + 1] && n != 0)
				ft_putchar_fd('\"', 1);
			j++;
		}
		ft_putchar_fd('\n', 1);
	}
}
