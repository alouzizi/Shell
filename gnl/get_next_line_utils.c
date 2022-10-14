/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 18:59:30 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/14 02:51:08 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_strcpy_gnl(char *dst, const char *src)
{
	unsigned int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
}

char	*ft_strchr_gnl(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}

void	ft_bzero_gnl(char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (n > i)
		s[i++] = 0;
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		str2_len;
	int		str_len;
	int		i;
	char	*str;

	str2_len = 0;
	while (s2[str2_len] && s2[str2_len] != '\n')
		str2_len++;
	if (s2[str2_len] == '\n')
		str2_len++;
	str = malloc(ft_strlen_gnl(s1) + str2_len + 1);
	if (!str)
		return (NULL);
	ft_strcpy_gnl(str, s1);
	str_len = ft_strlen_gnl(str);
	i = 0;
	while (i < str2_len)
	{
		str[str_len + i] = s2[i];
		i++;
	}
	str[str_len + i] = 0;
	free(s1);
	return (str);
}
