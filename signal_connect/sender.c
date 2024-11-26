#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <errno.h>

/*  !!!ALLERT!!!
В данной программе переопределены сигналы:
SIGBUS	10	0000
SIGFPE	8	0001
SIGILL	4	0010
SIGSEGV	11	0011
SIGSYS	12	0100
SIGXCPU	30	0101
SIGXFSZ	31	0110
SIGPROF	29	0111
SIGTRAP	5	1000
SIGUSR1	16	1001
SIGUSR2	17	1010
SIGALRM	14	1011
SIGCHLD	18	1100
SIGHUP	1	1101
SIGPIPE	13	1110
SIGPOLL	22	1111
SIGINT	2	связь
SIGCONT	25  конец связи
 */

char * str;
int cursor = 0;
int part = 0;
int getted_signal;
int size;
int flag = 1;
pid_t id;

void operator(){}
void print_char(char c);
void send_signal();

int main (int argc, char ** argv){
	
	struct timespec begin,end;
	clock_gettime(CLOCK_MONOTONIC_RAW, &begin);

	printf("My pid is %i\n", getpid());

	if (argc != 3){
		printf("It's must be 2 arguments\n");
		exit(EXIT_FAILURE);
	}

	id = atoi(argv[2]);

	int input = open(argv[1], O_RDWR);
	if (input < 0) {perror("U busturd; err:open file input\n");exit(EXIT_FAILURE);}

	struct stat *data = calloc(1, sizeof(struct stat));
	fstat(input, data);

	size = (int)data->st_size;

	//printf("Size of file = %i\n", size);

	str = calloc(size, sizeof(char));

	if (read(input, str, size) < 0) {perror("U busturd; err:read file\n");exit(EXIT_FAILURE);}

	//printf("Send first signal\n");

	struct sigaction operator;
	operator.sa_handler = send_signal;
	operator.sa_flags = SA_RESTART;
	sigaction(SIGINT, &operator, &operator);

	kill(id, SIGINT); // Send signal to contact and transfer informetion about myself

	//printf("Now I ready to work!\n");

	while (flag){}

	kill(id, SIGCONT);

	clock_gettime(CLOCK_MONOTONIC_RAW, &end);

	double time = (end.tv_sec - begin.tv_sec) + (((double)end.tv_nsec - (double)begin.tv_nsec) / (double)1000000000);

	printf("TIME %lg\n", time);
	printf("SIZE %d\n", size);
	printf("SPEED %f\n", (double)size/time);

	close(input);
	free(str);
	free(data);

	return 0;
}

void print_char(char c) {
	printf("%c - ", c);
	for (int i = 7; i >= 0 ; i--){
		printf("%i", c >> i & 1);
	}
	printf("\n");	
}

void send_signal(){

	if (part == 2){
		part = 0;
		cursor++;
	}

	if (cursor >= size){
		flag = 0;
		return;
	}

	//printf("send signal: part %d, cursor %i\n", part, cursor);

	getted_signal = 0b1111 & (str[cursor] >> (4 * part));
	
	//printf("signal %d\n", getted_signal);

	part++;

	switch (getted_signal){
		case 0:kill(id, SIGBUS);break;
		case 1:kill(id, SIGFPE);break;
		case 2:kill(id, SIGILL);break;
		case 3:kill(id, SIGSEGV);break;
		case 4:kill(id, SIGSYS);break;
		case 5:kill(id, SIGXCPU);break;
		case 6:kill(id, SIGXFSZ);break;
		case 7:kill(id, SIGPROF);break;
		case 8:kill(id, SIGTRAP);break;
		case 9:kill(id, SIGUSR1);break;
		case 10:kill(id, SIGUSR2);break;
		case 11:kill(id, SIGALRM);break;
		case 12:kill(id, SIGCHLD);break;
		case 13:kill(id, SIGHUP);break;
		case 14:kill(id, SIGPIPE);break;
		case 15:kill(id, SIGPOLL);break;
		default:
			perror("HOW U GET HERE\n");
			exit(EXIT_FAILURE);
	}	
}