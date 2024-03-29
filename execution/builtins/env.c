/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:20:00 by ywadday           #+#    #+#             */
/*   Updated: 2022/12/18 03:20:23 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	shlvl_oldpwd(char **str)
{
	char	*tmp;

	if (!ft_strcmp(str[0], "SHLVL"))
	{
		tmp = ft_itoa(ft_atoi(str[1]));
		free(str[1]);
		str[1] = tmp;
	}
	if (ft_strcmp(str[0], "OLDPWD"))
		add_back(&g_global.g_env,
			new_node2(ft_strdup(str[0]), ft_strdup(str[1])));
}

void	addtolist(char **env)
{
	int		i;
	int		j;
	char	**str;

	i = -1;
	while (env[++i] != NULL)
	{
		if (env[i][ft_strlen(env[i]) - 1] == '=')
		{
			j = 0;
			while (env[i][j] && env[i][j] != '=')
				j++;
			env[i][j] = '\0';
			str[0] = ft_strdup(env[i]);
			str[1] = ft_strdup("");
		}
		else
			str = ft_split(env[i], '=');
		shlvl_oldpwd(str);
		free_array(str);
	}
}

void	parse_env(char **env)
{
	char	s[1024];
	char	*path;

	g_global.g_env = NULL;
	path = getcwd(s, 1024);
	if (!env || !*env)
	{
		add_var_to_env("PWD", path);
		add_var_to_env("SHLVL", "1");
		return ;
	}
	else
	{
		addtolist(env);
		if (!get_value_from_env("PWD"))
			add_var_to_env("PWD", path);
		if (!get_value_from_env("PWD"))
			add_var_to_env("SHLVL", "1");
		return ;
	}
}

void	print_env(void)
{
	t_env	*head;

	head = g_global.g_env;
	while (head)
	{
		if (head->value)
			printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
}
