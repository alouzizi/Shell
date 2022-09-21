/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 05:15:24 by alouzizi          #+#    #+#             */
/*   Updated: 2022/09/21 21:10:16 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

void	pipe_cmd_exec(t_tree *root, char **env, int index)
{
	char	**paths;
	char	*path;

	if (!index)
	{
		if (isbuiltin(root->right->s, env))
			exit(0);
		paths = get_path(root->right->s[0], env);
		path = check_access(paths);
		if (path)
			if (execve(path, root->right->s, env))
				print_cnf_error(root->right->s[0]);
	}
	else
	{
		paths = get_path(root->left->s[0], env);
		path = check_access(paths);
		if (path)
			if (execve(path, root->left->s, env))
				print_cnf_error(root->left->s[0]);
	}
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
	g_global.signal = 1;
}

void	pipe_left(int *fd, t_tree *root, char **env)
{
	dup_function(fd, 1);
	if (isbuiltin(root->left->s, env))
		exit(0);
	pipe_cmd_exec(root, env, 1);
	g_global.signal = 1;
}

int	creat_pipe(t_tree *root, char **env)
{
	int	*fd;
	int	id;

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
	waitpid(id, NULL, 0);
	return (0);
}
