/*****************************************************
 * File: commands.h
 *
 * Header file for commands.c
 *
 * @author swa9846 : Stephen Allan
 ****************************************************/


#define MAX_READ 255



/*
 * Display internal commands supported by mysh. Shows support of external
 * bash commands and file viewing.
 */
void help();


/*
 * Adds a string to the list of previously entered commands of length maxSize
 * (10 by default).
 * 
 * @param history - The list of N previous commands
 * @param buf - The string to ass to history
 * @param entry - The index into history when below maxSize
 * @param maxSize - The number of commands to keep in history
 */
void addToHistory( char *history[], char *buf, int entry, int maxSize );


/*
 * Displays maxSize commands held in history
 * 
 * @param history - The list of N previous commands
 * @param numCmd - The first command number in history
 * @param maxSize - The number of commands to keep in history
 */
void displayHistory( char *history[], int numCmd, int maxSize );


/*
 * Frees all memory allocated in history, prints a new line for the terminal
 * prompt, and exits the main program with exit code status.
 * 
 * @param history - The list of N previous commands
 * @param maxSize - The number of commands to keep in history
 * @param status - The exit status
 */
void quit( char *history[], int maxSize, int status );