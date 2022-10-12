/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 09:34:02 by alouzizi          #+#    #+#             */
/*   Updated: 2022/10/12 17:20:38 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_isalnum_redirections(int c)
{
	if ( (c >= 43 && c <= 46) || ((c >= 65 && c <= 95) \
		|| (c >= 97 && c <= 122)) || ((c >= '0') && (c <= '9')))
		return (1);
	return (0);
}


int	get_redirect_file(t_redirct *p, char *str ,int i)
{
	int	j;
	int l;

	j = i;
	p->file = malloc(sizeof(char *) * 2);
	if (!p->file)
		exit(1);
	p->file[1] = NULL;
	while( str[j] && ((str[i] != '>' || str[i] != '<' || str[i] != '|' 
			|| str[i] != ' ') && ft_isalnum_redirections(str[i])))
		i++;
	p->file[0] = malloc(i - j + 1);
	if (!p->file[0])
		exit (1);
	l = 0;
	while (j < i)
		p->file[0][l++] = str[j++];
	p->file[0][l] = '\0';
	return (i);
}

t_redirct	*redirection_parse(t_tree *root,char *str , int *i)
{
	t_redirct	*p;
	t_redirct	*temp;
	char		**tab;
	int			j;

	j = *i;
	j += 1;
	p = malloc(sizeof(t_redirct));
	if (!p)
		exit(1);
	while(str[j] == ' ')
		j++;
	if(!str[j])
	{
		ft_putendl_fd("Syntax Error", 2);
		p->i = -1;
		return (p);
	}
	j = get_redirect_file(p, str, j);
	if ((str[j]) && (str[j] != '<' || str[j] != '>'))
		p->param =  transfer_list_to_2darray(get_cmd(str, &j));
	else
		p->param = NULL;
	if ((str[j]) && (str[j] == '<' || str[j] == '>'))
	{
		temp = redirection_parse(root, str , &j);
		p->param = ft_strjoin2d(p->param, temp->param);
		p->file = ft_strjoin2d(p->file, temp->file);
		if (temp->i == -1)
			return (p);
	}
	*i = j;
	return (p);
}

char	**ft_strjoin2d(char **s, char **s0)
{
	int	i;
	int j;
	char **s1;
		
	j = 0;
	if (!s0)
		return(s);
	i = arr_len(s);
	i += arr_len(s0);
	s1 = malloc(sizeof(char*) *(i + 1));
	if (!s1)
		exit(1);
	i = 0;
	while(s[i])
	{
		s1[i] = s[i];
		i++;
	}
	while(s0[j])
		s1[i++] = s0[j++];
	s1[i] = NULL;
	return (s1);
}
