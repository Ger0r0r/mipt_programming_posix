#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main (int argc, char ** argv){

	if (argc != 2){
		printf("Must enter directory's path\n");
		exit(EXIT_FAILURE);
	}

	DIR * path = opendir(argv[1]);

	if(path == NULL){
		printf("wrong directory's path\n");
		exit(EXIT_FAILURE);
	}

	struct dirent * data = calloc(1, sizeof(struct dirent));

	data = readdir(path);

	while (data){
		if (DT_DIR == data->d_type){
			printf("%s\n", data->d_name);	
		}
				
		data = readdir(path);
	}

	free(data);

	return 0;
}
