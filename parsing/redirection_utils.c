/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 09:34:02 by alouzizi          #+#    #+#             */
/*   Updated: 2022/10/27 03:36:06 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_redirct	*redirection(t_tree **temp, char *s, char **str,t_vars *v)
{
	t_redirct	*r;
	t_redirct	*p;
	t_tree		*tmp;
	int			i;

	i = 0;
	(*temp)->s = malloc(sizeof(char *) * 2);
	if (!(*temp)->s)
	{
		perror(PRMPT_ERR);
		return (NULL);
	}
	(*temp)->s[1] = NULL;
	if ((s[i + 1] == '<' || s[i + 1] == '>') && (s[i] == '<' || s[i] == '>'))
	{
		//ymkn lik tzide 2la kant hdahom xi redirect 5ra
		if (s[i] != s[i + 1])
		{
			ft_putendl_fd("Syntax Error", 2);
			return (NULL);
		}
		(*temp)->s[0] = data(2, s[i], s[i + 1]);
		i++;
	}
	else
		(*temp)->s[0] = data(1, s[i], 0);
	r = redirection_pars(*temp, s, &i, v);
	if(!r || r->j == -1)
		return (NULL);
	if (str)
		r->param = ft_strjoin2d(str, r->param);
	(*temp)->left = newtree(r->file);
	if (s[i] && (s[i] == '>' || s[i] == '<'))
	{
		tmp = (*temp)->left;
		tmp->left = newtree(NULL);
		tmp = tmp->left;
		p = redirection(&tmp, &s[i], NULL,v);
		if(r->param[0])
			r->param = ft_strjoin2d(r->param, p->param);
		i += p->j;
		if(r->param[0])
			tmp->left->left =  newtree(r->param);
	}
	else if(r->param)
		(*temp)->left->left = newtree(r->param);
	r->j = i;
	return (r);
}

t_redirct	*redirection_pars(t_tree *temp, char *s, int *i, t_vars *v)
{
	t_redirct	*p;
	t_redirct	*tmp;
	int			l;

	(*i) += 1;
	p = malloc(sizeof(t_redirct));
	if (!p)
	{
		perror(PRMPT_ERR);
		return (NULL);
	}
	p->j = 1;
	while (s[*i] == ' ')
		(*i)++;
	if (!s[*i] || s[*i] == '>' || s[*i] == '<' || s[*i] == '|' || s[*i] =='&')
	{
		ft_putendl_fd("Syntax Error", 2);
		p->j = -1;
		return (p);
	}
	*i = get_redirect_file(p, s, *i);
	if ((s[*i]) && (s[*i] != '<' || s[*i] != '>' || s[*i] == '|' || s[*i] =='&'))
		p->param = transfer_list_to_2darray(get_cmd(s, &*i, v));
	else
		p->param = NULL;
	l = ft_strlen(temp->s[0]);
	if ((s[*i]) && !ft_strncmp(temp->s[0], &s[*i],l))
	{
		tmp = redirection_pars(temp, s, &*i, v);
		p->param = ft_strjoin2d(p->param, tmp->param);
		p->file = ft_strjoin2d(p->file, tmp->file);
		if (tmp->j == -1)
			return (p);
	}
	return(p);
}

int	get_redirect_file(t_redirct *p, char *str, int i)
{
	int	j;
	int	l;

	j = i;
	p->file = malloc(sizeof(char *) * 2);
	if (!p->file)
		exit(1);
	p->file[1] = NULL;
	while (str[i] && str[i] != ' ')
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

char	**ft_strjoin2d(char **s, char **s0)
{
	char	**s1;
	int		i;
	int		j;

	j = 0;
	if (!s0)
		return (s);
	i = arr_len(s);
	i += arr_len(s0);
	s1 = malloc(sizeof(char *) * (i + 1));
	if (!s1)
		exit(1);
	i = 0;
	while (s[i])
	{
		s1[i] = s[i];
		i++;
	}
	while (s0[j])
		s1[i++] = s0[j++];
	s1[i] = NULL;
	return (s1);
}
