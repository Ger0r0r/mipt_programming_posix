#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

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

int num = 0;
int flag = 1;
char cccc = 0;
pid_t partner_pid;
int output;

void finish_transfer();
void operator_0000();
void operator_0001();
void operator_0010();
void operator_0011();
void operator_0100();
void operator_0101();
void operator_0110();
void operator_0111();
void operator_1000();
void operator_1001();
void operator_1010();
void operator_1011();
void operator_1100();
void operator_1101();
void operator_1110();
void operator_1111();
void print_char(char c);
void read_write_char(int code);

int main (int argc, char ** argv){

	if (argc != 2){
		printf("It's need filename\n");
		exit(EXIT_FAILURE);
	}

	printf("My pid is %i\n", getpid());

	output = open(argv[1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (output < 0) {perror("U busturd; err:open file output\n");exit(EXIT_FAILURE);}

	struct sigaction op01;op01.sa_handler = operator_0000;op01.sa_flags = SA_RESTART;sigaction(SIGBUS, &op01, &op01);
	struct sigaction op02;op02.sa_handler = operator_0001;op02.sa_flags = SA_RESTART;sigaction(SIGFPE, &op02, &op02);
	struct sigaction op03;op03.sa_handler = operator_0010;op03.sa_flags = SA_RESTART;sigaction(SIGILL, &op03, &op03);
	struct sigaction op04;op04.sa_handler = operator_0011;op04.sa_flags = SA_RESTART;sigaction(SIGSEGV, &op04, &op04);
	struct sigaction op05;op05.sa_handler = operator_0100;op05.sa_flags = SA_RESTART;sigaction(SIGSYS, &op05, &op05);
	struct sigaction op06;op06.sa_handler = operator_0101;op06.sa_flags = SA_RESTART;sigaction(SIGXCPU, &op06, &op06);
	struct sigaction op07;op07.sa_handler = operator_0110;op07.sa_flags = SA_RESTART;sigaction(SIGXFSZ, &op07, &op07);
	struct sigaction op08;op08.sa_handler = operator_0111;op08.sa_flags = SA_RESTART;sigaction(SIGPROF, &op08, &op08);
	struct sigaction op09;op09.sa_handler = operator_1000;op09.sa_flags = SA_RESTART;sigaction(SIGTRAP, &op09, &op09);
	struct sigaction op10;op10.sa_handler = operator_1001;op10.sa_flags = SA_RESTART;sigaction(SIGUSR1, &op10, &op10);
	struct sigaction op11;op11.sa_handler = operator_1010;op11.sa_flags = SA_RESTART;sigaction(SIGUSR2, &op11, &op11);
	struct sigaction op12;op12.sa_handler = operator_1011;op12.sa_flags = SA_RESTART;sigaction(SIGALRM, &op12, &op12);
	struct sigaction op13;op13.sa_handler = operator_1100;op13.sa_flags = SA_RESTART;sigaction(SIGCHLD, &op13, &op13);
	struct sigaction op14;op14.sa_handler = operator_1101;op14.sa_flags = SA_RESTART;sigaction(SIGHUP, &op14, &op14);
	struct sigaction op15;op15.sa_handler = operator_1110;op15.sa_flags = SA_RESTART;sigaction(SIGPIPE, &op15, &op15);
	struct sigaction op16;op16.sa_handler = operator_1111;op16.sa_flags = SA_RESTART;sigaction(SIGPOLL, &op16, &op16);

	struct sigaction act;
	act.sa_sigaction = finish_transfer;
	sigaction(SIGCONT, &act, NULL);

	//printf("I wait for a partner\n");
	
	siginfo_t info;
	sigset_t set;
	//int sig;
	//int *sigptr = &sig;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigprocmask(SIG_BLOCK, &set, NULL);

	sigwaitinfo(&set, &info); // get info about sender
	partner_pid = info.si_pid;

	//printf("I conected with partner %i\n", (int)partner_pid);
	//printf("I ready to catch bites!\n");

	kill(partner_pid, SIGINT);

	while (flag){}

	close(output);
	//printf("Work done!\n");
	exit(EXIT_SUCCESS);
}


void finish_transfer() {
	flag = 0;
}

void print_char(char c) {
	printf("%c - ", c);
	for (int i = 7; i >= 0 ; i--){
		printf("%i", c >> i & 1);
	}
	printf("\n");	
}

void operator_0000(){read_write_char(0b0);/* printf("I GET %i - 0000\n", num);print_char(cccc); */}
void operator_0001(){read_write_char(0b1);/* printf("I GET %i - 0001\n", num);print_char(cccc); */}
void operator_0010(){read_write_char(0b10);/* printf("I GET %i - 0010\n", num);print_char(cccc); */}
void operator_0011(){read_write_char(0b11);/* printf("I GET %i - 0011\n", num);print_char(cccc); */}
void operator_0100(){read_write_char(0b100);/* printf("I GET %i - 0100\n", num);print_char(cccc); */}
void operator_0101(){read_write_char(0b101);/* printf("I GET %i - 0101\n", num);print_char(cccc); */}
void operator_0110(){read_write_char(0b110);/* printf("I GET %i - 0110\n", num);print_char(cccc); */}
void operator_0111(){read_write_char(0b111);/* printf("I GET %i - 0111\n", num);print_char(cccc); */}
void operator_1000(){read_write_char(0b1000);/* printf("I GET %i - 1000\n", num);print_char(cccc); */}
void operator_1001(){read_write_char(0b1001);/* printf("I GET %i - 1001\n", num);print_char(cccc); */}
void operator_1010(){read_write_char(0b1010);/* printf("I GET %i - 1010\n", num);print_char(cccc); */}
void operator_1011(){read_write_char(0b1011);/* printf("I GET %i - 1011\n", num);print_char(cccc); */}
void operator_1100(){read_write_char(0b1100);/* printf("I GET %i - 1100\n", num);print_char(cccc); */}
void operator_1101(){read_write_char(0b1101);/* printf("I GET %i - 1101\n", num);print_char(cccc); */}
void operator_1110(){read_write_char(0b1110);/* printf("I GET %i - 1110\n", num);print_char(cccc); */}
void operator_1111(){read_write_char(0b1111);/* printf("I GET %i - 1111\n", num);print_char(cccc); */}

void read_write_char(int code){
	cccc |= (code) << (4 * num);
	num++;

	if (num == 2){
			write(output,  &cccc, 1);
			cccc = 0;
			num = 0;
	}

	kill(partner_pid, SIGINT);
}