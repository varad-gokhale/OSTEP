#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char** argv)
{

	if(argc <= 1){
		printf("my-grep: searchterm [file ...]\n");
		exit(1);
	}
	else if(argc == 2){
		char* buffer = (char*)malloc(sizeof(char) * 512);
		char* s;
		while(1)
		{
			s = fgets(buffer, 512, stdin);
			if(strcmp(s, argv[1]) == 10 && (strlen(s)-1) == strlen(argv[1]))
				printf("%s", s);
		}
				
	}
	else{
		char* line = NULL;
		size_t line_size = 0;
		int size_returned = 0;
		FILE *f = NULL;
		
		for(int i = 2; i < argc; ++i){
			f = fopen(argv[i], "r");
			if(f == NULL){
				printf("my-grep: cannot open file\n");
				exit(1);
			}
			while((size_returned = getline(&line, &line_size, f)) != -1){
				if(strstr(line, argv[1]))
			        {
					printf("%s", line);
					free(line);
					line = NULL;
				} 
			}
			fclose(f);
		}
	}
	
	exit(0);
}
