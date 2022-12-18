/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 00:36:46 by alouzizi          #+#    #+#             */
/*   Updated: 2022/12/18 02:24:15 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_herdocintree(t_tree **root)
{
	t_tree	*temp;

	temp = *root;
	if (temp)
	{
		check_herdocintree(&temp->left);
		if (!ft_strcmp(temp->s[0], "<<") && temp->s[0])
			herdoc(&temp);
		check_herdocintree(&temp->right);
	}
	else
		return ;
}

void	herdoc(t_tree **root)
{
	static int	o = 0;
	int			i;

	if (!ft_strcmp((*root)->s[0], "<<"))
	{
		i = -1;
		while ((*root)->left->s[++i])
		{
			o = herdoc_loop(root, o, i, NULL);
			if (o == -1)
				break ;
		}
	}
}

int	herdoc_loop(t_tree **root, int o, int i, char *her)
{
	int		j;
	char	*s;

	j = 1;
	s = readline(">");
	if (!s)
	{
		o++;
		j = open_herdoc(root, s, i, o);
	}
	while (ft_strcmp(s, (*root)->left->s[i]) && j != 0)
	{
		her = ft_strjoin2(her, s, 1);
		her = ft_strjoin2(her, "\n", 0);
		s = readline(">");
		if (!s)
			return (-1);
	}
	if (j != 0)
	{
		o++;
		free(s);
		check_open_and_free(root, o, i, her);
	}
	return (o);
}

void	check_open_and_free(t_tree **root, int o, int i, char *her)
{
	int		j;
	char	*s;

	s = ft_strjoin("/tmp/", ft_itoa(o), 2);
	j = open(s, O_CREAT | O_TRUNC | O_RDWR, 0777);
	ft_putstr_fd(her, j);
	free((*root)->left->s[i]);
	(*root)->left->s[i] = ft_strdup(s);
	free(s);
	free(her);
}

int	open_herdoc(t_tree **root, char *s, int i, int o)
{
	int	j;

	s = ft_strjoin("/tmp/", ft_itoa(o), 0);
	j = open(s, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (j < 0)
	{
		perror(PRMPT_ERR);
		exit(1);
	}
	free((*root)->left->s[i]);
	(*root)->left->s[i] = ft_strdup(s);
	free (s);
	return (0);
}
