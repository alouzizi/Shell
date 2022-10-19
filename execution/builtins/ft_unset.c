/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 09:07:12 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/19 00:05:32 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	free_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

// remove_from_env removes a var from env
// simply

char	**copy_after_unset(char **copy, int i)
{
	char	**env;
	int		u;
	int		j;

	u = -1;
	j = 0;
	env = malloc(sizeof(char *) * arr_len(copy));
	while (copy[++u])
	{
		if (u != i)
		{
			env[j] = ft_strdup(copy[u]);
			j++;
		}
	}
	env[j] = 0;
	return (env);
}

void	print_unset_error(char *arg)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	g_global.status = 1;
}

int	remove_from_env(char *cmd, t_vars *v)
{
	char	**copy;
	char	*name;
	int		i;

	i = -1;
	if (cmd[0] == '_' && !cmd[1])
		return (0);
	if (!ft_isalpha(cmd[0]) || !check_var_name(cmd))
		return (print_unset_error(cmd), 1);
	while (v->env[++i])
	{
		name = get_name(v->env[i], '=');
		if (!ft_strcmp(name, cmd))
		{
			copy = ft_arr_copy(v->env);
			free_array(v->env);
			v->env = copy_after_unset(copy, i);
			free(name);
			free_array(copy);
			break ;
		}
		free(name);
	}
	return (0);
}

// ft_unset with no args does nothing

void	ft_unset(char **cmd, t_vars *v)
{
	int	i;

	i = 0;
	g_global.status = 0;
	if (!cmd[1])
		return ;
	else
	{
		while (cmd[++i])
			remove_from_env(cmd[i], v);
	}
}
