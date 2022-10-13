/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 22:17:33 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/05 18:56:37 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_strjoin_char(char *s, char c)
{
	char	*ret;
	int		j;
	int		len;

	if (!s || !c)
		return (NULL);
	len = ft_strlen(s) + 1;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	j = 0;
	while (s[j])
	{
		ret[j] = s[j];
		j++;
	}
	ret[j + 1] = c;
	ret[j + 2] = '\0';
	return (ret);
}

char	*open_directory(void)
{
	struct dirent	*de;
	DIR				*dr;
	char			*value;

	dr = opendir(".");
	value = 0;
	if (dr)
	{
		de = readdir(dr);
		while (de)
		{
			if (de->d_name[0] != '.')
				value = ft_strjoin(ft_strjoin(value, " "), de->d_name);
			de = readdir(dr);
		}
		closedir(dr);
	}
	ft_putendl_fd(value, 1);
	return (value);
}

char	*replace_star(char *line)
{
	char	*expand;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(line);
	expand = "";
	while (line[i])
	{
		if (line[i] == '*')
		{
			while (line[i] == '*' && line[i])
				i++;
			expand = ft_strjoin(expand, open_directory());
		}
		if (i < len)
			expand = ft_strjoin_char(expand, &line[i]);
		i++;
	}
	return (expand);
}

int	find_star(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		//add a func to check if its whithin quotes or not
		if (line[i] == '*')
			return (i);
		i++;
	}
	return (-1);
}

char	*expand_star(char *line)
{
	// char	cwd[PATH_MAX];
	// char	*path;
	int		i;

	// path = getcwd(cwd, sizeof(cwd));
	i = 0;
	while (i != -1)
	{
		i = find_star(line);
		if (i != -1)
			line = replace_star(line);
	}
	return (line);
}
