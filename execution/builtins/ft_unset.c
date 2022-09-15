/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 09:07:12 by ooumlil           #+#    #+#             */
/*   Updated: 2022/09/15 02:01:03 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

// remove_from_env removes a var from env
// simply

void	remove_from_env(char **cmd, char **env)
{
	int	i;
	int	j;

	i = -1;
	j = 1;
	while (env[++i] && cmd[j])
	{
		if (!ft_strncmp(env[i], cmd[j], ft_strlen(cmd[j])))
		{
			env[i] = ft_strdup("");
			j++;
		}
	}
}

// ft_unset with no args does nothing

void	ft_unset(char **cmd, char **env)
{
	if (!cmd[1])
		return ;
	else
		remove_from_env(cmd, env);
}
