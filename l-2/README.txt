Be in the current working directory "l-2".

To compile the program type:
$ make

To run the program type:

$ l-2

or

$ ./l-2

To remove all executables and object codes type:
$ make clean

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
When the program is initially ran (using $ lab02 or $ ./lab02), the user will be prompted with the question:
"Please enter k:"
The user is only allowed to input 1, 2, 4, 8, 16, 32. The user will be prompted with an error if they use any other number and will have to restart the program.


Once the user inputs an integer for k, the user will be prompted with:
"Please enter %u unsigned integers:"

The user must input however many indicated unsigned integers. If the user goes above the listed amount needed, the program will only record the necessary integers. If the user inputs too little integers and presses enter, the program will wait for the user to enter the required amount.

If one of the user's integers goes over the maximum or does not meet the minimum, the program will prompt an error message and the user must restart. For the maximum, the program will only spot the first integer that goes over the limit, likewise for the minimum. 


After all unsigned integers are recorded, the program will return the with an "Overall Value". Here the program will end and the user must type $ lab02 or $ ./lab02 again to restart.
