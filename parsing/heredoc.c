/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 00:36:46 by alouzizi          #+#    #+#             */
/*   Updated: 2022/12/16 14:16:58 by alouzizi         ###   ########.fr       */
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
		if (!ft_strcmp(temp->s[0], "<<"))
			herdoc(&temp);
		check_herdocintree(&temp->right);
	}
	else
		return ;
}

void	herdoc(t_tree **root)
{
	static int	o = 0;
	char		*s;
	char		*her;
	int			i;
	int			j;

	j = 1;
	if (!ft_strcmp((*root)->s[0], "<<"))
	{
		i = -1;
		while ((*root)->left->s[++i])
		{
			j = 1;
			her = NULL;
			s = readline(">");
			if (!s)
			{
				o++;
				s = ft_strjoin("/tmp/", ft_itoa(o), 0);
				j = open(s, O_CREAT | O_TRUNC | O_RDWR, 0777);
				if (j < 0)
				{
					perror(PRMPT_ERR);
					return ;
				}
				free((*root)->left->s[i]);
				(*root)->left->s[i] = ft_strdup(s);
				j = 0;
				free (s);
			}
			while (ft_strcmp(s, (*root)->left->s[i]) && j != 0)
			{
				her = ft_strjoin2(her, s, 1);
				her = ft_strjoin2(her, "\n", 0);
				s = readline(">");
				if (!s)
					break ;
			}
			if (j != 0)
			{
				o++;
				free(s);
				s = ft_strjoin("/tmp/", ft_itoa(o), 2);
				j = open(s, O_CREAT | O_TRUNC | O_RDWR, 0777);
				ft_putstr_fd(her, j);
				free((*root)->left->s[i]);
				(*root)->left->s[i] = ft_strdup(s);
				free(s);
				free(her);
			}
		}
	}
}

char	*ft_strjoin2(char *s1, char *s2, int o)
{
	char	*s;
	int		i;
	int		j;

	if (!s1)
		return (s2);
	if (!s2)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	s = (char *)malloc(sizeof(char) * (i + 1));
	while (!s)
		return (NULL);
	j = -1;
	i = 0;
	while (s1[++j])
		s[j] = s1[j];
	while (s2[i])
		s[j++] = s2[i++];
	s[j] = '\0';
	free(s1);
	if (o)
		free(s2);
	return (s);
}

void	free_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}