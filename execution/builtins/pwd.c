/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:59:31 by ywadday           #+#    #+#             */
/*   Updated: 2022/12/16 14:21:43 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_value_from_env(char *var)
{
	t_env	*head;

	head = g_global.g_env;
	while (head)
	{
		if (!ft_strcmp(head->key, var))
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

void	pwd(void)
{
	char	*pwd;
	char	s[1024];

	pwd = get_value_from_env("PWD");
	if (!pwd)
	{
		getcwd(s, 1024);
		pwd = ft_strdup(s);
		add_var_to_env("PWD", pwd);
	}
	printf("%s\n", pwd);
}
