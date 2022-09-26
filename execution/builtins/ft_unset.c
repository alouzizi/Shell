/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 09:07:12 by ooumlil           #+#    #+#             */
/*   Updated: 2022/09/26 05:32:23 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

// void	arr_free(char **arr)
// {
// 	int	i;

// 	i = -1;
// 	while (arr[++i])
// 		free(arr[i]);
// 	free(arr);
// }

// char	**my_realloc(char **env)
// {
// 	int		len;
// 	char	**new_env;

// 	len = arr_len(env);
// }

// remove_from_env removes a var from env
// simply

void	remove_from_env(char *cmd)
{
	int	i;

	i = -1;
	while (g_global.n_env[++i])
		if (!ft_strncmp(g_global.n_env[i], cmd, ft_strlen(cmd)))
			g_global.n_env[i] = ft_strdup("");
}

// ft_unset with no args does nothing

void	ft_unset(char **cmd)
{
	int	i;

	i = 0;
	if (!cmd[1])
		return ;
	else
	{
		while (cmd[++i])
			remove_from_env(cmd[i]);
	}
}
