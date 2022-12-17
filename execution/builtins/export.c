/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 16:54:48 by ywadday           #+#    #+#             */
/*   Updated: 2022/12/17 01:55:40 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_export(void)
{
	t_env	*head;

	head = g_global.g_env;
	while (head != NULL)
	{
		printf("declare -x ");
		if (head->value)
			printf("%s=\"%s\"\n", head->key, head->value);
		else
			printf("%s\n", head->key);
		head = head->next;
	}
}

void	modify_if_exist(char *key, char *value, int *b, int *b2)
{
	t_env	*head;

	head = g_global.g_env;
	while (head)
	{
		if (!ft_strcmp(head->key, key))
		{
			if (*b == 1)
			{
				head->value = ft_strjoin(head->value, value, 2);
				*b = 0;
			}
			else
				head->value = ft_strdup(value);
			*b2 = 1;
			break ;
		}
		head = head->next;
	}
}

void	add_var_to_env(char *key, char *value)
{
	t_env	*tmp;
	int		b;
	int		b2;

	b = 0;
	b2 = 0;
	if (key[ft_strlen(key) - 1] == '+')
	{
		key[ft_strlen(key) - 1] = '\0';
		b = 1;
	}
	if (value)
		modify_if_exist(key, value, &b, &b2);
	if (b2 == 0 && b == 0)
	{
		tmp = new_node2(key, value);
		add_back(&g_global.g_env, tmp);
	}
}

void	export(char **key_value)
{
	t_export_shit	x;

	x.i = 0;
	if (!key_value[1])
	{
		print_export();
		return ;
	}
	while (key_value[++x.i])
	{
		x.j = 0;
		if (!ony_chars(key_value[x.i][0]))
		{
			printf("export: `%s': not a valid identifier\n", key_value[x.i]);
			continue ;
		}
		while (key_value[x.i][x.j] && key_value[x.i][x.j] != '=')
			x.j++;
		x.key = ft_substr(key_value[x.i], 0, x.j);
		if (key_value[x.i][ft_strlen(key_value[x.i]) - 1] == '=')
			x.v = ft_strdup("");
		else if (x.j == (int)ft_strlen(key_value[x.i]))
			x.v = NULL;
		else
			x.v = ft_substr(key_value[x.i], x.j + 1, ft_strlen(key_value[x.i]));
		add_var_to_env(x.key, x.v);
	}
}

t_env	*new_node2(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->value = value;
	new->key = key;
	new->next = NULL;
	return (new);
}
