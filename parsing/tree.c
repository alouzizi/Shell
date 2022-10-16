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
		return (redirect_intput(root));
	else
		return (simple_cmd(root));
	return (0);
}

int	and_or(t_tree **root, char **str, char *s, int j)
{
	t_tree	*temp2;
	int		l;
	int		i;

	l = 0;
	i = 1;
	if (j != 1 && j != 2 && j != 3)
	{
		ft_putendl_fd("Syntax Error", 2);
		return (0);
	}
	if (root)
		temp2 = *root;
	(*root) = newtree(NULL);
	(*root)->s = malloc(sizeof(char *) * 2);
	(*root)->s[0] = data(1, s[l], 0);
	l++;
	if (j == 1)
		(*root)->left = newtree(str);
	else
		(*root)->left = temp2;
	(*root)->right = newtree(NULL);
	l++;
	i = l;
	while (s[i] != '|' && s[i])
	{
		if (s[i] == '<' || s[i] == '>')
		{
			i = 0;
			break ;
		}
		i++;
	}
	if (i)
		(*root)->right->s = transfer_list_to_2darray(get_cmd(s, &l));
	else
		l = 1;

	//printf();
	puts("*****");
	printf("l = %d\n", l);
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
		if (s[i] == '|' && s[i])
		{
			j = and_or(&root, str, &s[i], j);
			if (j == 0)
				return ;
			i += j;
			temp = root->right;
			j = 3;
		}
		if ((s[i] == '<' || s[i] == '>') && s[i])
		{
			j = redirection(&temp, &s[i], str, j);
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
	print_tree(root, 0);
	check_herdocintree(&root);
	//herdoc(&root);
	operator_selection(root);
}

void check_herdocintree(t_tree **root)
{
	t_tree *temp;

	temp = *root;
	if (temp)
	{
		check_herdocintree(&temp->left);
		if(!ft_strcmp(temp->s[0],"<<"))
			herdoc(&temp);
		check_herdocintree(&temp->right);
	}
	else
		return ;
}

void	herdoc(t_tree **root)
{
	t_tree *temp;
	char	*s;
	char	*her;
	static	int o = 0;
	int 	i;

	temp = (*root);
	s = NULL;
	int j = 1;
	if (!ft_strcmp(temp->s[0],"<<"))
	{
		i  = -1;
		her = NULL;
		while(temp->right->s[++i])
		{
			j = 1;
			puts(temp->right->s[i]);
			s = readline("> ");
			if (!s)
			{ 
				o++;
				s  = ft_strjoin("/tmp/" ,ft_itoa(o));
				int f = open(s, O_CREAT | O_TRUNC | O_RDWR , 0777);
				temp->right->s[i] = ft_strdup(s);
				j = 0;
				free (s);
			}
			while(ft_strcmp(s , temp->right->s[i]) && j != 0)
			{
					her = ft_strjoin(her, s);
					her = ft_strjoin(her ,"\n");
					s =  readline(">");
					if (!s)
						break ;
			}
			if (j != 0)
			{
				o++;
				s  = ft_strjoin("/tmp/" ,ft_itoa(o));
				int f = open(s, O_CREAT | O_TRUNC | O_RDWR , 0777);
				ft_putstr_fd(her ,f);
				printf("i === %d\n", i);
				temp->right->s[i] = ft_strdup(s);
				free(her);
				her = NULL;
			}
		}
	}
	return ;
}


int	redirection(t_tree **temp, char *s, char **str, int j)
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
	}
	else
		(*temp)->s[0] = data(1, s[i], 0);
	(*temp)->left = newtree(str);
	if (s[i] == '>' || s[i] == '<')
	{
		r = redirection_parse(*temp, s, &i);
		printf(" i == %d\n", i);
		if (r->j == -1)
			return (0);
		if (j == 0)
			(*temp)->left->s = r->param;
		else
			(*temp)->left->s = ft_strjoin2d((*temp)->left->s, r->param);
		(*temp)->right = newtree(r->file);
		//return (i);
	}
	puts("*****************|||");
	i++;
	j = i;
	str = transfer_list_to_2darray(get_cmd(s, &j));
	if (str[0])
		(*temp)->right = newtree(NULL);
	else
	{
		ft_putendl_fd("Syntax Error", 2);
		return (0);
	}
	(*temp) = (*temp)->right;
	return (i -1);
}
