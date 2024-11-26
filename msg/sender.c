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

void send_msg(int qid, int msgtype, char * str){
	struct msgbuf msg;

	msg.mtype = msgtype;

	snprintf(msg.mtext, sizeof(msg.mtext), "%s", str);

	if (msgsnd(qid, (void *) &msg, sizeof(msg.mtext),IPC_NOWAIT) == -1) {
		perror("msgsnd error");
		exit(EXIT_FAILURE);
	}
	//printf("%s", msg.mtext);
}

int main (int argv, char** argc){

	char * str = calloc (SIZE_OF_STRING, sizeof(char));

	int qid;
	int msgkey = 1234;
    int msgtype = 1;

	int character;

	qid = msgget(msgkey, IPC_CREAT | 0666);

	while(fgets(str, SIZE_OF_STRING, stdin)){
		send_msg(qid, msgtype, str);
	}

	free(str);

	return 0;
}