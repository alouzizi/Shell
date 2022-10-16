/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 00:00:54 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/16 00:54:51 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	open_heredoc(t_tree *root)
{
	char	*line;
	char	*tmp_line;
	char	*tmp_heredoc;
	char	*heredoc;

	heredoc = ft_calloc(1, sizeof(char));
	line = readline("> ");
	while (line && ft_strcmp(line, root->s[0]))
	{
		tmp_heredoc = heredoc;
		tmp_line = ft_strjoin_no_free(line, "\n");
		heredoc = ft_strjoin(tmp_heredoc, tmp_line);
		free(line);
		free(tmp_line);
		line = readline("> ");
	}
	free(line);
	free(root->s[0]);
	root->s[0] = heredoc;
}
