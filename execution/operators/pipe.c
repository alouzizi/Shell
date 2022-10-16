/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 05:15:24 by alouzizi          #+#    #+#             */
/*   Updated: 2022/10/16 10:38:25 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	dup_function(int *fd, int index)
{
	if (index)
	{
		dup2(fd[1], index);
		close(fd[1]);
		close(fd[0]);
	}
	else
	{
		dup2(fd[0], index);
		close(fd[0]);
		close(fd[1]);
	}
}


void	pipe_right(int *fd, t_tree *root, t_vars *v)
{
	dup_function(fd, 0);
	operator_selection(root->right, v);
	exit(g_global.status);
}

void	pipe_left(int *fd, t_tree *root, t_vars *v)
{
	dup_function(fd, 1);
	operator_selection(root->left, v);
	exit(g_global.status);
}

int	create_pipe(t_tree *root, t_vars *v)
{
	int	*fd;
	int	id;
	int	status;

	g_global.is_child++;
	status = 0;
	fd = malloc(sizeof(int) * 2);
	if (pipe(fd) == -1)
		perror("Pipe");
	id = fork();
	if (!id)
		pipe_left(fd, root, v);
	id = fork();
	if (!id)
		pipe_right(fd, root, v);
	close(fd[1]);
	close(fd[0]);
	waitpid(id, &status, 0);
	wait(0);
	exit_status(status);
	return (0);
}
