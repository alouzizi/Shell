/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:50:01 by alouzizi          #+#    #+#             */
/*   Updated: 2022/09/09 14:50:01 by alouzizi         ###   ########.fr       */
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
# include "libft/libft.h"
# include "parsing/parsing.h"
# include "execution/execution.h"

# define CTL_D "\033[A\033[12Cexit\n"
# define COUNT 10

typedef struct s_data
{
	int		signal;
	int		status;
	char	**n_env;
}	t_data;

t_data	g_global;

#endif