In order to compile the program, input:
$ make

---------------------------------------------------------

$ make run
can be used to automatically start ./cat command
---------------------------------------------------------

In order to run the program, you can input these commands:
$ ./cat
OR
$ ./cat -
OR
$ cat
OR
$ cat -

After inputting any of these commands, the system will wait for a user input.
Once a user input is made, the program will output a repeat of the inputted string of characters.
In order to end this continuous loop, do Crtl + d

--------------------------------------------------------------------------------------------

More commands you can input are:
$ ./cat file1.txt
$ ./cat file2.txt

depending on which file you choose (1 or 2), the program will read ONE

If you would like the program to read both inputs:
$ ./cat file1.txt file2.txt

likwise, with 1 or 2 in any order (ex: ./cat file2.txt file1.txt)
--------------------------------------------------------------------------------------------

Additionally, the program will read any quantity of the files the user inputs
EX:
$ ./cat file1.txt file1.txt file1.txt           (and so on)
^ for this instance, the program will output the content of file1 3 times.

--------------------------------------------------------------------------------------------

The last commands you can input is:
$ ./cat - file1.txt
$ ./cat - file2.txt
$ ./cat - file1.txt file2.txt
$ ./cat file1.txt - file2.txt
$ ./cat file1.txt file2.txt -

likewise, in any order (with cat being first) 

This will allow the user to input any string then read back what the chosen file contains

--------------------------------------------------------------------------------------------

To clean the program, input:
$ make clean
