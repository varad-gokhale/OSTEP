#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void append_to_args(char*, char***, int*);

void process_builtin(int argc, char** argv, char*** path_array, int* path_array_size)
{
	if(argc == 2 && strcmp(argv[1], "exit") == 0)	exit(0);
	
	if(strcmp(argv[1], "cd") == 0)
	{
		if(argc < 3 || argc > 3){
			fprintf(stderr, "illegal use of cd: takes only one directory path\n");
			exit(1);
		}
		
		if(chdir(argv[2]) != 0)
		{
			fprintf(stderr, "no such directory\n");
			exit(1);
		}	
	}
	
	if(strcmp(argv[1], "path") == 0)
	{
		for(int i = 2; i < argc; ++i){
			char temp[strlen(argv[i]) + 2];
			strcat(temp, argv[i]);
			strcat(temp, "/");	
			append_to_args(argv[i], path_array, path_array_size);
		}
	}
		
}
void append_int(int num, char ***arg_array, int* arg_size)
{
	*arg_size += 1;
	int i = *arg_size;
	
	*arg_array = (char**)realloc(*arg_array, sizeof(char*) * i);

	if (*arg_array == 0){
		printf("Out of memory..exiting\n");
		exit(1);
	}
	(*arg_array)[i-1] = NULL; 
	
}
void append_to_args(char* tok, char ***arg_array, int* arg_size)
{
	*arg_size += 1;
	int i = *arg_size;
	int len = strlen(tok);
	
	*arg_array = (char**)realloc(*arg_array, sizeof(char*) * i);
	if (*arg_array == 0){
		printf("Out of memory..exiting\n");
		exit(1);
	}

	*(*arg_array + i-1) = (char*)malloc(sizeof(char) * (len+1));
	if(*(*arg_array + i-1) == 0){
		printf("Out of memory..exiting\n");
		exit(1);
	}
	
	strcpy(*(*arg_array+i-1), tok);
}

void print_arg_array(char **arr, int* size){
	for(int i = 0; i < *size; ++i)
		if(arr[i] != NULL)		printf("%s\n", arr[i]);
}

void free_arg_array(char ***arr, int* size){
	for(int i = 0; i < *size; ++i){
		free(*(*arr + i));
	}
	free(*arr);
	*arr = NULL;
	*size = 0;
}

int main(int argc, char** argv){

/*	FILE *f = fopen("batch.txt", "r");
	if(f == NULL){
		printf("File open unsuccessful. Exiting...\n");
		exit(1);
	}
*/
	char *lineptr = NULL;
	ssize_t r_size = 0;
	size_t line_size = 0;
	char *tok, *saveptr;
	char** arg_array = NULL;
	int arg_array_size = 0;

	char **path_arr = NULL;
	int path_arr_size = 0;
	
	if(argc > 1)
		process_builtin(argc, argv, &path_arr, &path_arr_size);

	while(1){
		printf("gosh> ");
		r_size = getline(&lineptr, &line_size, stdin);
		
		//parse and get stuff 
		if(r_size == EOF){
			printf("\n");
			free(lineptr);
			exit(0);
		}
			
		//parse the string and get the tokens
		
		tok = strtok_r(lineptr, " \t\r\n\v\f", &saveptr);	
		if(tok != NULL){
			append_to_args(tok, &arg_array, &arg_array_size);
		}
		while(tok != NULL){
			tok = strtok_r(NULL, " \t\r\n\v\f", &saveptr);
			if(tok != NULL){
				append_to_args(tok, &arg_array, &arg_array_size);	
			}
		}	
		append_int(0, &arg_array, &arg_array_size);

//		print_arg_array(arg_array, &arg_array_size);
		
		//check if the binary is present in either /bin or /usr/bin
		char filepath[50] = "/bin/";
		strcat(filepath, arg_array[0]);
		if(access(filepath, X_OK) == 0){
			int rc = fork();
			if(rc < 0){
				fprintf(stderr, "fork failed\n");
				exit(1);
			}
			else if(rc == 0){
				execv(filepath, arg_array);
			}
			else{
				wait(NULL);
			}
		}
		else{
			printf("file not found\n");
		}
			
		free_arg_array(&arg_array, &arg_array_size);
		
		free(lineptr);
		lineptr = NULL;
		
	}
	exit(0);
}
