#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SIZE_OF_BUFFER 1024

int main(int argc, char *argv[])
{
	int pipefd[2];
	pid_t cpid;
	char buf[SIZE_OF_BUFFER] = {0};
	char text_way[SIZE_OF_BUFFER] = {0};

	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	cpid = fork();
	printf("fork %d\n", cpid);

	if (cpid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (cpid == 0) {    /* Child reads from pipe */
		close(pipefd[1]);          /* Close unused write end */

		printf("child!!! - ");

		int read_value = read(pipefd[0], buf, SIZE_OF_BUFFER);

		snprintf(text_way, SIZE_OF_BUFFER+1, "/%s", buf);

		printf("string - %s\n", text_way);

		close(pipefd[0]);

		exit(execlp("ls", "ls", "-la", text_way, NULL));

	} else {            /* Parent writes argv[1] to pipe */
		close(pipefd[0]);          /* Close unused read end */
		write(pipefd[1], argv[1], strlen(argv[1]));
		printf("write - %s\n", argv[1]);
		close(pipefd[1]);          /* Reader will see EOF */
		wait(NULL);                /* Wait for child */
		exit(EXIT_SUCCESS);
	}
}