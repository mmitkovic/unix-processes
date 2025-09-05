/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_pipe_sum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:41:03 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/09/05 18:01:50 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main()
{
	int arr[] = {1, 2, 3, 4, 1, 1};
	int arr_size = sizeof(arr) / sizeof(int); // num of elements in the array
	int fd[2];
	int start, end;

	if (pipe(fd) == -1) 
	{
		return (1);
	}
	pid_t id = fork();
	if (id == -1)
		return (2);

	if (id == 0)
	{
		start = 0;
		end = arr_size / 2;
	}
	else
	{
		start = arr_size / 2;
		end = arr_size;
	}
	
	// sum for every process
	int sum = 0;
	int i = start;
	while (i < end)
	{
		sum += arr[i];
		i++;
	}

	// printf the res
	if (id == 0)
		printf("Calculated sum from child: %d\n", sum);
	else
		printf("Calculated sum from parent: %d\n", sum);

	// sending partial sum from child to parent
	if (id == 0)
	{
		close(fd[0]);
		if (write(fd[1], &sum, sizeof(sum)) == -1)
			return 1;
		close(fd[1]);
	}
	else
	{
		int sum_from_child;
		close(fd[1]);
		if (read(fd[0], &sum_from_child, sizeof(sum_from_child)))
			return 1;
		close(fd[0]);

		int total = sum + sum_from_child;
		printf("Total sum: %d\n", total);
		wait(NULL);
	}
	
	
	return (0);
}