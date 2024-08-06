#include <stdio.h>
#include <stdlib.h>

int main() {
  // stores k value using k
    unsigned int k;

        printf("Please enter k:\t");
        scanf("%u", &k);

        // Check if the inputted k is valid 
        if (k != 1 && k != 2 && k != 4 && k != 8 && k != 16 && k != 32) {
            printf("The integer is invalid. Please try again.\n");
            return -1; // Exit the program with an error
    }
	// num stores the inputted values
    unsigned int num;
    // overallValue stores the combination of the inputted values in binary
    unsigned int overallValue = 0;

    // Calculate the maximum value that can be represented with k bits
    unsigned int maxValue = (1 << (32 / k)) - 1;

    printf("Please enter %u unsigned ints: ", k);

    for (unsigned int i = 0; i < k; i++) {
        scanf("%u", &num);
	// checks if the inputted value is in between the acceptable values
        if (num < 0 || num > maxValue) {
            printf("The integer %u is an invalid input.\n", num);
            return -1; // Exit the program with an error

        } else {
	  // adds to the overall value of the number is acceptable for the size
            overallValue = (overallValue << (32 / k)) | num;
        }
        
    }
    printf("Overall Value = %u\n", overallValue);

    return EXIT_SUCCESS;
}
