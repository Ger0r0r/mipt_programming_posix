#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define SPECIAL_KEY_FOR_SHM 0xDEADFA11

int main (int argc, char ** argv) {

	int output = open(argv[1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (output < 0) {printf("U busturd; err:open file output\n");exit(-1);}
		
	int segment_id = 0;
	char * shared_memory;
	struct shmid_ds shmbuffer;

	segment_id = shmget(SPECIAL_KEY_FOR_SHM, 0, 0);

	shared_memory = (char*)shmat(segment_id, 0, O_RDWR);

	//printf("Shared memory reattached at address: %p\n", shared_memory);

	shmctl(segment_id, IPC_STAT, &shmbuffer);
	int segment_size = shmbuffer.shm_segsz;

	//printf("Segment size: %d\n", segment_size);

	int fwrite = write(output, shared_memory, segment_size);
	if (fwrite < 0) {printf("U busturd; err: write file\n");exit(-1);}

	shmdt(shared_memory);
	shmctl(segment_id, IPC_RMID, 0);

	return 0;
}