/*******************************************************
 * File: stats.c
 *
 * Can compute the average, the standard deviation,
 * and print out grades in their letter grade groupings.
 *
 * @author swa9846 : Stephen Allan
 ******************************************************/

#include <stdio.h>	// printf()
#include <math.h>	// sqrt()
#include "stats.h"	// prototypes


double average(int size, int grades[]) {
    float sum = 0.0;
    for (int i=0; i < size; i++)
	sum += grades[i];

    return sum / size;
}

double stddev(int size, int grades[], double mean) {
    float variance = 0.0; 
    for(int i=0; i < size; i++)
	variance += (grades[i] - mean) * (grades[i] - mean);

    return sqrt(variance / (size - 1));
}

void histogram(int size, int grades[]) {
    int range[10] = { 0 };
    char* letter_grades[] = {"A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F"};
    
    int i;
    for (i = 0; i < size; i++) {
	int curr = grades[i];

	if (curr >= 92)
	    range[0]++;
	else if (curr >= 89)
	    range[1]++;
	else if (curr >= 85)
	    range[2]++;
	else if (curr >= 82)
	    range[3]++;
	else if (curr >= 79)
	    range[4]++;
	else if (curr >= 75)
	    range[5]++;
	else if (curr >= 72)
	    range[6]++;
	else if (curr >= 69)
	    range[7]++;
	else if (curr >= 60)
	    range[8]++;
	else
	    range[9]++;
    }

    for (i = 0; i < 10; i++) {
	printf("%s:\t%d\n", letter_grades[i], range[i]);
    }
}
