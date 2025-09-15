/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 13:59:12 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/09/15 14:13:53 by mmitkovi         ###   ########.fr       */
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
		execlp("ping", "ping", "-c", "3", "google.com", NULL);
		// nothing get executed after exec functions
		printf("THIS SHOULD NOT PRINT ON TERMINAL\n");
	}
	else
	{
		wait(NULL);
		printf("---\n");
		printf("Post process in parent process.\n");
		printf("---\n");
	}
	return (0);
}
