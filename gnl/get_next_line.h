/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 08:27:09 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/14 02:48:11 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "../minishell.h"

size_t	ft_strlen_gnl(const char *s);
void	ft_strcpy_gnl(char *dst, const char *src);
char	*ft_strchr_gnl(const char *s, int c);
void	ft_bzero_gnl(char *s, size_t n);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*get_next_line(int fd);

#endif
