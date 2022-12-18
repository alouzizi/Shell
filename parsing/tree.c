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

#include "../minishell.h"

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

t_v	pipe_parsing(t_tree **root, char **str, char *s, t_v v)
{
	t_tree	*temp2;

	if (v.j != 1 && v.j != 2 && v.j != 3)
	{
		ft_putendl_fd("Syntax Error", 2);
		v.j = -1;
		return (v);
	}
	if (*root)
	{
		temp2 = *root;
		(*root) = newtree(NULL);
	}
	else
		(*root) = newtree(NULL);
	(*root)->s = malloc(sizeof(char *) * 2);
	(*root)->s[0] = data(1, s[v.i], 0);
	(*root)->s[1] = NULL;
	v.i++;
	if (v.j == 1)
		(*root)->left = newtree(str);
	else
		(*root)->left = temp2;
	v.j = 3;
	return (v);
}

t_v	norm_rediect(t_tree **root, char **str, char *s, t_v v)
{
	if ((s[v.i] == '<' || s[v.i] == '>') && s[v.i])
	{
		v.j = red(root, &s[v.i], str);
		if (v.j == -1)
			return (v);
		v.i += v.j;
		v.j = 2;
	}
	return (v);
}

t_v	norm_tree(t_tree **root, char **str, char *s, t_v v)
{
	if (s[v.i] == '|' && s[v.i])
	{
		v = pipe_parsing(root, str, s, v);
		if (v.j == -1)
			return (v);
		str = transfer_list_to_2darray(get_cmd(s, &v.i));
		if (str[0])
		{
			if ((s[v.i] != '<' && s[v.i] != '>'))
				(*root)->right = newtree(str);
			else
				(*root)->right = newtree(NULL);
		}
		else
		{
			ft_putendl_fd("Syntax Erro1r", 2);
			return (v.j = -1, v);
		}
	}
	v = norm_rediect(root, str, s, v);
	if (v.j == -1)
		return (v);
	return (v);
}

void	tree(t_tree **root, char *s)
{
	char		**str;
	t_v			v;	

	v.i = 0;
	v.j = 0;
	*root = NULL;
	str = NULL;
	while (s[v.i])
	{
		if (s[v.i] != '|' && s[v.i] != '<' && s[v.i] != '>' && s[v.i] != '&')
		{
			str = transfer_list_to_2darray(get_cmd(s, &v.i));
			v.j = 1;
		}
		v = norm_tree(root, str, s, v);
		if (v.j == -1)
			return ;
	}
	if (v.j == 1)
		*root = newtree(str);
	if (!*root)
		return ;
	check_herdocintree(root);
	operator_selection(*root);
	free_tree(*root);
}
