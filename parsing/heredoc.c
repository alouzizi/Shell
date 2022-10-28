/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 00:36:46 by alouzizi          #+#    #+#             */
/*   Updated: 2022/10/28 02:03:41 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
		while(temp->left->s[++i])
		{
			j = 1;
			s = readline(">");
			if (!s)
			{ 
				o++;
				s  = ft_strjoin("/tmp/" ,ft_itoa(o),0);
				int f = open(s, O_CREAT | O_TRUNC | O_RDWR , 0777);
                if(f < 0)
                {
                    perror(PRMPT_ERR);
                    return ;
                }
				temp->left->s[i] = ft_strdup(s);
				j = 0;
				free (s);
			}
			while(ft_strcmp(s , temp->left->s[i]) && j != 0)
			{
					her = ft_strjoin2(her, s);
					her = ft_strjoin2(her ,"\n");
					s =  readline(">");
					if (!s)
						break ;
			}
			if (j != 0)
			{
				o++;
				s  = ft_strjoin("/tmp/" ,ft_itoa(o),2);
				int f = open(s, O_CREAT | O_TRUNC | O_RDWR , 0777);
				ft_putstr_fd(her ,f);
				temp->left->s[i] = ft_strdup(s);
				free(her);
				her = NULL;
			}
		}
	}
	return ;
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*s;
	int		i;
	int		j;

	if(!s1)
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
	return (s);
}