/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 08:16:26 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/20 23:28:13 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

// checks if the argument is a digit

int	arg_isdigit(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

// turns ascii to unsigned long long

long long	a_to_ll(char *str)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (sign * result);
}

// prints in this case the exit error for exit

void	ft_putstr_fd_2(char *s1, char *s2, char *s3, int fd)
{
	ft_putstr_fd(s1, fd);
	ft_putstr_fd(s2, fd);
	ft_putendl_fd(s3, fd);
}

void	numeric_argument_error(char *cmd)
{
	ft_putendl_fd("exit", 2);
	ft_putstr_fd_2("minishell: exit: ", cmd, \
	": numeric argument required", 2);
	g_global.status = 255;
	exit(g_global.status);
}

// exits the program with a specified exit number
// entred by the user

void	ft_exit(char **cmd)
{
	g_global.status = 0;
	if (!cmd[1])
	{
		ft_putendl_fd("exit", 1);
		exit(g_global.status);
	}
	if (!cmd[2] && arg_isdigit(cmd[1])
		&& a_to_ll(cmd[1]) >= LLONG_MIN && a_to_ll(cmd[1]) <= LLONG_MAX)
	{
		ft_putendl_fd("exit", 1);
		g_global.status = (a_to_ll(cmd[1]) % 256);
		exit(g_global.status);
	}
	else if (!arg_isdigit(cmd[1]))
		numeric_argument_error(cmd[1]);
	else
	{
		ft_putendl_fd("exit\nminishell: exit: too many arguments", 2);
		g_global.status = 1;
	}
}
