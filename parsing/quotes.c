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

#include "parsing.h"

t_node	*get_cmd(char *s, int *i)
{
	t_node	*cmd;

	cmd = NULL;
	while (s[*i])
	{
		if (s[*i] == '"' || s[*i] == '\'')
			handle_quotes(&cmd, s, s[*i], i);
		else if (s[*i] != ' ')
		{
			if (s[*i] == '|' || s[*i] == '<' || s[*i] == '>' || s[*i] == '&')
				return (cmd);
			if (normall_collect(&cmd, s, i) == 1)
				return (cmd);
		}
		while (s[*i] && s[*i] == ' ')
			(*i)++;
	}
	return (cmd);
}

int	normall_collect(t_node **cmd, char *s, int *i)
{
	t_node	*node;
	t_node	*list;
	int		star;
	int		end;

	list = NULL;
	star = *i;
	while (s[*i] && s[*i] != '\'' && s[*i] != '"' && s[*i] != ' ')
	{
		if (s[*i] == '|' || s[*i] == '<' || s[*i] == '>' || s[*i] == '&')
			break ;
		(*i)++;
	}
	end = (*i) - 1;
	node = create_node(s, star, end);
	if ((s[*i] == '\'' || s[*i] == '"') && s[*i])
	{
		handle_quotes(&list, s, s[*i], i);
		node->s = ft_strjoin(node->s, list->s);
		free(list->s);
		list = NULL;
	}
	ft_lstadd_back(cmd, node);
	return (0);
}

void	handle_quotes(t_node **cmd, char *s, char c, int *i)
{
	t_node	*node;
	t_node	*list;
	int		start;
	int		end;

	list = NULL;
	(*i)++;
	start = *i;
	while (s[*i] != c && s[*i])
		(*i)++;
	end = (*i) - 1;
	printf("start = %c | %d\n", s[start], start);
	if (s[*i] == '"')
	{
		node = create_node(NULL, 0, 0);
		node->s = expand_$(s, start, 0);
	}
	else
		node = create_node(s, start, end);
	(*i) += 1;
	if ((s[*i] == '\'' || s[*i] == '"') && s[*i])
	{
		handle_quotes(&list, s, s[*i], i);
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

t_node	*create_node(char *str, int start, int end)
{
	t_node	*node;
	int		i;

	i = 0;
	node = malloc(sizeof(t_node));
	if (!node)
		exit(1);
	node->next = NULL;
	if(end != 0)
	{
		node->s = malloc(sizeof(char) * (end - start + 1));
		if (!node->s)
			exit(1);
		while (start <= end)
			node->s[i++] = str[start++];
		node->s[i] = 0;
	}
	return (node);
}

char	**transfer_list_to_2darray(t_node *node)
{
	char	**tab;
	int		i;

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

int	check_quotes(char *s, int i, int j)
{
	while (s[i])
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\'' && s[i])
				i++;
			if (s[i] != '\'')
				j = 1;
		}
		if (s[i] == '"')
		{
			i++;
			while (s[i] != '"' && s[i])
				i++;
			if (s[i] != '"')
				j = 1;
		}
		i++;
	}
	return (j);
}


char *expand_$(char *s, int start, int lvl)
{
	char *expand;
	t_node *node;
	char *dollar;
	int j = 0;
	int i = start;

	node = malloc(sizeof(t_node));
	while(( lvl == 1 || s[start] != '$') && s[start] != '"')
		start++;
	expand = malloc( start - i + 1);
	while(i < start)
		expand[j++] = s[i++];
	expand[j] = '\0'; 
	if (s[i] == '$')
	{
		dollar = expand_$2(s, i);
		if (dollar)
			expand = ft_strjoin(expand, dollar);
	}
	return(expand);
}

char *expand_$2(char *s, int i)
{
	int j;
	int start;
	char *dollar;

	j = start = 0;
	if (ft_isdigit(s[i + 1]) || (!ft_isalpha(s[i + 1]) && s[i + 1] != '_') )
	{
		if(ft_isdigit(s[i + 1]))
			return (expand_$(s, i + 2, 0));
		else
			return(expand_$(s, i , 1));
	}
	else if (ft_isdigit(s[i + 1]) || ft_isalpha(s[i + 1]) || s[i + 1] == '_' )
	{
		++i;
		while(ft_isdigit(s[i]) || ft_isalpha(s[i]) || s[i] == '_' )
		{
			start++;
			i++;
		}
		dollar = malloc(start + 1);
		i -= start;
		while(start--)
			dollar[j++] = s[i++];
		dollar[j] = '\0';
		dollar = getenv(dollar);
	}
	if(s[i] && s[i] != '"')
	{
		if(!dollar)
			return(expand_$(s, i,0));
		dollar = ft_strdup(dollar);
		dollar = ft_strjoin(dollar,expand_$(s, i,0));
	}
	return (dollar);
}