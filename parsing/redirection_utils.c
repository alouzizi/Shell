/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 09:34:02 by alouzizi          #+#    #+#             */
/*   Updated: 2022/11/03 01:19:48 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	token_redirection(t_tree *temp, char *s)
{
	int	i;

	i = 0;
	temp->s = malloc(sizeof(char *) * 2);
	if (!temp->s)
	{
		perror(PRMPT_ERR);
		return (-1);
	}
	temp->s[1] = NULL;
	if ((s[i + 1] == '<' || s[i + 1] == '>') && (s[i] == '<' || s[i] == '>'))
	{
		if (s[i] != s[i + 1])
		{
			ft_putendl_fd("Syntax Error", 2);
			return (-1);
		}
		temp->s[0] = data(2, s[i], s[i + 1]);
		i++;
	}
	else
		temp->s[0] = data(1, s[i], 0);
	return (i);
}

int	token_file_param(t_tree **temp, char *s, t_redirct *r, t_vars *v)
{
	t_redirct	*p;
	t_tree		*tmp;
	int			i;

	i = 0;
	if (s[i] && (s[i] == '>' || s[i] == '<'))
	{
		tmp = (*temp)->left;
		tmp->left = newtree(NULL);
		tmp = tmp->left;
		p = redirection(&tmp, &s[i], NULL, v);
		if (!p)
			return (-1);
		if (r->param[0])
			r->param = ft_strjoin2d(r->param, p->param);
		i += p->j;
		if (r->param[0])
			tmp->left->left = newtree(r->param);
	}
	else if (r->param)
		(*temp)->left->left = newtree(r->param);
	return (i);
}

t_redirct	*redirection(t_tree **temp, char *s, char **str, t_vars *v)
{
	t_redirct	*r;
	int			i;
	int			j;

	i = token_redirection(*temp, s);
	if (i == -1)
		return (NULL);
	r = redirection_pars(*temp, s, &i, v);
	if (!r || r->j == -1)
		return (NULL);
	if (str)
		r->param = ft_strjoin2d(str, r->param);
	(*temp)->left = newtree(r->file);
	j = token_file_param(temp, &s[i], r, v);
	if (j == -1)
		return (NULL);
	i += j;
	r->j = i;
	return (r);
}

t_redirct	*redirection_pars(t_tree *temp, char *s, int *i, t_vars *v)
{
	t_redirct	*p;
	int			j;

	(*i) += 1;
	p = malloc(sizeof(t_redirct));
	if (!p)
		return (NULL);
	p->param = NULL;
	p->file = NULL;
	p->j = 1;
	while (s[*i] == ' ' && s[*i])
		(*i)++;
	if (!s[*i] || s[*i] == '>' || s[*i] == '<' || s[*i] == '|' || s[*i] == '&')
	{
		ft_putendl_fd("Syntax Error", 2);
		p->j = -1;
		return (p);
	}
	*i = get_redirect_file(p, s, *i);
	j = check_nextredirect(temp, &s[*i], p, v);
	if (j == -1)
		return (p);
	*i += j;
	return (p);
}

int	check_nextredirect(t_tree *temp, char *s, t_redirct *p, t_vars *v)
{
	t_redirct	*tmp;
	int			l;
	int			i;

	i = 0;
	if ((s[i]) && (s[i] != '<' || s[i] != '>' || s[i] == '|' || s[i] == '&'))
		p->param = transfer_list_to_2darray(get_cmd(s, &i, v));
	l = ft_strlen(temp->s[0]);
	if (s[i] && s[i + 1] && l == 1 && (s[i + 1] == '>' || s[i + 1] == '<'
			|| s[i + 1] == '|' || s[i + 1] == '&'))
		return (i);
	if ((s[i]) && !ft_strncmp(temp->s[0], &s[i], l))
	{
		if (l == 2)
			i += 1;
		tmp = redirection_pars(temp, s, &i, v);
		p->param = ft_strjoin2d(p->param, tmp->param);
		p->file = ft_strjoin2d(p->file, tmp->file);
		if (tmp->j == -1)
			return (-1);
		free(tmp);
	}
	return (i);
}
