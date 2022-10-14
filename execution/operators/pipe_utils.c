/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:48:21 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/13 22:49:41 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	execute_pipe(char **arr)
{
	char	**paths;
	char	*path;

	paths = get_path(arr[0]);
	path = check_access(paths);
	if (!path)
	{
		print_cnf_error(arr[0]);
		exit (g_global.status);
	}
	execve(path, arr, g_global.n_env);
}
