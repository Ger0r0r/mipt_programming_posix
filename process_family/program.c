#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main (){

	int log = open("log.txt", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (log < 0) {printf("Ты дурачок... Oшибка: не смог открыть файл\n");exit(-1);}

	//int fWrite;

	pid_t main_pid, w;
	//int rv;
	int wstatus;
	for (size_t i = 0; i < 10; i++){
		main_pid = fork();
	}

	switch (main_pid) {
	case -1:
		perror("fork");
		exit(1);
		break;

	case 0:
		dprintf(log, "PID c: %d    my parent: %d\n", getpid(), getppid());
		return(2);
		break;

	default:
		w = waitpid(main_pid, &wstatus, WUNTRACED | WCONTINUED);
		if (w == -1){
			perror("waitpid");
			exit(-1);
		}

		dprintf(log, "PID p: %d    my parent: %d    my child: %d with %d\n", getpid(), getppid(), main_pid, WEXITSTATUS(main_pid));
		return(4);
		break;
	}


	close(log);

	return 0;
}