/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 21:44:43 by ywadday           #+#    #+#             */
/*   Updated: 2022/12/16 14:21:18 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*my_path(char *path, int *i)
{
	char	s[1024];
	char	*get_from;

	*i = 0;
	if (!path || !ft_strcmp(path, "-") || !ft_strcmp(path, "~"))
	{
		if (!path || !ft_strcmp(path, "~"))
			get_from = ft_strdup("HOME");
		if (path && !ft_strcmp(path, "-"))
			get_from = ft_strdup("OLDPWD");
		path = get_value_from_env(get_from);
		*i = 1;
		if (!path)
		{
			printf("cd %s not set\n", get_from);
			return (NULL);
		}
	}
	if (!ft_strcmp(path, ".") && !getcwd(s, 1024))
	{
		printf("cd: error retrieving current directory:\
		getcwd: cannot access parent directories: No such file or directory\n");
		return (NULL);
	}
	return (path);
}

void	handle_error(char *path)
{
	if (errno == ENOTDIR)
		printf("cd: not a directory: %s\n", path);
	else if (path && ft_strcmp(path, "."))
		printf("cd: no such file or directory: %s\n", path);
}

void	cd(char *path)
{
	char	*old_pwd;
	char	s[1024];
	int		i;

	getcwd(s, 1024);
	old_pwd = ft_strdup(s);
	path = my_path(path, &i);
	if (chdir(path) == -1)
	{
		handle_error(path);
		return ;
	}
	else
	{
		add_var_to_env("OLDPWD", old_pwd);
		if (i == 0)
		{
			s[0] = '\0';
			getcwd(s, 1024);
			path = ft_strdup(s);
		}
		add_var_to_env("PWD", path);
	}
}
