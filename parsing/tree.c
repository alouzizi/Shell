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

void	free_tree(t_tree *root)
{
	if (root == NULL)
		return ;
	else
	{
		free_tree(root->right);
		free_array(root->s);
		free_tree(root->left);
		free(root);
	}
}

int	pipe_parsing(t_tree **root, char **str, char *s, int j)
{
	t_tree	*temp2;
	int		l;

	l = 0;
	if (j != 1 && j != 2 && j != 3)
	{
		ft_putendl_fd("Syntax Error", 2);
		return (0);
	}
	if (*root)
	{
		temp2 = *root;
		(*root) = newtree(NULL);
	}
	else
		(*root) = newtree(NULL);
	(*root)->s = malloc(sizeof(char *) * 2);
	(*root)->s[0] = data(1, s[l], 0);
	(*root)->s[1] = NULL;
	l++;
	if (j == 1)
		(*root)->left = newtree(str);
	else
		(*root)->left = temp2;
	return (l);
}

void	tree(t_tree **root, char *s, t_vars *v)
{
	char		**str;
	int			i;
	int			j;

	i = 0;
	j = 0;
	*root = NULL;
	str = NULL;
	while (s[i])
	{
		if (s[i] != '|' && s[i] != '<' && s[i] != '>' && s[i] != '&')
		{
			str = transfer_list_to_2darray(get_cmd(s, &i, v));
			j = 1;
		}
		if (s[i] == '|' && s[i])
		{
			j = pipe_parsing(root, str, &s[i], j);
			if (j == 0)
				return ;
			i += j;
			str = transfer_list_to_2darray(get_cmd(s, &i, v));
			if (str[0])
			{
				if ((s[i] != '<' && s[i] != '>'))
					(*root)->right = newtree(str);
				else
					(*root)->right = newtree(NULL);
			}
			else
			{
				ft_putendl_fd("Syntax Error", 2);
				return ;
			}
			j = 3;
		}
		if ((s[i] == '<' || s[i] == '>') && s[i])
		{
			j = red(root, &s[i], str, v);
			if (j == -1)
				return ;
			i += j;
			j = 2;
		}
	}
	if (j == 1)
		*root = newtree(str);
	if (!*root)
		return ;
	//print_tree(*root, 0);
	check_herdocintree(root);
	operator_selection(*root, v);
	free_tree(*root);
}

int	red(t_tree **root, char *s, char **str, t_vars *v)
{
	t_tree		*temp;
	t_redirct	*r;
	int			i;

	i = 0;
	if (*root)
		temp = (*root)->right;
	else
	{
		(*root) = newtree(NULL);
		temp = *root;
	}
	r = redirection(&temp, &s[i], str, v);
	if (!r || r->j == -1)
		return (-1);
	i += r->j;
	free(r);
	return (i);
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
	if (root->s)
		printf("[%s]\n", root->s[0]);
	print_tree(root->left, space);
}
