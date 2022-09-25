/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 05:15:24 by alouzizi          #+#    #+#             */
/*   Updated: 2022/09/25 04:03:26 by ooumlil          ###   ########.fr       */
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

void	execute_pipe(char **arr, char **env)
{
	char	**paths;
	char	*path;

	paths = get_path(arr[0], env);
	path = check_access(paths);
	if (path)
		if (execve(path, arr, env))
			print_cnf_error(arr[0]);
}

void	pipe_cmd_exec(t_tree *root, char **env, int index)
{
	if (!index)
	{
		if (isbuiltin(root->right->s, env))
			exit(0);
		execute_pipe(root->right->s, env);
	}
	else
		execute_pipe(root->left->s, env);
}

void	pipe_right(int *fd, t_tree *root, char **env)
{
	dup_function(fd, 0);
	if (root->right->s[0][0] == '|')
	{
		creat_pipe(root->right, env);
		exit(0);
	}
	else
		pipe_cmd_exec(root, env, 0);
}

void	pipe_left(int *fd, t_tree *root, char **env)
{
	dup_function(fd, 1);
	if (isbuiltin(root->left->s, env))
		exit(0);
	pipe_cmd_exec(root, env, 1);
}

int	creat_pipe(t_tree *root, char **env)
{
	int	*fd;
	int	id;
	int	status;

	status = 0;
	fd = malloc(sizeof(int) * 2);
	if (pipe(fd) == -1)
		perror("Pipe");
	id = fork();
	if (!id)
		pipe_left(fd, root, env);
	id = fork();
	if (!id)
		pipe_right(fd, root, env);
	close(fd[1]);
	close(fd[0]);
	waitpid(id, &status, 0);
	wait(0);
	g_global.status = status % 256;
	return (0);
}
