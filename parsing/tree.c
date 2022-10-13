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

int	simple_cmd(t_tree *root)
{
	return (execute(root->s));
}

int	and_operator(t_tree *root)
{
	if (!simple_cmd(root->left))
		simple_cmd(root->right);
	return (0);
}

int	or_operator(t_tree *root)
{
	if (simple_cmd(root->left))
		simple_cmd(root->right);
	return (0);
}

int	operator_selection(t_tree *root)
{
	if (!builtincmp(root->s[0], "|"))
		return (create_pipe(root));
	else if (!builtincmp(root->s[0], "||"))
		return (or_operator(root));
	else if (!builtincmp(root->s[0], "&&"))
		return (and_operator(root));
	else if (!builtincmp(root->s[0], ">"))
		return (redirecte_output(root, 0));
	else if (!builtincmp(root->s[0], "<"))
		return (redirect_intput(root));
	else if (!builtincmp(root->s[0], ">>"))
		return (redirecte_output(root, 1));
	else if (!builtincmp(root->s[0], "<<"))
		puts("HEREDOC");
	else
		return (simple_cmd(root));
	return (0);
}

int	and_or(t_tree *root, char **str, char *s, int j)
{
	t_tree	*temp;
	t_tree	*temp2;
	int		l;

	l = 0;
	temp = NULL;
	if (s[l] != s[l + 1] || j == 0)
	{
		ft_putendl_fd("Syntax Error", 2);
		return (l);
	}
	if (j == 1)
	{
		temp->s = str;
		temp->right = NULL;
		temp->left = NULL;
	}
	temp2 = malloc(sizeof(t_tree));
	temp2->s = malloc(sizeof(char *) * 2);
	temp2->s[0] = data(2, s[l], s[l + 1]);
	l++;
	temp2->left = root;
	root = temp2;
	l++;
	root->right = malloc(sizeof(t_tree));
	temp = root->right;
	return (l);
}

void	tree(char *s)
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
			str = transfer_list_to_2darray(get_cmd(s, &i));
			j = 1;
		}
		if ((s[i] == '|' || s[i] == '<' || s[i] == '>') && s[i])
		{
			j = pipe_redirection(&temp, &s[i], str, j);
			if (j == 0)
				return ;
			i += j;
			j = 0;
		}
	}
	if (j == 1)
	{
		temp->s = str;
		temp->left = NULL;
		temp->right = NULL;
	}
	if (!root || !root->s)
		return ;
	print_tree(root, 0);
	operator_selection(root);
}

int	pipe_redirection(t_tree **temp, char *s, char **str, int j)
{
	t_redirct	*r;
	int			i;

	i = 0;
	if ((j != 1 && s[i] == '|') || (j == 1 && str[0] == NULL))
	{
		ft_putendl_fd("Syntax Error", 2);
		return (0);
	}
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
		r = redirection_parse(*temp, s, &i);
		if (r->i == -1)
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
	str = transfer_list_to_2darray(get_cmd(s, &j));
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
