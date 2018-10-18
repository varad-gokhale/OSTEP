	1) Run a while loop and get input using getline() from either the stdin or batch.txt
	2)  If EOF is hit at any point, exit the program gracefully (exit(0))
	3)  To parse the input, use strtok/strtok_r and break input into constituent pieces
	4)  To execute commands, look into fork(), exec() and wait()/waitpid()
	5)  Use the execv flavor of exec specifically. It shouldn't return. If it does, something is wrong.
	6)  The most challenging part is getting the arguments correctly specified

	7)  Paths ==> path variable must be specified to describe the set of directories to search for executables
	8)  To check if a particular file exists in a directory and is executable, consider the access() system call
	9)  Built in commands are == exit, cd and path. Do not execute built-in commands like other programs. 
	10) Shell redirection should be supported. 
	11) Parallel commands should be supported.
	12) Print error message on errors
