/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 19:04:00 by alouzizi          #+#    #+#             */
/*   Updated: 2022/12/18 03:19:56 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

int	ft_word_len(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	**ft_split(char *str, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) * (ft_count_words(str, c) + 1));
	if (!tab)
		return (NULL);
	while (str[i])
	{
		k = 0;
		tab[j] = malloc(sizeof(char) * (ft_word_len(&str[i], c) + 1));
		if (!tab[j])
			return (NULL);
		while (str[i] && str[i] != c)
			tab[j][k++] = str[i++];
		tab[j][k] = '\0';
		if (str[i])
			i++;
		j++;
	}
	tab[j] = NULL;
	return (tab);
}
