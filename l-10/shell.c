#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFSIZE 4096

/* Retrieve the hostname and make sure that this program is not being run on the main odin server.
 * It must be run on one of the vcf cluster nodes (vcf0 - vcf3).
 */
void check()
{
        char hostname[10];
        gethostname(hostname, 9);
        hostname[9] = '\0';
        if (strcmp(hostname, "csci-odin") == 0) {
                fprintf(stderr, "WARNING: TO MINIMIZE THE RISK OF FORK BOMBING THE ODIN SERVER,\nYOU MUST RUN THIS PROGRAM ON ONE OF THE VCF CLUSTER NODES!!!\n");
                exit(EXIT_FAILURE);
        } // if
} // check

int main()
{
	check();
	setbuf(stdout, NULL); // makes printf() unbuffered
	int n;
	char cmd[BUFFSIZE];
	
	// Project 3 TODO: set the current working directory to the user home directory upon initial launch of the shell
	// You may use getenv("HOME") to retrive the user home directory
	char *dir = getenv("HOME");
	// if the dir is NULL exit or if the chdir(dir) != 0 exit too
	if(dir != NULL){
		if(chdir(dir) != 0){
			perror("directory");
            exit(EXIT_FAILURE);
		}

	} else {
		perror("Home directory not found");
        exit(EXIT_FAILURE);		
	}



	// inifite loop that repeated prompts the user to enter a command
	while (1) {
		printf("1730sh:");
		// Project 3 TODO: display the current working directory as part of the prompt
		char c[BUFFSIZE];
		// getcwd returns the current directory in c
    	if (getcwd(c, sizeof(c)) != NULL) {
			// if the dir is not NULL and dir exist in c print with ~(dir) else print the dir
        	if (dir != NULL && strstr(c, dir) == c) {
            	printf("~%s", c + strlen(dir));
        	} else {
            	printf("%s", c);
        	}
    	} else {
        	perror("getcwd");
        	exit(EXIT_FAILURE);
    	}
		printf("$ ");
		n = read(STDIN_FILENO, cmd, BUFFSIZE);

		// if user enters a non-empty command
		if (n > 1) {
			cmd[n-1] = '\0'; // replaces the final '\n' character with '\0' to make a proper C string
			
			
			// Lab 06 TODO: parse/tokenize cmd by space to prepare the
			// command line argument array that is required by execvp().
			// For example, if cmd is "head -n 1 file.txt", then the 
			// command line argument array needs to be
			// ["head", "-n", "1", "file.txt", NULL].
			

            // gets the first token
			char *token = strtok(cmd, " ");

            // creates the args to store the token
            char *args[BUFFSIZE];

            // creates the variable i to fill args
            int i = 0;

            // checks if token is not NULL
            while(token != NULL){
                // Since token is not null the token will be placed in the args array.
                args[i++] = token;
                // Fill the strtok with NULL means that it will still use the cmd and store it in the token
                token = strtok(NULL, " ");
            }

            // The last token should equal NULL to showcase the end of the array
            args[i] = NULL;
			

			// Lab 07 TODO: if the command contains input/output direction operators
			// such as "head -n 1 < input.txt > output.txt", then the command
			// line argument array required by execvp() needs to be
			// ["head", "-n", "1", NULL], while the "< input.txt > output.txt" portion
			// needs to be parsed properly to be used with dup2(2) inside the child process

			// placeholder to scan args
			i = 0;
			// input and output integers are used to store open input text or output text
			int input = -2;
			int output = -2;

			// scan args
			while(args[i] != NULL){

				// looks for input command
				if(strcmp(args[i], "<") == 0){
					// if there is an input command check the next to see for input.txt
					input = open(args[i + 1], O_RDONLY);

					// if the input can not be opened then print error and exit the code
					if (input == -1) {
                    	perror("open input file");
                    	exit(EXIT_FAILURE);
                	}

					// Remove the "<" and the filename from args
                	args[i] = NULL;
                	args[i + 1] = NULL;
				// looks for output command to print in output file
				} else if (strcmp(args[i], ">") == 0) {
                	// Output redirection
                	output = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);

					// if the output can not be opened then print error and exit the code
					if (output == -1) {
                    	perror("open output file");
                    	exit(EXIT_FAILURE);
                	}

                	// Remove the ">" and the filename from args
                	args[i] = NULL;
                	args[i + 1] = NULL;
				// looks for output command to append in output file
            	} else if (strcmp(args[i], ">>") == 0) {
                	// Output redirection
                	output = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0666);

					// if the output can not be opened then print error and exit the code
					if (output == -1) {
                    	perror("open output file");
                    	exit(EXIT_FAILURE);
                	}

                	// Remove the ">" and the filename from args
                	args[i] = NULL;
                	args[i + 1] = NULL;
            	}
				i++;
			}
			
			
			// Lab 06 TODO: if the command is "exit", quit the program
			
            // if the first args is exit, exit the program
            if(strcmp(args[0], "exit") == 0){
                exit(0);
            }
			 
			// Project 3 TODO: else if the command is "cd", then use chdir(2) to
			// to support change directory functionalities
			else if (strcmp(args[0], "cd") == 0){
				// uses the chdir and if the command returns a 0 throw an error
			  char *path = strtok(args[1],"/");
		 
			  while(path != NULL){
						 if(chdir(path) != 0){
						   if(strcmp(path, "~") == 0){
						       chdir(dir);
						       } else{
						       chdir(path);
						       }
						 }
				     
						 path = strtok(NULL, "/");
				}
				  
			}else{ 
			
			
				// Lab 06 TODO: for all other commands, fork a child process and let
				// the child process execute user-specified command with its options/arguments.
				// NOTE: fork() only needs to be called once. DO NOT CALL fork() more than one time.

            
            	// forks the process
				pid_t pid = fork();

            	// if the forked process equals -1 exit the progran
            	if(pid == -1){
                	exit(EXIT_FAILURE);
            	// if the forked process equals 0 its the child process perform the child process task
            	} else if(pid == 0){
					// Lab 07 TODO: inside the child process, use dup2(2) to redirect
					// standard input and output as specified by the user command
				
					// performs the dup2 if the input was used to open something
					if(input != -2){
						dup2(input, STDIN_FILENO);
					}
					// performs the dup2 if the output was used to open something
					if(output != -2){
						dup2(output, STDIN_FILENO);
					}
				
					// Lab 06 TODO: inside the child process, invoke execvp().
					// if execvp() returns -1, be sure to use exit(EXIT_FAILURE);
					// to terminate the child process
                	if(execvp(args[0], args) == -1){
                    	exit(EXIT_FAILURE);
                	}
            	// if the forked process does not equal 0 or -1 its a parent process wait for the child process
            	}else{
				// Lab 06 TODO: inside the parent process, wait for the child process
				// You are not required to do anything special with the child's 
				// termination status
                	int status;
                	waitpid(pid, &status, 0);
            	}
				close(output);
				close(input);
			} // else

		} // if
	} // while
} // main
