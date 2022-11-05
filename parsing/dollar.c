/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 23:47:28 by ooumlil           #+#    #+#             */
/*   Updated: 2022/11/05 14:17:53 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*expand_dollar(char *s, int lvl, char c, t_vars *v)
{
	char	*expand;
	char	*dollar;
	int		j;
	int		i;
	int		start;

	j = 0;
	start = 0;
	i = 0;
	while ((lvl == 1 || s[start] != '$') && s[start] != c && s[start])
		start++;
	expand = malloc(start - i + 1);
	while (i < start)
		expand[j++] = s[i++];
	expand[j] = '\0';
	if (s[i] == '$')
	{
		dollar = expand_dollar_2(s, i, v, c);
		if (dollar)
			expand = ft_strjoin(expand, dollar, 3);
	}
	return (expand);
}

char	*expand_dollar_2(char *s, int i, t_vars *v, char c)
{
	char	*dollar;

	dollar = NULL;
	if (s[i + 1] && (ft_isdigit(s[i + 1])
			|| (!ft_isalpha(s[i + 1]) && s[i + 1] != '_')))
	{
		if (ft_isdigit(s[i + 1]))
			return (expand_dollar(&s[i + 2], 0, c, v));
		else if (s[i + 1] == '?')
			dollar = ft_itoa(g_global.status);
		else
			return (expand_dollar(&s[i], 1, c, v));
		return (ft_strjoin(dollar, expand_dollar(&s[i + 2], 0, c, v), 1));
	}
	dollar = check_expand(s, &i, v);
	if (s[i] && s[i] != c)
	{
		if (!dollar)
			return (expand_dollar(&s[i], 0, c, v));
		dollar = ft_strjoin(dollar, expand_dollar(&s[i], 0, c, v), 3);
	}
	return (dollar);
}

char	*check_expand(char *s, int *i, t_vars *v)
{
	char	*dollar;
	char	*tmp;
	int		start;
	int		j;

	j = 0;
	start = 0;
	if (s[*i + 1] && (ft_isdigit(s[*i + 1])
			|| ft_isalpha(s[*i + 1]) || s[*i + 1] == '_'))
	{
		++(*i);
		while (s[*i] && (ft_isdigit(s[*i])
				|| ft_isalpha(s[*i]) || s[*i] == '_'))
		{
			start++;
			(*i)++;
		}
		dollar = malloc(start + 1);
		if (!dollar)
			exit (1);
		(*i) -= start;
		while (start--)
			dollar[j++] = s[(*i)++];
		dollar[j] = '\0';
		tmp = get_env(dollar, v);
		free(dollar);
	}
	return (tmp);
}
