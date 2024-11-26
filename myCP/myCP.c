#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<ctype.h>

#define SIZE_OF_BUFER 32000

int main (int argc, char ** argv){

	printf("%s\n%s\n", argv[1], argv[2]);
 
	int input = open(argv[1], O_RDWR);
	int output = open(argv[2], O_CREAT | O_RDWR | O_TRUNC, 0777);
	
	if (input < 0) {printf("U busturd; err:open file input\n");exit(-1);}
	if (output < 0) {printf("U busturd; err:open file output\n");exit(-1);}

	int fRead = 1;
	int fWrite = 1;
	char str[SIZE_OF_BUFER + 1] = {0};

	while (1){

		fRead = read(input, str, SIZE_OF_BUFER);
		if (fRead < 0) {printf("U busturd; err:read file\n");exit(-1);}

		fWrite = write(output, str, fRead);
		if (fWrite < 0)	{printf("U busturd; err:write file\n");exit(-1);}

		if (fRead < SIZE_OF_BUFER) break;		
	}
	close(input);
	close(output);

	return 0;
}