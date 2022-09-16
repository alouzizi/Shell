/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 05:15:24 by alouzizi          #+#    #+#             */
/*   Updated: 2022/09/15 17:05:12 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int creat_pipe()
{
	int fd[2];
	if (pipe(fd) == -1)
		write(2,"erore",5);
	int id1 = fork();
	if (id1 == 0)
	{
		dup2(fd[1] , STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		execlp("ls", "ls" ,"-la", NULL);
	}
	int id2 = fork();
	if (id2 == 0)
	{
		dup2(fd[0] , STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "pipe.c", NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(id1, NULL, 0);
	waitpid(id2, NULL, 0);
}


int main()
{
	creat_pipe();
}