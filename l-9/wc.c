/**
 * This project takes in the arguments that is attached to the 
 * linux command when compiling it. It will take in the input
 * file find the number of lines, words, and character print
 * that into the output file
*/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 1048576

bool checkIfFile(char *string);

void headExc(char *buffer,int buffer_size, int lines, int bytes, int fileDes);

char buffer[BUFFER_SIZE];

bool isInteger(const char *str);

int countWords(const char *str);

int countLines(const char *str);

int main(int argc, char *argv[])
{
    // Open a file in write-only mode with permissions 0644 (read/write for owner, read for others)
    int fileDescriptor = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int fd = STDIN_FILENO;
    bool l = false;
    bool c = false;
    bool w = false;
    int totalL = 0;
    int totalC = 0;
    int totalW = 0;
    ssize_t bytes_read;
    int times = 0;
    char targetCharL = 'l';
    char targetCharW = 'w';
    char targetCharC = 'c';
    // checks all the arguments in the argv array
    for(int i = 1; i < argc; i++){ 

        // checks if the argument is a file
        if(checkIfFile(argv[i])){ 

            // if the first argument is a file we want to find l,c,w
            if(i == 1){
                l = true;
                c = true;
                w = true;
            }

            // opens the file
            fd = open(argv[i], O_RDONLY);

            // if it fails to open file
            if(fd == -1){

                write(STDERR_FILENO, "no file\n", 8);
                exit(EXIT_FAILURE);
            }

            // reads from the file
            bytes_read = read(fd, buffer, BUFFER_SIZE);

            // writes the files name in the file before printing the numbers
            char fileprint[20]; 
            snprintf(fileprint, sizeof(fileprint), "%s\n", argv[i]);
            // Get the length of the string
            size_t lengthFile = strlen(fileprint);
            write(fileDescriptor, &fileprint, lengthFile);
            // if number of lines needs to be found find it
            if(l){
                int line = countLines(buffer);
                totalL = totalL + line;
                printf("lines = %d\n", line);
                char number_str[20]; 
                snprintf(number_str, sizeof(number_str), "%d ", line);

                // Get the length of the string
                size_t length = strlen(number_str);
                write(fileDescriptor, &number_str, length);
            }
            // if number of words needs to be found find it
            if(w){
                int words = countWords(buffer);
                totalW = totalW + words;
                printf("words = %d\n", words);
                char number_str[20]; 
                snprintf(number_str, sizeof(number_str), "%d ", words);
                // Get the length of the string
                size_t length = strlen(number_str);
                write(fileDescriptor, &number_str, length);
            }
            // if number of characters needs to be found find it
            if(c){
                char number_str[20]; 
                snprintf(number_str, sizeof(number_str), "%ld ", bytes_read);
                printf("characters = %ld\n", bytes_read);
                // Get the length of the string
                size_t length = strlen(number_str);
                write(fileDescriptor, &number_str, length);
                totalC = totalC + bytes_read;
            }
            // makes sure the next file gets printed on the next line
            char str_next[20]; 
            snprintf(str_next, sizeof(str_next), "\n");
            size_t length = strlen(str_next);
            write(fileDescriptor, &str_next, length);
            times++;
        }

        // finds if l w c are parameters to know if the need to find l,w,c
        if(argv[i][0] == '-'){ 
            for (int j = 1; argv[i][j] != '\0'; j++) {
                if (argv[i][j] == targetCharL) {
                    l = true;
                }
                if (argv[i][j] == targetCharW) {
                    w = true;
                }
                if (argv[i][j] == targetCharC) {
                    c = true;
                }
            }
        }
        

    }
    // if multiple files are detected print the total value last
    if(times > 1){
        char number_str[20];
        snprintf(number_str, sizeof(number_str), "%d %d %d", totalL, totalW, totalC);

        // Get the length of the string
        size_t length = strlen(number_str);
        write(fileDescriptor, &number_str, length);
    }
    close(fd);
    return 0;
}

// counts lines
int countLines(const char *str) {
    int lineCount = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            // counts the number of new lines detected in the string
            lineCount++;
        }
    }

    // If the string does not end with a new line, add one to count the last line
    if (str[0] != '\0' && str[strlen(str) - 1] != '\n') {
        lineCount++;
    }

    return lineCount;
}

// checks if its a file
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

// checks if a number is an integer
bool isInteger(const char *str) {
    // if the string is empty its not a interger
    if (str == NULL || *str == '\0') {
        return false;
    }

    char* endptr;
    strtol(str, &endptr, 10);

    // Check if the entire string was consumed and it represents a valid integer
    return (*endptr == '\0');
}

//counts the amount of words in a string
int countWords(const char *str) {
    int wordCount = 0;
    bool inWord = false;

    while (*str) {
        // isspace checks it the chara is a space
        if (isspace(*str)) {
            // Character is a space or whitespace
            inWord = false;
        } else if (!inWord) {
            // Character is the start of a new word
            inWord = true;
            wordCount++;
        }
        str++;
    }

    return wordCount;
}
