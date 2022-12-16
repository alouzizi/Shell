/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 18:56:09 by ywadday           #+#    #+#             */
/*   Updated: 2022/12/16 14:21:54 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_from_middle(char *key)
{
	t_env	*head;
	t_env	*tmp;

	head = g_global.g_env;
	while (head)
	{
		if (head->next && !ft_strcmp(head->next->key, key))
		{
			tmp = head->next;
			head->next = head->next->next;
			free(tmp);
		}
		head = head->next;
	}
}

void	unset(char **var)
{
	t_env	*tmp;
	int		i;

	i = 0;
	while (var[++i])
	{
		if (!ft_strcmp(g_global.g_env->key, var[i]))
		{
			tmp = g_global.g_env;
			g_global.g_env = g_global.g_env->next;
			free(tmp);
		}
		else
			remove_from_middle(var[i]);
	}
}
