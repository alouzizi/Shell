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

#include "../minishell.h"

t_node	*get_cmd(char *s, int *i)
{
	t_node	*cmd;

	cmd = NULL;
	while (s[*i])
	{
		if (s[*i] == '"' || s[*i] == '\'')
			handle_quotes(&cmd, s, i);
		else if (s[*i] != ' ')
		{
			if (s[*i] == '|' || s[*i] == '<' || s[*i] == '>' || s[*i] == '&')
				return (cmd);
			if (normall_collect(&cmd, s, i) == 1)
				return (cmd);
		}
		while (s[*i] && s[*i] == ' ')
			(*i)++;
	}
	return (cmd);
}

void	handle_quotes(t_node **cmd, char *s, int *i)
{
	t_node	*node;
	int		start;
	int		end;
	char	c;

	c = s[*i];
	(*i)++;
	start = *i;
	while (s[*i] != c && s[*i])
		(*i)++;
	end = (*i) - 1;
	if (s[*i] == '"')
	{
		node = ft_lstnew(NULL);
		node->s = expand_dollar(&s[start], 0, c);
	}
	else
		node = create_node(s, start, end);
	(*i) += 1;
	what_next(node, s, i);
	ft_lstadd_back(cmd, node);
}

void	what_next(t_node *node, char *s, int *i)
{
	t_node	*list;

	list = NULL;
	if ((s[*i] == '\'' || s[*i] == '"') && s[*i])
	{
		handle_quotes(&list, s, i);
		node->s = ft_strjoin(node->s, list->s, 3);
		free(list);
	}
	if (s[*i] != ' ' && s[*i])
	{
		normall_collect(&list, s, i);
		node->s = ft_strjoin(node->s, list->s, 3);
		free(list);
	}
}

char	**transfer_list_to_2darray(t_node *node)
{
	char	**tab;
	t_node	*tmp;
	int		i;

	i = ft_lstsize(node) + 1;
	tab = malloc(sizeof(char *) * i);
	i = 0;
	while (node != NULL)
	{
		tab[i] = node->s;
		tmp = node;
		i++;
		node = node->next;
		free(tmp);
	}
	tab[i] = 0;
	return (tab);
}

int	check_quotes(char *s, int i, int j)
{
	while (s[++i])
	{
		if (s[i] && s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			if (!s[i] || s[i] != '\'')
				return (1);
		}
		if (s[i] && s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
				i++;
			if (!s[i] || s[i] != '"')
				return (1);
		}
	}
	return (j);
}
