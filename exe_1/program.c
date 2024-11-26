#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv){

	if (argc < 2){
		printf("Print excute program!\n");
		exit(-1);
	}

	int output = open(argv[1], O_CREAT | O_RDWR | O_TRUNC, 0777);

	dup2(output, STDOUT_FILENO);

	execvp(argv[2], argv + 2);
	printf("GOVNO\n");
	return 0;

}