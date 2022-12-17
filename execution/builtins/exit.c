/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 18:29:54 by alouzizi          #+#    #+#             */
/*   Updated: 2022/12/17 19:24:41 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_number(char *status)
{
	int	i;

	i = 0;
	while (status[i])
	{
		if (!(status[i] >= '0' && status[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

static void	valid_arg(char *s)
{
	if (is_number(s))
	{
		printf("exit\n");
		g_global.status = ft_atoi(s);
		exit (g_global.status);
	}
	printf("exit\nbash: exit: : %s: numeric argument required\n", s);
	g_global.status = 255;
	exit (255);
}

int	exitt(char **str)
{
	int	i;

	i = 1;
	while (str[i])
		i++;
	if (i > 3)
	{
		if (!is_number(str[1]))
		{
			printf("exit\nbash: exit: : %s: numeric argument required\n", str[1]);
			g_global.status = 255;
			exit (255);
		}
		printf("exit\nbash: exit: too many arguments\n");
		g_global.status = 255;
		return (0);
	}
	else
	{
		if (str[1])
			valid_arg(str[1]);
		printf("exit\n");
		exit (0);
	}
	return (1);
}
