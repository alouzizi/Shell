/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:49:00 by alouzizi          #+#    #+#             */
/*   Updated: 2022/09/09 14:49:00 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

void	tree(char *s, char **env)
{
	t_tree	*root;
	t_tree	*temp;
	t_tree	*temp2;
	char	**str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	root = malloc(sizeof(t_tree));
	temp = root;
	while (s[i])
	{
		if (s[i] != '|' && s[i] != '<' && s[i] != '>' && s[i] != '&')
		{
			str = transfer_list_to_2darray(get_cmd(s, &i));
			j = 1;
		}
		if ((s[i] == '|' || s[i] == '<' || s[i] == '>') \
			&& s[i + 1] != '|' && s[i])
		{
			if (j == 0 && s[i] == '|')
			{
				ft_putendl_fd("Syntax Error\n", 2);
				return ;
			}
			if (j == 1)
			{
				temp->s = malloc(sizeof(char *) * 2);
				if (s[i + 1] == '<' || s[i + 1] == '>')
				{
					if (s[i] != s[i + 1])
					{
						ft_putendl_fd("Syntax Error\n", 2);
						return ;
					}
					temp->s[0] = data(2, s[i], s[i + 1]);
					i++;
				}
				else
				temp->s[0] = data(1, s[i], 0);
				temp->left = newtree(str);
				j = 0;
				i++;
			}
			temp->right = malloc(sizeof(t_tree));
			temp = temp->right;
		}
		if (s[i] == '&' || s[i] == '|')
		{
			if (s[i] != s[i + 1] || j == 0)
			{
				ft_putendl_fd("Syntax Error\n", 2);
				return ;
			}
			if (j == 1)
			{
				temp->s = str;
				temp->right = NULL;
				temp->left = NULL;
				j = 0;
			}
			temp2 = malloc(sizeof(t_tree));
			temp2->s = malloc(sizeof(char *) * 2);
			temp2->s[0] = data(2, s[i], s[i + 1]);
			i++;
			temp2->left = root;
			root = temp2;
			j = 0;
			i++;
			root->right = malloc(sizeof(t_tree));
			temp = root->right;
		}
	}
	if (j != 0)
	{
		temp->s = str;
		temp->left = NULL;
		temp->right = NULL;
	}
	else
		root = 0;
	print_tree(root, 0);
	if (root)
		execute(root->s, env);
	creat_pipe(root, env);
}
