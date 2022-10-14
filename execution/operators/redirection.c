/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:46:28 by alouzizi          #+#    #+#             */
/*   Updated: 2022/10/14 17:00:09 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	redirecte_output(t_tree *root, int j)
{
	int	pid;
	int	i;
	int	f;

	i = 0;
	while (root->right->s[i + 1])
	{
		f = open(root->right->s[i], O_CREAT | O_RDONLY | O_TRUNC, 0777);
		if (f < 0)
			return (-1);
		i++;
	}
	if (j)
		f = open(root->right->s[i], O_CREAT | O_WRONLY | O_APPEND, 0777);
	else
		f = open(root->right->s[i], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	pid = fork();
	if (!pid)
	{
		if (f < 0)
			return (-1);
		dup2(f, 1);
		close(f);
		operator_selection(root->left);
		// if (isbuiltin(root->left->s))
		exit(g_global.status);
		// execute_pipe(root->left->s);
	}
	return (wait(0), close(f), 0);
}

int	redirect_intput(t_tree *root)
{
	int	pid;
	int	i;
	int	f;

	i = 0;
	while (root->right->s[i])
	{
		if (access(root->right->s[i], F_OK))
		{
			write(2, "no such file or directory: ", 27);
			ft_putendl_fd(root->right->s[i], 2);
			return (-1);
		}
		if (access(root->right->s[i], R_OK))
		{
			ft_putstr_fd(root->right->s[i], 2);
			write(2, ": Permission denied\n", 20);
			return (-1);
		}
		i++;
	}
	f = open(root->right->s[i - 1], O_RDONLY, 0777);
	pid = fork();
	if (!pid)
	{
		if (f < 0)
			return (-1);
		dup2(f, STDIN_FILENO);
		close(f);
		operator_selection(root->left);
		// if (isbuiltin(root->left->s))
			exit(g_global.status);
		// execute_pipe(root->left->s);
	}
	return (wait(0), close(f), 0);
}
