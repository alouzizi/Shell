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
	if (root != NULL)
	{
		free_tree(root->right);
		free_array(root->s);
		free_tree(root->left);
		free(root);
	}
}

int	pipe_parsing(t_tree **root, char **str, char *s, int j, t_vars *v)
{
	t_tree	*temp2;
	int		l;
	l = 0;
	static int i =0;
	if (j != 1 && j != 2 && j != 3)
	{
		ft_putendl_fd("Syntax Error", 2);
		return (0);
	}
	if (root)
		temp2 = *root;
	i++;
	(*root) = newtree(NULL);
	(*root)->s = malloc(sizeof(char *) * 2);
	(*root)->s[0] = data(1, s[l], 0);
	l++;
	if (j == 1)
		(*root)->left = newtree(str);
	else
		(*root)->left = temp2;
	(*root)->right = newtree(NULL);
	(*root)->right->s = transfer_list_to_2darray(get_cmd(s, &l, v));
	l++;
	return (l);
}

void	tree(char *s, t_vars *v)
{
	t_tree	*root;
	t_tree	*temp;
	char	**str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	root = newtree(NULL);
	temp = root;
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
			j = pipe_parsing(&root, str, &s[i], j, v);
			if (j == 0)
				return ;
			i += j;
			temp = root->right;
			j = 3;
		}
		if ((s[i] == '<' || s[i] == '>') && s[i])
		{
			j = redirection(&temp, &s[i], str, j, v);
			if (j == 0)
				return ;
			i += j;
			j = 2;
		}
	}
	if (j == 1)
		temp->s = str;
	if (!root || !root->s)
		return ;
	// print_tree(root, 0);
	operator_selection(root, v);
	free_tree(root);
}

int	redirection(t_tree **temp, char *s, char **str, int j, t_vars *v)
{
	t_redirct	*r;
	int			i;

	i = 0;
	(*temp)->s = malloc(sizeof(char *));
	if ((s[i + 1] == '<' || s[i + 1] == '>') && (s[i] == '<' || s[i] == '>'))
	{
		if (s[i] != s[i + 1])
		{
			ft_putendl_fd("Syntax Error", 2);
			return (0);
		}
		(*temp)->s[0] = data(2, s[i], s[i + 1]);
		i++;
	}
	else
		(*temp)->s[0] = data(1, s[i], 0);
	(*temp)->left = newtree(str);
	if (s[i] == '>' || s[i] == '<')
	{
		r = redirection_parse(*temp, s, &i, v);
		if (r->j == -1)
			return (0);
		if (j == 0)
			(*temp)->left->s = r->param;
		else
			(*temp)->left->s = ft_strjoin2d((*temp)->left->s, r->param);
		(*temp)->right = newtree(r->file);
		return (i);
	}
	i++;
	j = i;
	str = transfer_list_to_2darray(get_cmd(s, &j, v));
	if (str[0])
		(*temp)->right = newtree(NULL);
	else
	{
		ft_putendl_fd("Syntax Error33", 2);
		return (0);
	}
	(*temp) = (*temp)->right;
	return (i);
}
