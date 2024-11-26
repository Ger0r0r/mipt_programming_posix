#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define SIZE_OF_STRING 100

struct msgbuf {
	long mtype;
	char mtext[SIZE_OF_STRING];
};

void get_msg(int qid, int msgtype) {
	struct msgbuf msg;

	if (msgrcv(qid, (void *) &msg, sizeof(msg.mtext), msgtype, MSG_NOERROR | IPC_NOWAIT) == -1) {
		if (errno != ENOMSG) {
			perror("msgrcv");
			exit(EXIT_FAILURE);
		}
		//printf("No message available for msgrcv()\n");
	} else
		printf("%s", msg.mtext);
}

int main (int argv, char** argc){

	int qid;
	int msgkey = 1234;
    int msgtype = 1;

	int character;

	qid = msgget(msgkey, IPC_CREAT | 0666);

	while(1){
		get_msg(qid, msgtype);
	}

	return 0;
}