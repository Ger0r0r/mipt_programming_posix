#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>

#define SIZE_OF_BUFER 32000

char *** find_vector(char * str, int len);

int main (int argc, char** argv) {

	if (argc != 2){printf("Arguments must be 2\n");exit(EXIT_FAILURE);}
	
	int readtxt = open(argv[1], O_RDWR);	
	if (readtxt < 0) {printf("U busturd; err:open file readtxt\n");exit(EXIT_FAILURE);}

	int size_buffer = lseek(readtxt, 0, SEEK_END);

	lseek(readtxt, 0, SEEK_SET);

	char * command = calloc(size_buffer, sizeof(char));

	int fRead = read(readtxt, command, size_buffer);
	if (fRead < 0) {printf("U busturd; err:read file\n");exit(EXIT_FAILURE);}

	if (command[size_buffer - 1] == '\n'){command[size_buffer - 1] = '\0';}
	

	close(readtxt);	

	char *** vector = find_vector(command, fRead);

	int size_vector = 0;

	for (size_t i = 0; vector[i] != NULL; i++){
		size_vector = i;
	}
	
	if (!size_vector){
		if(execvp(vector[0][0], vector[0]) == -1){printf("U busturd; err:exec\n");perror("AAAA -- ");exit(EXIT_FAILURE);}
		free(command);

		return 0;
	}
	

	int pipefd[size_vector][2];
	for (size_t i = 0; i < size_vector; i++){
		if (pipe(pipefd[i]) == -1){
			perror("pipe fail");
			exit(EXIT_FAILURE);
		}
	}

	pid_t cpid;

	cpid = fork();
	if (cpid == -1){
		perror("fork fail");
		exit(EXIT_FAILURE);
	}
	
	for (size_t i = 0; i < size_vector; i++)
	{
		if (cpid == 0){
			if (i == size_vector - 1){
				close(pipefd[i][1]);
				dup2(pipefd[i][0], STDIN_FILENO);
				printf("\n");
				execvp(vector[i + 1][0], vector[i + 1]);
				
				close(pipefd[i][0]);
				_exit(EXIT_SUCCESS);
			}else{
				close(pipefd[i][1]);
				cpid = fork();
				if (cpid == -1){
					perror("fork fail");
					exit(EXIT_FAILURE);
				}
			}
		}else{
			if (i == 0){
				close(pipefd[i][0]);
				
				dup2(pipefd[i][1], STDOUT_FILENO);
				execvp(vector[i][0], vector[i]);
				
				close(pipefd[i][1]);
				wait(NULL);
				exit(EXIT_SUCCESS);
			}else{
				close(pipefd[i][0]);
				dup2(pipefd[i - 1][0], STDIN_FILENO);
				dup2(pipefd[i][1], STDOUT_FILENO);
				execvp(vector[i][0], vector[i]);
				close(pipefd[i - 1][0]);
				close(pipefd[i][1]);
				wait(NULL);
				exit(EXIT_SUCCESS);
			}
		}
	}
	free(command);

	return 0;
}

char *** find_vector(char * str, int len){
	int counter_stiks = 0;
	for (size_t i = 0; i < len; i++){
		counter_stiks = (str[i] == '|') ? counter_stiks + 1 : counter_stiks ;
	}

	int * counter_space = calloc(counter_stiks + 1, sizeof(int));
	int counter = 0;

	for (size_t i = 0; i < len; i++){
		counter_space[counter] = (str[i] == ' ') ? counter_space[counter] + 1 : counter_space[counter];
		counter = (str[i] == '|') ? counter + 1 : counter ;
	}
	

	char *** matrix = calloc(counter_stiks + 2, sizeof(char *));

	for (size_t i = 0; i < counter_stiks + 1; i++){
		matrix[i] = calloc(counter_space[i] + 1, sizeof(char *));
	}

	free(counter_space);
	
	int i = 0;
	int j = 0;
	char *str1, *str2, *token, *subtoken;
    char *saveptr1, *saveptr2;

	for (j = 0, str1 = str;  ; j++, str1 = NULL) {
        token = strtok_r(str1, "|", &saveptr1);
        if (token == NULL)
            break;
        //printf("%d: %s\n", j, token);
        for (str2 = token, i = 0; ; i++, str2 = NULL) {
            subtoken = strtok_r(str2, " ", &saveptr2);
            if (subtoken == NULL)
                break;
            //printf("	 --> %s\n", subtoken);
			matrix[j][i] = subtoken;
			matrix[j][i+1] = NULL;
        }
    }
	return matrix;
}