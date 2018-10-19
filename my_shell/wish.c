#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv){

/*	FILE *f = fopen("batch.txt", "r");
	if(f == NULL){
		printf("File open unsuccessful. Exiting...\n");
		exit(1);
	}
*/
	char *lineptr = NULL;
	int r_size;
	size_t line_size = 0;

	while(1){
		printf("wish> ");
		while((r_size = getline(&lineptr, &line_size, stdin)) != -1){
		//	printf("%s", lineptr);
			
			free(lineptr);
			lineptr = NULL;
		}
	}
	exit(0);

}
