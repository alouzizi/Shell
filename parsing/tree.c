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

void	tree(char *s, char **env)
{
	t_tree	*root;
	t_tree	*temp;
	t_tree	*temp2;
	char	**str;
	int		i;
	int		j;

	i = j = 0;
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
		if (s[i] == '&' || (s[i] == '|' && s[i + 1] == '|'))
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
		if ((s[i] == '|' || s[i] == '<' || s[i] == '>') && s[i])
		{
			if ((j != 1 && s[i] == '|') || (j == 1 && str[0] == NULL))
			{
				ft_putendl_fd("Syntax Error\n", 2);
				return ;
			}
			temp->s = malloc(sizeof(char *));
			if (s[i + 1] == '<' || s[i + 1] == '>'  && (s[i] == '<' || s[i] == '>') )
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
			if (j == 1)
				temp->left = newtree(str);
			else
				temp->left = NULL;
			i++;
			j = i;
			str = transfer_list_to_2darray(get_cmd(s, &j));
			if (str[0])
				temp->right = newtree(NULL);
			else
			{
				ft_putendl_fd("Syntax Error\n", 2);
				return ;
			}
			temp = temp->right;
			j = 0;
		}
	}
	if (j == 1)
	{
		temp->s = str;
		temp->left = NULL;
		temp->right = NULL;
	}
	print_tree(root, 0);
	// if (root)
	// 	execute(root->s, env);
	creat_pipe(root, env);
}
