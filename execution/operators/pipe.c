/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 18:27:05 by alouzizi          #+#    #+#             */
/*   Updated: 2022/12/16 14:45:18 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	dup_function(int fd1, int fd2, int i)
{
	dup2(fd1, i);
	close(fd1);
	close(fd2);
}

void	pipe_right(int *fd, t_tree *root)
{
	dup_function(fd[0], fd[1], 0);
	operator_selection(root->right);
	exit(g_global.status);
}

void	pipe_left(int *fd, t_tree *root)
{
	dup_function(fd[1], fd[0], 1);
	operator_selection(root->left);
	exit(g_global.status);
}

int	create_pipe(t_tree *root)
{
	int	*fd;
	int	id;
	int	status;

	g_global.is_child++;
	status = 0;
	fd = malloc(sizeof(int) * 2);
	if (pipe(fd) == -1)
		return (1);
	id = fork();
	if (!id)
		pipe_left(fd, root);
	id = fork();
	if (!id)
		pipe_right(fd, root);
	close(fd[1]);
	close(fd[0]);
	waitpid(id, &status, 0);
	wait(0);
	exit_status(status);
	free(fd);
	return (0);
}
