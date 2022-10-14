/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 00:00:54 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/14 09:07:37 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	open_heredoc(t_tree *root)
{
	char	*line;
	// char	*tmp_line;
	char	*tmp_heredoc;
	char	*heredoc;

	heredoc = ft_calloc(1, 1);
	line = readline("> ");
	while (ft_strcmp(line, root->s[0]))
	{
		tmp_heredoc = ft_strjoin_no_free(line, "\n");
		heredoc = ft_strjoin_no_free(tmp_heredoc, line);
		free(line);
		// free(tmp_line);
		free(tmp_heredoc);
		line = readline("> ");
	}
	free(line);
	// puts(heredoc);
	free(root->s[0]);
	root->s[0] = heredoc;
}

void	check_heredoc(t_tree *root)
{
	if (root)
	{
		if (!builtincmp(root->s[0], "<<"))
		{
			open_heredoc(root->right);
			puts(root->right->s[0]);
		}
		check_heredoc(root->left);
		check_heredoc(root->right);
	}
	puts("hh");
	return ;
}
