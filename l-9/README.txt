How to COMPILE:
$ make

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

How to RUN:
All inputs below are applicable 

-------------------------------
HEAD

$ ./head 
$ ./head - 
$ ./head -n 5 
$ ./head -c 5 - 
$ ./head -n 5 file1.txt - 
$ ./head -c 5 - file2.txt 
$ ./head file1.txt 
$ ./head file1.txt file2.txt 
$ ./head -n 5 file1.txt 
$ ./head -n 5 file1.txt file2.txt 
$ ./head -c 3 file1.txt 
$ ./head -c 3 file1.txt file2.txt

---------------------------------
WC

$ ./wc 
$ ./wc - 
$ ./wc -lw - 
$ ./wc -c -w file1.txt - file2.txt 
$ ./wc file1.txt 
$ ./wc file1.txt file2.txt 
$ ./wc -c file1.txt file2.txt 
$ ./wc -lc file1.txt file2.txt 
$ ./wc -cl file1.txt file2.txt 
$ ./wc -cwl file1.txt file2.txt 
$ ./wc -w -l file1.txt file2.txt 
$ ./wc -l -cw file1.txt file2.txt 

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

How to CLEAN:
$ make clean 

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Program outputs:

When scanning the files, once inputting in a command such as $ ./wc -cl file1.txt , information about the output will print in the terminal, while a summary of the output will print in the file called "output.txt"
(only the $ ./wc command will output something in the terminal. $ ./head commands will directly put the output in "output.txt")

^^ IMPORTANT NOTE: OUTPUTTS ARE LOCATED IN "output.txt" for both $ ./head and $ ./wc

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

OTHER:

file1.txt and file2.txt were used for personal testing 
