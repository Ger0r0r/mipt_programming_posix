#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<ctype.h>

int search_number (char * str, int pos);

#define SIZE_OF_BUFER 32000

int main (int argc, char ** argv){

	printf("%s\n%s\n", argv[1], argv[2]);
 
	int input = open(argv[1], O_RDWR);
	int output = open(argv[2], O_CREAT | O_RDWR | O_TRUNC, 0777);
	
	if (input < 0) {printf("U busturd; err:open file input\n");exit(-1);}
	if (output < 0) {printf("U busturd; err:open file output\n");exit(-1);}

	int fRead = 1;
	int fWrite = 1;
	int cursor = 0;
	int length = 0;
	int sum = 0;
	int flag = 0;
	int flag_of_end = 0;

	char str[SIZE_OF_BUFER + 1] = {0};

	//printf("\n\nStart new cicle #%d \t\t with fRead = %d\n", counter, fRead);

	fRead = read(input, str, SIZE_OF_BUFER);
	if (fRead < 0) {printf("U busturd; err:read file\n");exit(-1);}

	//printf("I have read str: %s\nI get fRead = %d\n", str, fRead);

	while (1){
		length = search_number(str, cursor);

		if (length == 0){
			memcpy(str, (void *)(str + cursor), SIZE_OF_BUFER - cursor);

			fRead = read(input, (void *)(str + SIZE_OF_BUFER - cursor), cursor);
			if (fRead < 0) {printf("U busturd; err:read file\n");exit(-1);}

			str[SIZE_OF_BUFER - cursor + fRead] = '\0';

			cursor = 0;

			continue;
		}
		if (length < 0){
			length *= -1;
			flag_of_end = 1;
		}

		sum = 0;
		flag = 1;
		/*
		0001 - include number
		0010 - include sign
		0100 - TRASH
		*/
		for (int i = 0; i < (length - 1); i++){
			if ((str[cursor + i] == '+') || (str[cursor + i] == '-')){
				if ((flag & 2) != 2){
					flag |= 2;
					continue;
				}
				else{
					flag |= 4;
					continue;
				}
			}
				
			
			if (!isdigit(str[cursor + i])) {
				flag |= 4;
			}
			else {
				flag |= 1;
				sum += str[cursor + i] - '0';
			}
		}
		
		if ((flag & 4) == 4){
			fWrite = write(output, (void *)(str + cursor), length - 1);
		}
		else if ((sum % 3) == 0){
			if (str[cursor + length - 2] == '0' ||str[cursor + length - 2] == '5'){
				fWrite = write(output, "BizzBuzz", 8);
			}
			else {
				fWrite = write(output, "Bizz", 4);
			}	
		}
		else if (str[cursor + length - 2] == '0' ||str[cursor + length - 2] == '5'){
			fWrite = write(output, "Buzz", 4);
		}
		else {
			fWrite = write(output, (void *)(str + cursor), length - 1);
		}
		
		
		if (fWrite < 0) {
			printf("U busturd; err:write file\n");exit(-1);
		}

		if (flag_of_end == 1) break;
		
		
		fWrite = write(output, (void *)(str + cursor + length - 1), 1);
		if (fWrite < 0) {
			printf("U busturd; err:write file\n");exit(-1);
		}

		
		cursor += length;
	}
	close(input);
	close(output);

	return 0;
}

//==================================================//

int search_number (char * str, int pos){
	int len = pos;
	//unsigned char flag = 1;
	while (1){
		if (isspace(str[pos])) return (pos - len + 1);
		if (pos == SIZE_OF_BUFER) return 0;
		if ((str[pos] == EOF) | (str[pos] == '\0')) return (len - pos - 1);
		pos++;
	}	
}

//==================================================//
