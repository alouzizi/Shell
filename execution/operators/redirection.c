/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:46:28 by alouzizi          #+#    #+#             */
/*   Updated: 2022/12/17 01:58:43 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	redirecte_output(t_tree *root, int j)
{
	t_tree	*n;
	int		i;
	int		f;

	i = 0;
	n = root->left->left;
	while (root->left->s[i + 1])
	{
		f = open(root->left->s[i++], O_CREAT | O_RDONLY | O_TRUNC, 0777);
		if (f < 0)
			return (print_error(root->left->s[i - 1]));
	}
	if (j)
		f = open(root->left->s[i], O_CREAT | O_WRONLY | O_APPEND, 0777);
	else
		f = open(root->left->s[i], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (f < 0)
		return (print_error(root->left->s[i]));
	if (n && (!builtincmp(n->s[0], "cd") || !builtincmp(n->s[0], "exit")))
		return (simple_cmd(root->left->left));
	return (redirection_dup(root, 1, f));
}

int	print_error(char *s)
{
	ft_putstr_fd("minishell: ", 2);
	perror(s);
	return (-1);
}

int	redirect_intput(t_tree *root)
{
	t_tree	*n;
	int		i;
	int		f;

	i = 0;
	n = root->left->left;
	while (root->left->s[i])
	{
		if (access(root->left->s[i], F_OK))
			return (print_error(root->left->s[i]));
		if (access(root->left->s[i], R_OK))
			return (print_error(root->left->s[i]));
		i++;
	}
	f = open(root->left->s[i - 1], O_RDONLY, 0777);
	if (f < 0)
		return (print_error(root->left->s[i - 1]));
	if (n && (!builtincmp(n->s[0], "cd") || !builtincmp(n->s[0], "exit")))
		return (simple_cmd(root->left->left));
	return (redirection_dup(root, 0, f));
}

int	redirection_dup(t_tree *root, int o, int f)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror(PRMPT_ERR);
		return (-1);
	}
	if (pid == 0)
	{
		dup2(f, o);
		close(f);
		if (root->left->left)
			operator_selection(root->left->left);
		exit(g_global.status);
	}
	close(f);
	wait(0);
	return (0);
}

int	operator_selection(t_tree *root)
{
	if (!builtincmp(root->s[0], "|"))
		return (create_pipe(root));
	else if (!builtincmp(root->s[0], ">"))
		return (redirecte_output(root, 0));
	else if (!builtincmp(root->s[0], "<"))
		return (redirect_intput(root));
	else if (!builtincmp(root->s[0], ">>"))
		return (redirecte_output(root, 1));
	else if (!builtincmp(root->s[0], "<<"))
		return (redirect_intput(root));
	else
		return (simple_cmd(root));
	return (0);
}
