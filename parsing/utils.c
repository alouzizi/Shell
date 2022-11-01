/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:36:15 by alouzizi          #+#    #+#             */
/*   Updated: 2022/11/01 16:39:02 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**ft_strjoin2d(char **s, char **s0)
{
	char	**s1;
	int		i;
	int		j;

	j = 0;
	if (!s0)
		return (s);
	if (!s)
		return (s0);
	i = arr_len(s);
	i += arr_len(s0);
	s1 = malloc(sizeof(char *) * (i + 1));
	if (!s1)
		exit(1);
	i = 0;
	while (s[i])
	{
		s1[i] = s[i];
		i++;
	}
	while (s0[j])
		s1[i++] = s0[j++];
	s1[i] = NULL;
	return (s1);
}

int	get_redirect_file(t_redirct *p, char *str, int i)
{
	int	j;
	int	l;

	j = i;
	p->file = malloc(sizeof(char *) * 2);
	if (!p->file)
		exit(1);
	p->file[1] = NULL;
	while (str[i] && str[i] != ' ')
		i++;
	p->file[0] = malloc(i - j + 1);
	if (!p->file[0])
		exit (1);
	l = 0;
	while (j < i)
		p->file[0][l++] = str[j++];
	p->file[0][l] = '\0';
	return (i);
}

t_node	*create_node(char *str, int start, int end)
{
	t_node	*node;
	int		i;

	i = 0;
	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->s = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!node->s)
		return (NULL);
	while (start <= end)
		node->s[i++] = str[start++];
	node->s[i] = '\0';
	return (node);
}
