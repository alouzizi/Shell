/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qouts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:48:36 by alouzizi          #+#    #+#             */
/*   Updated: 2022/09/09 14:48:36 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node *get_cmd(char *s, int *i)
{
	t_node *cmd;

	cmd = NULL;
	while (s[*i])
	{
		if (s[*i] == '"' || s[*i] == '\'')
			handle_qouts(&cmd, s, s[*i], i);
		else if (s[*i] != ' ')
			if (normall_collect(&cmd, s, i) == 1)
				return (cmd);
			if (s[*i] == '|' || s[*i] == '<' || s[*i] == '>' || s[*i] == '&')
				return (cmd);
		while (s[*i] && s[*i] == ' ')
			(*i)++;
	}
	return (cmd);
}

int normall_collect(t_node **cmd, char *s, int *i)
{
	int star;
	int end;
	t_node *node;
	t_node *list;

	list = NULL;
	star = *i;
	while (s[*i] && s[*i] != '\'' && s[*i] != '"' && s[*i] != ' ')
	{
		if (s[*i] == '|' || s[*i] == '<' || s[*i] == '>' || s[*i] == '&')
			break;
		(*i)++;
	}
	end = (*i) - 1;
	node = creat_node(s, star, end);
	if ((s[*i] == '\'' || s[*i] == '"') && s[*i])
	{
		handle_qouts(&list, s, s[*i], i);
		node->s = ft_strjoin(node->s, list->s);
		free(list->s);
		list = NULL;
	}
	ft_lstadd_back(cmd, node);
	return (0);
}


void handle_qouts(t_node **cmd, char *s, char c, int *i)
{
	t_node *node;
	t_node *list;

	int start;
	int end;

	list = NULL;
	(*i)++;
	start = *i;
	while (s[*i] != c && s[*i])
		(*i)++;
	end = (*i) - 1;
		node = creat_node(s, start, end);
	(*i) += 1;
	if ((s[*i] == '\'' || s[*i] == '"') && s[*i])
	{
		handle_qouts(&list, s, s[*i], i);
		node->s = ft_strjoin(node->s, list->s);
		free(list->s);
	}
	if (s[*i] != ' ' && s[*i])
	{
		normall_collect(&list, s, i);
		node->s = ft_strjoin(node->s, list->s);
		free(list->s);
	}
	ft_lstadd_back(cmd, node);
}

t_node *creat_node(char *str, int start, int end)
{
	t_node *node;
	int i;

	i = 0;
	node = malloc(sizeof(t_node));
	if (!node)
		exit(1);
	node->next = NULL;
	node->s = malloc(sizeof(char) * (end - start + 1));
	if (!node->s)
		exit(1);
	while (start <= end)
		node->s[i++] = str[start++];
	node->s[i] = '\0';
	return (node);
}

char **transfer_list_to_2darray(t_node *node)
{
	int i;
	char **tab;

	i = ft_lstsize(node) + 1;
	tab = malloc(sizeof(char *) * i);
	i = 0;
	while (node != NULL)
	{
		tab[i] = node->s;
		i++;
		node = node->next;
	}
	tab[i] = 0;
	return (tab);
}

int check_qouts(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(s[i])
	{
		if (s[i] == '\'')
		{
			i++;
			while(s[i] != '\'' && s[i])
				i++;
			if (s[i] != '\'')
				j = 1;
		}
		if (s[i] == '"')
		{
			i++;
			while(s[i] != '"' && s[i])
				i++;
			if (s[i] != '"')
				j = 1;
		}
		i++;
	}
	return (j);
}