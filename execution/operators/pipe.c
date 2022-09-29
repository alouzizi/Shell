/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 05:15:24 by alouzizi          #+#    #+#             */
/*   Updated: 2022/09/29 05:13:38 by ooumlil          ###   ########.fr       */
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
	if (root->right->s[0][0] == '|')
	{
		create_pipe(root->right);
		exit(g_global.status);
	}
	else
		pipe_cmd_exec(root, 0);
}

void	pipe_left(int *fd, t_tree *root)
{
	dup_function(fd, 1);
	if (isbuiltin(root->left->s))
		exit(g_global.status);
	pipe_cmd_exec(root, 1);
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
	// wait(0);
	if (WIFEXITED(status))
		g_global.status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_global.status = 128 + WTERMSIG(status);
	return (0);
}
