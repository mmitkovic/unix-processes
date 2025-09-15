/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_exec_exit_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:17:16 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/09/15 16:31:38 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main()
{
	pid_t pid = fork();
	if (pid == -1)
		return 1;

	if (pid == 0)
	{
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
