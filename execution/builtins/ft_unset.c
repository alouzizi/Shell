/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 09:07:12 by ooumlil           #+#    #+#             */
/*   Updated: 2022/09/27 07:41:56 by ooumlil          ###   ########.fr       */
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

void	copy_after_unset(char **copy, int i)
{
	int	u;
	int	j;

	u = -1;
	j = 0;
	g_global.n_env = malloc(sizeof(char *) * arr_len(copy));
	while (copy[++u])
	{
		if (u != i)
		{
			g_global.n_env[j] = ft_strdup(copy[u]);
			j++;
		}
	}
	g_global.n_env[j] = 0;
}

// void	print_unset_error(char *arg)
// {
// 	ft_putstr_fd("minishell: unset: `", 2);
// 	ft_putstr_fd(arg, 2);
// 	ft_putendl_fd("': not a valid identifier", 2);
// 	g_global.status = 1;
// }

void	remove_from_env(char *cmd)
{
	char	**copy;
	int		i;

	i = -1;
	// if (cmd[0] == '_' && !cmd[1])
	// 	return ;
	// if (!ft_isalpha(cmd[0]))
	// {
	// 	puts("hh");
	// 	print_unset_error(cmd);
	// 	return ;
	// }
	// if (!check_var_name(cmd))
	// {
	// 	print_unset_error(cmd);
	// 	return ;
	// }
	copy = ft_arr_copy(g_global.n_env);
	while (g_global.n_env[++i])
	{
		if (!ft_strncmp(g_global.n_env[i], cmd, ft_strlen(cmd)))
		{	
			free_array(g_global.n_env);
			copy_after_unset(copy, i);
		}
	}
	free_array(copy);
}

// ft_unset with no args does nothing

void	ft_unset(char **cmd)
{
	int	i;

	i = 0;
	// g_global.status = 0;
	if (!cmd[1])
		return ;
	else
	{
		while (cmd[++i])
			remove_from_env(cmd[i]);
	}
}
