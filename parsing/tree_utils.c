/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 04:57:35 by alouzizi          #+#    #+#             */
/*   Updated: 2022/09/20 08:16:49 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	printf("\n");
	while (++i < space)
		printf(" ");
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
		exit(1);
	s[i++] = c;
	if (j == 2)
		s[i++] = c2;
	s[i] = '\0';
	return (s);
}
