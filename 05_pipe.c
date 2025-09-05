/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:34:15 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/09/05 17:02:11 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int fd[2];
	// fd[0] = read end;
	// fd[1] = write end;
	if (pipe(fd) == -1)
	{
		printf("Error on the pipe.\n");
		return 1;
	}
	int id = fork();
	if (id == -1)
	{
		printf("Error on the fork.\n");
		return 1;
	}
	if (id == 0)
	{
		// child
		// we want to write from child to parent
		close(fd[0]); // we dont read anything from this end in this process
		int x;
		printf("Input a number: ");
		scanf("%d", &x);
		
		// writing to the write end
		if (write(fd[1], &x, sizeof(int)) == -1) {
			printf("Error occured in the write.\n");
			return 1;
		}
		close(fd[1]); // close the write end since we don't use it anymore
	}
	else
	{
		// parent
		close(fd[1]);
		int y;
		if (read(fd[0], &y, sizeof(int)) == -1) {
			printf("Error occured in the read.\n");
			return 1;
		}
		close(fd[0]);
		y *= y;
		printf("From child process: %d\n", y);
	}
	return 0;
}