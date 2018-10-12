#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void run_length_encoding(char* line)
{
	int count = 1;
	int len = strlen(line);
	for(int i = 1; i <= len; ++i)
	{
		if(line[i] != line[i-1])
		{
			fwrite(&count, 4, 1, stdout);
			//printf("count is: %d\n",count);	
			fwrite(line+i-1, 1, 1, stdout);
			//printf("char is: %c\n", line[i-1]);
			count = 1;
		}
		else
			count += 1;
	}
}

int main(int argc, char** argv)
{
	if(argc == 1){
		printf("my-zip: file1 [file2 ...]\n");
		exit(1);
	}
	printf("\r\b");

	char* line = NULL;
	size_t line_size = 0;
	int ret_size = 0;

	FILE *r = NULL;
	
	for(int i = 1; i < argc; ++i)
	{
		r = fopen(argv[i], "r");
		if(r == NULL){
			printf("my-zip: file1 [file2 ...]\n");
			exit(1);
		}
		while((ret_size = getline(&line, &line_size, r) != -1)){
			run_length_encoding(line);
			free(line);
			line = NULL;
		}
	}
		
	exit(0);
}
