/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 00:29:26 by ooumlil           #+#    #+#             */
/*   Updated: 2022/09/26 07:58:55 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# define CNF ": command not found"
# define PRMPT_ERR "minishell: "
# include "../minishell.h"

//pwd
void				ft_pwd(void);

//echo
void				ft_echo(char **cmd);

//env
void				shlvl_handling(int i);
void				ft_update_env(char **env);
void				ft_env(void);

//export
char				**ft_arr_copy(char **arr);
char				*ft_strjoin_no_free(char *s1, char const *s2);
int					check_arg_export(char *arg, int i);
int					arr_len(char **arr);
int					ft_isalnum_export(int c);
int					check_var_name(char *arg);
int					has_value(char *arg, int *ptr);
void				print_export_error(char *arg);
void				sort_array_alphabetically(char **arr);
void				add_var_to_env(char *var);
void				add_to_value(char *arg, int i, int ptr);
void				update_or_add_var(int b, int ptr, char *var);
void				add_to_env(char *var, int b);
void				add_variable(char *arg);
void				add_to_export(char *cmd);
void				sort_array_alphabetically(char **arr);
void				print_export(char **arr);
void				ft_export(char **cmd);

//unset
void				ft_unset(char **cmd);
void				remove_from_env(char *cmd);

//cd
void				ft_cd(char **cmd);
void				cd_error_printing(char *arg);
char				*get_env(char *str);

//exit
unsigned long long	a_to_ull(char *str);
void				ft_exit(char **cmd);

//pipe
// void				pipe_right(int *fd, t_tree *root, char **env);
// void				pipe_left(int *fd, t_tree *root, char **env);
// int					creat_pipe(t_tree *root, char **env);

//executing
char				**get_path(char *s);
char				*check_access(char	**paths);
int					builtincmp(char *s1, char *s2);
int					isbuiltin(char **cmd);
void				print_cnf_error(char *cmd);
void				execute(char **s);
void				commands_execution(char **paths, char **cmd);

#endif