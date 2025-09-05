/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:54:25 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/09/05 11:20:21 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
	int id = fork();
	int num;

	if (id == 0)
	{
	/* --- CHILD ---*/
		num = 1;
	}
	else
	{
	/* --- PROCESS ---*/
		wait(NULL);
		num = 1;
	}
	int i = num;
	while (i < num + 5)
	{
		if (id == 0)
		{
			printf("Child process is printing: ");
			fflush(stdout);
		}
		else
		{
			printf("Parent process is printing: ");
			fflush(stdout);
		}
		printf("%d \n", i);
		fflush(stdout);
		i++;
	}
	return 0;
}