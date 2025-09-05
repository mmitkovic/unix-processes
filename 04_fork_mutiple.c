/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_fork_mutiple.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:34:13 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/09/05 14:56:46 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

int main ()
{
	setbuf(stdout, NULL); // unbuffered to reduce interleaving surprises
	pid_t id_1 = fork();
	pid_t id_2 = fork();

	if (id_1 == 0)
	{
		if (id_2 == 0)
			printf("Child of the child process | id_2: %d\n", id_2);
		printf("---\n");	
		printf("id_1: %d\n", id_1);
		if (id_2 > 0)
			printf("First child | id_2: %d\n", id_2);
	}
	else
	{
		printf("\n---PARENT---\n");
		int i = 1;
		if (id_2 > 0 && id_1 > 0)
			i++;
		printf("%d\n", i);
		printf("Parent id_1: %d\n", id_1);
		printf("Parent id_2: %d\n", id_2);
	}
	return 0;
}