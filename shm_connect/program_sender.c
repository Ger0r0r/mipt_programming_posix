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

	int input = open(argv[1], O_RDWR);
	if (input < 0) {printf("U busturd; err:open file input\n");exit(-1);}
		
	int segment_id = 0;
	char * shared_memory;
	struct shmid_ds shmbuffer;

	const int shared_segment_size = lseek(input, 0, SEEK_END) + 1;

	///DOLBAEB it need lseek to begin

	segment_id = shmget(SPECIAL_KEY_FOR_SHM, shared_segment_size, IPC_CREAT | 0777 );

	shared_memory = (char*)shmat(segment_id, NULL, O_RDWR);

	//printf("Shared memory attached at address: %p\n", shared_memory);

	shmctl(segment_id, IPC_STAT, &shmbuffer);
	int segment_size = shmbuffer.shm_segsz;

	//printf("Segment size: %d\n", segment_size);
	//printf("Shared segment size : %d\n", shared_segment_size);



	int fRead = read(input, shared_memory, shared_segment_size);
	if (fRead < 0) {printf("U busturd; err:read file\n");exit(-1);}
	
	printf("%s\n", shared_memory);

	shmdt(shared_memory);

	return 0;
}