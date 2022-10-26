/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:57:35 by alouzizi          #+#    #+#             */
/*   Updated: 2022/10/17 02:17:54 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	normall_collect(t_node **cmd, char *s, int *i, t_vars *v)
{
	t_node	*node;
	t_node	*list;
	int		star;
	int		end;

	list = NULL;
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
	if (s[*i] == '$' && s[*i])
	{
		if (node->s)
			node->s = ft_strjoin(node->s, expand_dollar(s, star, 0, ' ', v), 3);
		else
			node->s = expand_dollar(s, star, 0, ' ', v);
		while (s[*i] && (s[*i] != ' ' && s[*i] != '|' && s[*i] != '"' && s[*i]
				!= '<' && s[*i] != '&' && s[*i] != '|' && s[*i] != '>'))
			(*i)++;
	}
	if ((s[*i] == '\'' || s[*i] == '"') && s[*i])
	{
		handle_quotes(&list, s, s[*i], i, v);
		node->s = ft_strjoin(node->s, list->s, 3);
		list = NULL;
	}
	ft_lstadd_back(cmd, node);
	return (0);
}

t_tree	*newtree(char **content)
{
	t_tree	*tree;

	tree = malloc(sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->s = content;
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}

void	print_tree(t_tree *root, int space)
{
	int	i;

	i = COUNT - 1;
	if (root == NULL)
		return ;
	space += COUNT;
	print_tree(root->right, space);
	ft_putendl_fd("", 1);
	while (++i < space)
		ft_putstr_fd(" ", 1);
	if(root->s)
		printf("[%s]\n", root->s[0]);
	print_tree(root->left, space);
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
