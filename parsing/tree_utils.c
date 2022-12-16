/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:57:35 by alouzizi          #+#    #+#             */
/*   Updated: 2022/12/16 14:17:33 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	normall_collect(t_node **cmd, char *s, int *i)
{
	t_node	*node;
	int		star;
	int		end;

	star = *i;
	while (s[*i] && s[*i] != '\'' && s[*i] != '"' && s[*i] != ' '
		&& s[*i] != '$')
	{
		if (s[*i] == '|' || s[*i] == '<' || s[*i] == '>' || s[*i] == '&')
			break ;
		(*i)++;
	}
	end = (*i) - 1;
	node = create_node(s, star, end);
	(*i) += next(node, &s[*i]);
	ft_lstadd_back(cmd, node);
	return (0);
}

int	next(t_node *node, char *s)
{
	t_node	*list;
	int		i;

	i = 0;
	list = NULL;
	if (s[i] == '$' && s[i])
	{
		if (node->s)
			node->s = ft_strjoin(node->s, expand_dollar(&s[i], 0, ' '), 3);
		else
			node->s = expand_dollar(&s[i], 0, ' ');
		while (s[i] && (s[i] != ' ' && s[i] != '|' && s[i] != '"' && s[i]
				!= '<' && s[i] != '&' && s[i] != '|' && s[i] != '>'))
			i++;
	}
	if ((s[i] == '\'' || s[i] == '"') && s[i])
	{
		handle_quotes(&list, s, &i);
		node->s = ft_strjoin(node->s, list->s, 3);
		free(list);
		list = NULL;
	}
	return (i);
}

t_tree	*newtree(char **content)
{
	t_tree	*tree;

	tree = malloc(sizeof(t_tree));
	if (!tree)
		exit (1);
	tree->s = tabdup(content);
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}

char	*data(int j, char c, char c2)
{
	char	*s;
	int		i;

	i = 0;
	s = malloc(j + 1);
	if (!s)
		return (NULL);
	s[i++] = c;
	if (j == 2)
		s[i++] = c2;
	s[i] = '\0';
	return (s);
}
