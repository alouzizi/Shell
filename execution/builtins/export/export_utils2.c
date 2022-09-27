/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 05:20:03 by ooumlil           #+#    #+#             */
/*   Updated: 2022/09/27 02:33:10 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

// checks if its a variable that has value or not
// and returns the index where the value starts

int	has_value(char *arg, int *ptr)
{
	int	index;

	index = 0;
	while (arg[index] != '=')
		index++;
	if (arg[index] == '=')
		*ptr = -1;
	return (index);
}

// self-explanatory

void	update_or_add_var(int b, int ptr, char *var)
{
	if (b)
		g_global.n_env[ptr] = ft_strdup(var);
	else
		add_var_to_env(var);
}

// should i even explain

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	*ft_strjoin_no_free(char *s1, char const *s2)
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
	return (s);
}
