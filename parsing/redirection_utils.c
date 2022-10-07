/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 09:34:02 by alouzizi          #+#    #+#             */
/*   Updated: 2022/10/07 16:28:00 by alouzizi         ###   ########.fr       */
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

char	**redirection_parse(char *str , int i)
{
	char **s;
	char **tab;
	i += 1;
	while(str[i++] == ' ');
	while( str[i] && ((str[i] != '>' || str[i] != '<' || str[i] != '|' || str[i] != ' ') && ft_isalnum_redirections(str[i])))
		i++;
	if (str[i] != '<' || str[i] != '>')
	{
		
		s =  transfer_list_to_2darray(get_cmd(str, &i));
		 puts(">>>>>>>>>>>>>");
		 int j =0;
	while(s[j])
		printf("rd = [%s]\n",s[j++]);
	puts(">>>>>>>>>>>>>");
	printf("index = %d\n",i);
	}
	if (str[i] == '<' || str[i] == '>')
	{
		printf("------------\n");
		tab = redirection_parse(str , i);
	// 	int j =0;
	// while(tab[j])
	// 	puts(tab[j++]);
		s = ft_strjoin2d(s, tab);	
	}
	i = 0;
	return (s);
}

char	**ft_strjoin2d(char **s, char **s0)
{
	int	i;
	int j;
	char **s1;

	j = 0;
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

	 j=0;
	 puts(">>>>>>>>>>>>>");
	while(s1[j])
		printf("s = [%s]\n",s1[j++]);
	puts(">>>>>>>>>>>>>");
	return (s1);
}




