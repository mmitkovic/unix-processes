/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_redir_stdout.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:36:30 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/09/15 18:00:35 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>

/* file descriptors --- file */
/*	0					STDIN */
/*	1					STDOUT */
/*	2					STDERR */
/*	3					ping_result.txt*/
int main()
{
	pid_t pid = fork();
	if (pid == -1)
		return 1;

	if (pid == 0)
	{
		int file = open("ping_result.txt", O_WRONLY | O_CREAT, 0777);
		if (file == -1)
			return 2;

		printf("The fd of ping_result.txt: %d\n", file);
		int file2 = dup2(file, STDOUT_FILENO); // replacing STDOUT (1) with ping_result.txt
		printf("The duplicated fd: %d\n", file2);
		close(file);
			
		int err = execlp("ping", "ping", "-c", "1", "google.com", NULL);
		if (err == -1)
			printf("Program in not executed!\n");
	}
	else
	{
		int wstatus;
		wait(&wstatus);
		if (WEXITSTATUS(wstatus)) {
			int status_code = WEXITSTATUS(wstatus);
			printf("Exit code: %d\n", status_code);
			if (status_code == 0)
				printf("Success!\n");
			else
				printf("Fail!\n");
		}
		wait(NULL);
		printf("---\n");
		printf("Post process in parent process.\n");
		printf("---\n");
	}
	return (0);
}
