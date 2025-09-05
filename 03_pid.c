/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_pid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:31:47 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/09/05 13:14:55 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
	int res;
	int id = fork();
	if (id == 0) {
		printf("In child process getpid: %d and getppid: %d\n", getpid(), getppid());
	}
	else
	{
		res = wait(NULL);
		printf("---\n");
		printf("Parent.\n");
		printf("res returns: %d\n", res);
	}
	if (res == -1) {
		printf("No children to wait for.\n");
	} else {
		printf("%d finished execution.\n", res);
	}
	return 0;
}