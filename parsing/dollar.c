/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 23:47:28 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/13 14:48:25 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*expand_dollar(char *s, int start, int lvl, char c)
{
	char	*expand;
	t_node	*node;
	char	*dollar;
	int		j;
	int		i;

	j = 0;
	i = start;
	node = malloc(sizeof(t_node));
	while ((lvl == 1 || s[start] != '$') && s[start] != c)
		start++;
	expand = malloc(start - i + 1);
	while (i < start)
		expand[j++] = s[i++];
	expand[j] = '\0';
	if (s[i] == '$')
	{
		dollar = expand_dollar_2(s, i);
		if (dollar)
			expand = ft_strjoin(expand, dollar);
	}
	return (expand);
}

char	*expand_dollar_2(char *s, int i)
{
	char	*dollar;
	int		j;
	int		start;

	j = 0;
	start = 0;
	if (ft_isdigit(s[i + 1]) || (!ft_isalpha(s[i + 1]) && s[i + 1] != '_'))
	{
		if (ft_isdigit(s[i + 1]))
			return (expand_dollar(s, i + 2, 0, '"'));
		else if (s[i + 1] == '?')
			dollar = ft_itoa(g_global.status);
		else
			return (expand_dollar(s, i, 1, '"'));
		return (ft_strjoin(dollar, expand_dollar(s, i + 2, 0, '"')));
	}
	else if (ft_isdigit(s[i + 1]) || ft_isalpha(s[i + 1]) || s[i + 1] == '_')
	{
		++i;
		while (ft_isdigit(s[i]) || ft_isalpha(s[i]) || s[i] == '_' )
		{
			start++;
			i++;
		}
		dollar = malloc(start + 1);
		i -= start;
		while (start--)
			dollar[j++] = s[i++];
		dollar[j] = '\0';
		dollar = get_env(dollar);
	}
	if (s[i] && s[i] != '"')
	{
		if (!dollar)
			return (expand_dollar(s, i, 0, '"'));
		dollar = ft_strdup(dollar);
		dollar = ft_strjoin(dollar, expand_dollar(s, i, 0, '"'));
	}
	return (dollar);
}
