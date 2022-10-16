/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoutes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:48:36 by alouzizi          #+#    #+#             */
/*   Updated: 2022/09/09 14:48:36 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_node	*get_cmd(char *s, int *i, t_vars *v)
{
	t_node	*cmd;

	cmd = NULL;
	while (s[*i])
	{
		if (s[*i] == '"' || s[*i] == '\'')
			handle_quotes(&cmd, s, s[*i], i, v);
		else if (s[*i] != ' ')
		{
			if (s[*i] == '|' || s[*i] == '<' || s[*i] == '>' || s[*i] == '&')
				return (cmd);
			if (normall_collect(&cmd, s, i, v) == 1)
				return (cmd);
		}
		while (s[*i] && s[*i] == ' ')
			(*i)++;
	}
	return (cmd);
}

void	handle_quotes(t_node **cmd, char *s, char c, int *i, t_vars *v)
{
	t_node	*node;
	t_node	*list;
	int		start;
	int		end;

	list = NULL;
	(*i)++;
	start = *i;
	while (s[*i] != c && s[*i])
		(*i)++;
	end = (*i) - 1;
	if (s[*i] == '"')
	{
		node = ft_lstnew(NULL);
		node->s = expand_dollar(s, start, 0, c, v);
	}
	else
		node = create_node(s, start, end);
	(*i) += 1;
	if ((s[*i] == '\'' || s[*i] == '"') && s[*i])
	{
		handle_quotes(&list, s, s[*i], i, v);
		node->s = ft_strjoin(node->s, list->s, 3);
	}
	if (s[*i] != ' ' && s[*i])
	{
		normall_collect(&list, s, i, v);
		node->s = ft_strjoin(node->s, list->s, 3);
	}
	ft_lstadd_back(cmd, node);
}

t_node	*create_node(char *str, int start, int end)
{
	t_node	*node;
	int		i;

	i = 0;
	node = malloc(sizeof(t_node));
	if (!node)
		exit(1);
	node->next = NULL;
	node->s = malloc(sizeof(char) * (end - start + 1));
	if (!node->s)
		exit(1);
	while (start <= end)
		node->s[i++] = str[start++];
	node->s[i] = 0;
	return (node);
}

char	**transfer_list_to_2darray(t_node *node)
{
	char	**tab;
	int		i;

	i = ft_lstsize(node) + 1;
	tab = malloc(sizeof(char *) * i);
	i = 0;
	while (node != NULL)
	{
		tab[i] = node->s;
		i++;
		node = node->next;
	}
	tab[i] = 0;
	return (tab);
}

int	check_quotes(char *s, int i, int j)
{
	while (s[i])
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\'' && s[i])
				i++;
			if (s[i] != '\'')
				j = 1;
		}
		if (s[i] == '"')
		{
			i++;
			while (s[i] != '"' && s[i])
				i++;
			if (s[i] != '"')
				j = 1;
		}
		i++;
	}
	return (j);
}
