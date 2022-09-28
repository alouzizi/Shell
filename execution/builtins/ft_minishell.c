/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:33:00 by ooumlil           #+#    #+#             */
/*   Updated: 2022/09/27 20:38:15 by ooumlil          ###   ########.fr       */
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
	status = 0;
	if (!pid)
		execve("minishell", cmd, g_global.n_env);
	else
	{
		g_global.signal = 0;
		g_global.is_child = 1;
		waitpid(pid, &status, 0);
	}
	exit_status(status);
}
