/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:04:14 by alouzizi          #+#    #+#             */
/*   Updated: 2022/10/19 02:42:16 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt_display(t_vars *v)
{
	char	*s;

	while (1)
	{
		g_global.signal = 0;
		g_global.is_child = 0;
		s = readline("minishell $ ");
		if (ft_strlen(s) > 1)
			add_history(s);
		if (!s)
		{
			ft_putstr_fd(CTL_D, 1);
			exit (g_global.status);
		}
		if (!check_quotes(s, 0, 0))
			tree(s, v);
		else
		{
			g_global.status = 1;
			ft_putendl_fd("Syntax Error : Check Quotes!", 2);
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_vars	v;

	if (ac != 1 || av[1])
		return (1);
	g_global.status = 0;
	v.env = ft_update_env(env);
	signals_handling();
	prompt_display(&v);
}

// char	**copy_to_env1(char **arr, int arr_size)
// {
// 	char	**env;
// 	int		i;

// 	i = 0;
// 	env = (char **)malloc(sizeof(char *) * (arr_size + 2));
// 	if (!env)
// 		return (NULL);
// 	while (arr[i])
// 	{
// 		env[i] = ft_strdup(arr[i]);
// 		i++;
// 	}
// 	env[i] = 0;
// 	return (env);
// }

// void	add_var(t_vars *v)
// {
// 	char	**copy;
// 	int		arr_size;

// 	arr_size = arr_len(v->env);
// 	copy = ft_arr_copy(v->env);
// 	free_array(v->env);
// 	v->env = copy_to_env1(copy, arr_size);
// 	v->env[arr_size] = strdup("check if added");
// 	v->env[arr_size + 1] = 0;
// 	free_array(copy);
// }

// int	main(int ac, char **av, char **env)
// {
// 	t_vars	v;

// 	if (ac != 1 || av[1])
// 		return (1);
// 	g_global.status = 0;
// 	v.env = ft_update_env(env);
// 	add_var(&v);
// 	for (size_t i = 0; v.env[i]; i++)
// 	{
// 		ft_putendl_fd(v.env[i], 1);
// 	}
// 	add_var(&v);
// 	for (size_t i = 0; v.env[i]; i++)
// 	{
// 		ft_putendl_fd(v.env[i], 1);
// 	}
// 	add_var(&v);
// 	for (size_t i = 0; v.env[i]; i++)
// 	{
// 		ft_putendl_fd(v.env[i], 1);
// 	}
// 	add_var(&v);
// 	for (size_t i = 0; v.env[i]; i++)
// 	{
// 		ft_putendl_fd(v.env[i], 1);
// 	}
// 	for (size_t i = 0; v.env[i]; i++)
// 	{
// 		ft_putendl_fd(v.env[i], 1);
// 	}
// 	add_var(&v);
// 	for (size_t i = 0; v.env[i]; i++)
// 	{
// 		ft_putendl_fd(v.env[i], 1);
// 	}
// 	add_var(&v);
// 	for (size_t i = 0; v.env[i]; i++)
// 	{
// 		ft_putendl_fd(v.env[i], 1);
// 	}
// 	while(1);
// 	// add_var(&v);
	
// }
