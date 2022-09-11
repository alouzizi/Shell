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

# ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
# include <string.h>
#include "libft/libft.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <termios.h>
# include <limits.h>
# define CTL_D "\033[A\033[12Cexit\n"

void    prompt_display(char **env);

//store cmd
t_node	*get_cmd(char *s, int *l);
int		check_qouts(char *s);
int		normall_collect(t_node **cmd, char *s, int *i);
void	handle_qouts(t_node **cmd, char *s, char c, int *i);
t_node	*creat_node(char *str, int start, int end);

#endif