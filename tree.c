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

#include "minishell.h"

void tree(char *s)
{
	t_tree	*root;
	t_tree	*temp;
	t_tree	*temp2;
	int	 	i;
	int	 	j;
	char	**str;

	i = 0;
	j = 0;
	int l;
	l =0;
	root = malloc(sizeof(t_tree));
	temp = root;
	while(s[i])
	{
		if (s[i] != '|' && s[i] != '<' && s[i]  !='>' && s[i] != '&')
		{
			str = transfer_list_to_2darray(get_cmd(s, &i));
			l = 0;
			if (j != 2)
				j = 1;
		}
		if ((s[i] == '|' || s[i] == '<' || s[i] == '>') && s[i + 1] != '|' && s[i])
		{
			if ( j == 0)
			{
				printf("syntax erore\n");
				exit (1);
			}
			if (j == 1)
			{
				temp->s = malloc(sizeof(char *) * 2);
				if (s[i + 1] == '<' || s[i + 1] == '>')
				{
					temp->s[0] = data(2, s[i], s[i + 1]);
					i++;
				}
				else
				temp->s[0] = data(1, s[i], 0);
				temp->right = newtree(str);
				j = 0;
				i++;
			}
			temp->left = malloc(sizeof(t_tree));
			temp = temp->left;
		}
		if (s[i] == '&' || s[i] == '|')
		{ 
			temp2->s = malloc(sizeof(char *) * 2);
			temp2 = malloc(sizeof(t_tree));
			if (s[i] == '|')
			{
				temp2->s[0] = data(2, s[i], s[i + 1]);
				i++;
			}
			else
				temp2->s[0] = data(1, s[i], 0);
			temp2->right = root;
			root = temp2;
			j =0;
			i++;
		}
	}
	temp->s = str;
	exit(1);
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
