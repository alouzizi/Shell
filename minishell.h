/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 02:49:44 by ooumlil           #+#    #+#             */
/*   Updated: 2022/10/13 02:49:44 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <termios.h>
# include <limits.h>
# include "structs.h"
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include "parsing/parsing.h"
# include "execution/execution.h"

# define CTL_D "\033[A\033[12Cexit\n"
# define COUNT 10

t_data	g_global;

#endif