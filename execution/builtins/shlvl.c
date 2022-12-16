/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 01:39:59 by ywadday           #+#    #+#             */
/*   Updated: 2022/12/16 14:21:51 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	lstsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

char	**new_env(void)
{
	int		size;
	char	**env;
	t_env	*head;
	char	*shlvl;
	int		i;

	size = lstsize(g_global.g_env) + 1;
	env = (char **)malloc(sizeof(g_global.g_env) * size);
	if (!env)
		return (NULL);
	garbage(env);
	head = g_global.g_env;
	shlvl = get_value_from_env("SHLVL");
	if (!shlvl)
	{
		add_var_to_env("SHLVL", "1");
		shlvl = "1";
	}
	else
		shlvl = ft_itoa(ft_atoi(shlvl) + 1);
	i = 0;
	while (head)
	{
		if (!ft_strcmp(head->key, "SHLVL"))
			head->value = shlvl;
		if (head->value)
		{
			if (head->value[0] == '=')
				head->value = "";
			env[i] = ft_strjoin(ft_strjoin(head->key, "=", 0), head->value, 0);
			i++;
		}
		head = head->next;
	}
	env[i] = NULL;
	return (env);
}
