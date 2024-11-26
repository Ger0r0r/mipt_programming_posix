#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

void operator_1();
void operator_2();

int main () {

	struct sigaction op1;
	struct sigaction op2;

	op1.sa_handler = operator_1;
	op2.sa_handler = operator_2;

	op1.sa_flags = SA_RESTART;
	op2.sa_flags = SA_RESTART;

	sigaction(SIGUSR1, &op1, &op1);
	sigaction(SIGUSR2, &op2, &op2);

	printf ("My pid: %i\n", getpid());

	int i = 0;

	while (1){
		sleep(10);
		printf("time %i\n", i);
		i++;		
	}
	return 0;
}

void operator_1(){
	printf("Hello!!!\n");
}

void operator_2(){
	printf("London is the capital of Great Britain\n");
}