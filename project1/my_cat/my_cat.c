#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char** argv)
{
	char* buffer = (char*)malloc(sizeof(char) * BUFFER_SIZE);
	char * s;

	for(int i = 1; i < argc; ++i)
	{
		FILE *f = fopen(argv[i], "r");
		if(f == NULL){
			printf("my-cat: cannot open file\n");
			exit(1);	
		}
		while((s = fgets(buffer, BUFFER_SIZE, f)) != NULL)
		{
			printf("%s", s);	
		}		
		fclose(f);
	}
	free(buffer);
	exit(0);
}
