/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:33:00 by ooumlil           #+#    #+#             */
/*   Updated: 2022/09/26 05:31:41 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

// with this you can just type 'minishell'
// it will be counted as a cmd

void	ft_minishell(char **cmd)
{
	int		pid;
	int		status;

	pid = fork();
	if (!pid)
	{
		execve("minishell", cmd, g_global.n_env);
		exit (0);
	}
	else
	{
		g_global.signal = 0;
		waitpid(pid, &status, 0);
	}
	g_global.status = status;
}
