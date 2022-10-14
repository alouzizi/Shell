/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 05:15:24 by alouzizi          #+#    #+#             */
/*   Updated: 2022/10/14 16:50:37 by alouzizi         ###   ########.fr       */
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

void	pipe_cmd_exec(t_tree *root, int index)
{
	if (!index)
	{
		if (isbuiltin(root->right->s))
			exit(g_global.status);
		execute_pipe(root->right->s);
	}
	else
		execute_pipe(root->left->s);
}

void	pipe_right(int *fd, t_tree *root)
{
	dup_function(fd, 0);
	operator_selection(root->right);
	// if (root->right->s[0][0] == '|')
	// {
	// 	create_pipe(root->right);
	exit(g_global.status);
	// }
	// else
	// 	pipe_cmd_exec(root, 0);
	exit (0);
}

void	pipe_left(int *fd, t_tree *root)
{
	dup_function(fd, 1);
	operator_selection(root->left);
	// if (isbuiltin(root->left->s))
	 exit(g_global.status);
	// pipe_cmd_exec(root, 1);
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
		perror("Pipe");
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
	return (0);
}
