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
#define COUNT 10
typedef struct s_data
{
	int	signal;
	int	status;
}	t_data;
t_data	g_global;

typedef struct tree
{
	struct tree *right;
	struct tree *left;
	char	**s;
}t_tree;

void print_tree(t_tree *root, int space);
void	tree(char *s);
t_tree	*newtree(char **content);
char	*data(int j, char c, char c2);

//signals
void				ctl_c(int signum);
void				sig_reset(void);
void				signals_handling(void);

//env
void				shlvl_handling(char **env, int i);
void				ft_update_env(char **env);
void				ft_env(char **env);

//store cmd
t_node	*get_cmd(char *s, int *l);
int		check_qouts(char *s);
int		normall_collect(t_node **cmd, char *s, int *i);
void	handle_qouts(t_node **cmd, char *s, char c, int *i);
t_node	*creat_node(char *str, int start, int end);
t_node	*expand_$(char *s ,int start, int j);
char	**transfer_list_to_2darray(t_node *node);

#endif