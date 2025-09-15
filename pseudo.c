#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main()
{
	int pipes[4][2];
	int pid[4];
	int val = 0;

	// crete pipes
	for(int i = 0; i < 4; i++) {
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
		
	for(int i = 0; i < 4; i++)
	{
		pid[i] = fork();
		if (pid[i] < 0) {
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid[i] == 0) // child
		{
			close(pipes[i][1]); // child doesn't write to its own pipe
			close(pipes[0][0]); // child doesn't read from output pipe
			
			int v = 0;
			if (read(pipes[i][0], &v, sizeof(int)) > 0) {
				v += 3;
				write(pipes[0][1], &v, sizeof(int));
			}

			close(pipes[i][0]);
			close(pipes[i][1]);
			exit (EXIT_SUCCESS);
		}
		// parent
		close(pipes[i][0]); // parent doesn't read from this pipe
		int w = 2;
		write(pipes[i][1], &w, sizeof(int));
		close(pipes[i][1]); // close write end after writing
	}
	close(pipes[0][1]); // close write end of output pipe (no more writers)

	if (read(pipes[0][0], &val, sizeof(int)) > 0) {
		printf("%d\n", val);
	}
	close(pipes[0][0]);
}
