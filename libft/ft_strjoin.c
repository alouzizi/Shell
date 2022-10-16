/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:03:55 by alouzizi          #+#    #+#             */
/*   Updated: 2022/10/16 01:00:45 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	free_option(int i, char *s1, char *s2)
{
	if (i == 0)
		return (0);
	else if (i == 1)
		return (free(s1), 0);
	else if (i == 2)
		return (free(s2), 0);
	else if (i == 3)
		return (free(s1), free(s2), 0);
	return (0);
}

char	*ft_strjoin(char *s1, char *s2, int o)
{
	char	*s;
	int		i;
	int		j;

	if (!s1 || !s2)
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
	free_option(o, s1, s2);
	return (s);
}
