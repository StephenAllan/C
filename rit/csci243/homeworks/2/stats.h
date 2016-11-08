/******************************************************
 * File: stats.h
 *
 * A Header file for the functions in the stats.c file
 * 
 * @author swa9846 : Stephen Allan
 *****************************************************/


/**
 * Find the average (mean) of the grades collection.
 * 
 * @param size		The size of the collection
 * @param grades	The collection to find the average of
 * @return		The average of all the grades
 */
double average(int size, int grades[]);

/**
 * Find the standard deviation of the grades collection.
 *
 * @param size		The size of the collection
 * @param grades	The collection to find the standard dev of
 * @param mean		The average (mean) of the collction
 * @return		The standard deviation of all the grades
 */
double stddev(int size, int grades[], double mean);

/**
 * Sorts the collection of grade values into groupings of letter grades.
 * Prints a table showing the frequencies of each grade in the collection.
 *
 * @param size		The size of the collection
 * @param grades	The collection to sort into letter grades
 */
void histogram(int size, int grades[]);
