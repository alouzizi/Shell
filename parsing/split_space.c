/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:10:21 by alouzizi          #+#    #+#             */
/*   Updated: 2022/10/14 13:09:22 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

static int	count_words(char const *s)
{
	int		count;
	int		i;
    char    c;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] != ' ' && s[i] && s[i] != '>' && s[i] != '<'
				&& s[i] != '|' && s[i] != '&')
		{
			if (s[i] == '\'' || s[i] == '"')
			{
				c = s[i];
				i++;
				while(s[i] != c)
					i++;
			}
			i++;
			count++;
		}
		
		while (s[i] != ' ' && s[i] && s[i] != '>' && s[i] != '<'
				&& s[i] != '|' && s[i] != '&')
			i++;
		if ( s[i] && (s[i] == '>' || s[i] == '<'
				|| s[i] == '|' || s[i] == '&'))
			break;
	}
	printf("%d\n", count);
	return (count);
}

static char	*init_str(char const *s)
{
	int		i;
	char	*ptr;
	char	c;

	i = 0;
	while (s[i] != ' ' && s[i] && s[i] != '>' && s[i] != '<'
			&& s[i] != '|' && s[i] != '&')
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			c = s[i];
			i++;
			while(s[i] != c)
				i++;
		}
		i++;
	}
	ptr = (char *)malloc(sizeof(char) * (i + 1));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, i + 1);
	return (ptr);
}

static char	**free_tab(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
	return (NULL);
}

char	**ft_split_space(char const *s)
{
	int		i;
	int		strs_len;
	char	**ptr;

	if (!s)
		return (NULL);
	strs_len = count_words(s);
	ptr = (char **)malloc(sizeof(char *) * (strs_len + 1));
	if (!ptr)
		return (NULL);
	i = -1;
	while (++i < strs_len)
	{
		while (s[0] == ' ')
			s++;
		ptr[i] = init_str(s);
		if (!ptr[i])
			return (free_tab(ptr));
		s = s + ft_strlen(ptr[i]);
	}
	ptr[i] = 0;
	return (ptr);
}
