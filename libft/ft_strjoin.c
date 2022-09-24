/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:03:55 by alouzizi          #+#    #+#             */
/*   Updated: 2022/09/23 23:34:24 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char	*s1, char const *s2)
{
	char	*s;
	int		i;
	int		j;
	int		len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	s = (char *)malloc(sizeof(char) * (len + 1));
	while (!s)
		return (NULL);
	j = 0;
	i = 0;
	while (s1[j])
	{
		s[j] = s1[j];
		j++;
	}
	while (s2[i])
	{
		s[j++] = s2[i++];
	}
	s[j] = '\0';
	free(s1);
	return (s);
}
