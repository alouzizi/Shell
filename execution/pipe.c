/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 05:15:24 by alouzizi          #+#    #+#             */
/*   Updated: 2022/09/15 19:30:19 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int creat_pipe(t_tree *root, char **env)
{
	int *fd;
	fd = malloc(sizeof(int) * 2);
	if (pipe(fd) == -1)
		write(2,"error\n",6);
	int id1 = fork();
	if (id1 == 0)
	{
		dup2(fd[1] , STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		//excute root->left
		execute(root->left->s, env);
	}
	int id2 = fork();
	if (id2 == 0)
	{
		dup2(fd[0] , STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (root->right->s[0][0] == '|')
			creat_pipe(root->right ,env);
		//excute root->right
		else
			execute(root->right->s, env);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(id1, NULL, 0);
	waitpid(id2, NULL, 0);
}