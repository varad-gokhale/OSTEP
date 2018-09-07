#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void run_length_decode(char* line, char new_file)
{
	if(new_file){
		printf("%c", *line++);
		printf("%c", *line++);
	}
	
	while(*line){
		unsigned int count = 0;
		count |= *line++;
		count |= *line++ << 8;
		count |= *line++ << 16;
		count |= *line++ << 24;
		for(int i = 0; i < count; ++i)
			printf("%c", *line);
		line += 1;
	}
}

int main(int argc, char** argv)
{

	if(argc <= 1){
		printf("my-unzip: file1 [file2 ...]\n");
		exit(1);
	}

	char* line = NULL;
	size_t line_size = 0;
	int ret_line_size = 0;
	FILE *f;

	for(int i = 1; i < argc; ++i){
		f = fopen(argv[i], "r");
		if(f == NULL){
			printf("Could not open file\n");
			exit(1);
		}
		char new_file = 1;
		while((ret_line_size = getline(&line, &line_size, f)) != -1){
			run_length_decode(line, new_file);
			new_file = 0;
			free(line);
			line = NULL;
		}
	}
	exit(0);
}
