#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv){
	FILE *f = fopen("batch.txt", "r");
	if(f == NULL){
		printf("File open unsuccessful. Exiting...\n");
		exit(1);
	}
	char *lineptr = NULL;
	int r_size;
	size_t line_size = 0;

	while((r_size = getline(&lineptr, &line_size, f)) != -1){
		printf("%s\n", lineptr);
		free(lineptr);
		lineptr = NULL;
	}
	fclose(f);
	exit(0);

}
