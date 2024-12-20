/**
 * This project takes in the arguments that is attached to the 
 * linux command when compiling it. It will take in the input
 * file and write to the output file what is contained in the 
 * input file except with the correct number of lines and/or
 * text
*/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_SIZE 1048576

bool checkIfFile(char *string);

void headExc(char *buffer,int buffer_size, int lines, int bytes, int fileDes);

char buffer[BUFFER_SIZE];

bool isInteger(const char *str);

int main(int argc, char *argv[])
{
    // Open a file in write-only mode with permissions 0644 (read/write for owner, read for others)
    int fileDescriptor = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int fd = STDIN_FILENO;
    int n = 1048576;
    int c = 1048576;
    ssize_t bytes_read;
    // scans through the arguments
    for(int i = 1; i < argc; i++){ 
        // if the argument is a file write call the headExc to write to file with the max n and max c
        if(checkIfFile(argv[i])){ 
            fd = open(argv[i], O_RDONLY);

            if(fd == -1){

                write(STDERR_FILENO, "no file\n", 8);
                exit(EXIT_FAILURE);
            }
            bytes_read = read(fd, buffer, BUFFER_SIZE);
            headExc(buffer, (int)bytes_read, n, c, fileDescriptor);
        }
        // if the argument contains a -n make sure that there is an interger next and set the max number of lines
        if(strcmp(argv[i],"-n") == 0){
            i++;
            if(!isInteger(argv[i])){
                printf("No Integer provided");
                exit(EXIT_FAILURE);
            }
            n = atoi(argv[i]);
            if(n < 0){
                printf("Integer needs to be positive");
                exit(EXIT_FAILURE);
            }
        }
        // if the argument contains a -c make sure that there is an interger next and set the max number of character
        if(strcmp(argv[i],"-c") == 0){
            i++;
            if(!isInteger(argv[i])){
                printf("No Integer provided");
                exit(EXIT_FAILURE);
            }
            c = atoi(argv[i]);
            if(c < 0){
                printf("Integer needs to be positive");
                exit(EXIT_FAILURE);
            }
        }
        // if - do nothing
        if(strcmp(argv[i],"-") == 0){

        }

    }

    close(fd);
    return 0;
}

// checks if a string is a file
bool checkIfFile(char *string)
{
    char end[] = ".txt";
    int string_length = strlen(string);
    int end_length = 4;
    // if the end length is longer than the string then we know it cant be a .txt file
    if(end_length > string_length){
        return false;
    }
    // checks if its a text file starting from the end
    for (int i = 0; i < end_length; i++){ 
        if (string[string_length - i] != end[end_length - i]){
            return false;
        }
    }
    return true;
}

// preforms the print to file, printing the number of lines and character depending on the limit
void headExc(char *buffer,int buffer_size, int lines, int bytes, int fileDes) {
    int lineCount = 0;
    int byteCount = 0;
    const char *text = "\n";
    // writes to output document character by character
    for(int i = 0; i < buffer_size; i++) {
        // if the lines max is reached end it
        if (lines > 0 && lineCount == lines) {
            break;
        }
        // if max bytes is reached then end it
        if (bytes > 0 && byteCount == bytes) {
            break;
        }

        // writes the single charater to output
        write(fileDes, &buffer[i], 1);


        // counting the lines
        if (buffer[i] == '\n') {
            lineCount++;
        }
        // counting the bytes
        byteCount++;
    }
    // writes to document the new line to make space for next text
    write(fileDes, text, 1);
}

// checks if the string is an interger
bool isInteger(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }

    char* endptr;
    strtol(str, &endptr, 10);

    // Check if the entire string was consumed and it represents a valid integer
    return (*endptr == '\0');
}
