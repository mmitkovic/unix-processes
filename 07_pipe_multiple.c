/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_pipe_multiple.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:08:25 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/09/09 16:18:36 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main()
{
	int arr[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
	int arr_size = sizeof(arr) / sizeof(int);
	int fd[2];
	
	if (pipe(fd) == -1) {
		perror("pipe");
		return 1;
	}
	
	for (int k = 0; k < 3; k++) {
		pid_t pid = fork();
		if (pid < 0) {
			perror("fork");
			return 1;
		}
		if (pid == 0) {
			// --- CHILD ---
			// compute start and end
			int start = k * (arr_size / 3);
			int end;
			if (k == 0)
				end = arr_size / 3;
			else if (k == 1)
				end = 2 * (arr_size / 3);
			else
				end = arr_size;
			int val = 0;
			for (int i = start; i < end; i++) val += arr[i];
			//child writes one int to the pipe
			close(fd[0]); // child doesn't read
			if (write(fd[1], &val, sizeof(val)) != sizeof(val)) {
				perror("write");
			}
			close(fd[1]);
			_exit(0);
		}
		//paretn keeps looping to fork the next child	
	}
	// --- PARENT ---
	close(fd[1]); // parent doesn't wire

	int total = 0;
	for (int i = 0; i < 3; i++) {
		int temp;
		if (read(fd[0], &temp, sizeof(int)) == -1)
			perror("read");
		total += temp;
	}
	// Reap children
	for (int i = 0; i < 3; i++)
		wait(NULL);
	printf("Total: %d\n", total);
	return 0;
}