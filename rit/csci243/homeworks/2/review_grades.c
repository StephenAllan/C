/*****************************************************
 * File: review_grades.c
 *
 * Takes in a listing of grades and returns the number
 * of grades, the average of the grades, the standard
 * deviation of the grades, and sorts and prints them
 * according to their letter grade as per the RIT 2014
 * grading rubric.
 *
 * @author swa9846 : Stephen Allan
 ****************************************************/

#include <stdio.h>	// printf()
#include <ctype.h>	// isdigit()
#include <string.h>	// strlen()
#include <stdlib.h>	// exit status'
#include "stats.h"	// prototypes


/**
 * Takes an array of characters (from the command line)
 * and return its integer value. Chops any decimal point
 * values off with no rounding.
 *
 * @param str	An array of characters
 * @return	The integer value of str
 */
int str_to_int( char* str ) {
    int result = 0;
    for (int i=0; str[i] != '\0'; i++) {
	if (str[i] == '.')
	    return result;
	result = result*10 + str[i] - '0';
    }

    return result;
}

/**
 * main. Takes in an array of grades from the command line
 * and converts them into integers. Prints out how many
 * grades there are and makes calls to find out their
 * average and standard deviation. Calls for a print
 * out of their letter grade groupings.
 *
 * @param argc	The number of command line arguments
 * @param argv	The command line arguments
 * @return	success exit code if no errors
 */
int main(int argc, char* argv[]) {
    int grades[argc];
    int count = 0;
    argc = argc - 1;

    int index = 0, i;
    for (i = 1; i <= argc; i++) {
	_Bool non_negative = 1;
	size_t len = strlen(argv[i]);

	for (int j=0; j < (int)len; j++) {
	    if (!isdigit(argv[i][j])) {
		if (argv[i][j] != '.') {
		    non_negative = 0;
		    count++;
		}
	        break;
	    }
	}
	
	if (non_negative) {
	    grades[index] = str_to_int(argv[i]);
	    index++;
	}
    }

    int size = (sizeof(grades) / sizeof(grades[0])) - (count + 1);
    if (size < 1 || argc <= 0) {
	printf("%s\n%s.\n", "usage: review_grades score1 [score2 ...]",
	       "note: score values are non-negative");
	return EXIT_FAILURE;
    }

    printf("population: %d\n", size);
   
    for (i = 0; i < size; i++)
	printf("%d ", grades[i]);
 
    double mean = average(size, grades);
    printf("\nmean: %.6f\n", mean);
    
    printf("std deviation: %.4f\n", stddev(size, grades, mean));
	
    histogram(size, grades);

    return EXIT_SUCCESS;
}
