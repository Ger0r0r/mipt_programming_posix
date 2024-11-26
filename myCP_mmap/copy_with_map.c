#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <sys/mman.h>

int main (int argc, char ** argv){
 
	int input = open(argv[1], O_RDWR);
	int output = open(argv[2], O_CREAT | O_RDWR | O_TRUNC, 0777);
	
	if (input < 0) {perror("U busturd; err:open file input\n");exit(-1);}
	if (output < 0) {perror("U busturd; err:open file output\n");exit(-1);}

	int fWrite = 1;

	int size = lseek(input, 0, SEEK_END);
	lseek(input, 0, SEEK_SET);

	char * memory = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, input, 0);

	fWrite = write(output, memory, size);
	if (fWrite < 0)	{perror("U busturd; err:write file\n");exit(-1);}	
	
	close(input);
	close(output);

	munmap(memory, size);

	return 0;
}

