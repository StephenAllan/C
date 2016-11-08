/*****************************************************
 * File: transitionMatrix.h
 *
 * A Header file for the functions in the transitionMatrix.c file
 *
 * @author swa9846 : Stephen Allan
 ****************************************************/

#include "classes.h"

#define ERROR_STATE 99



/**
 * Transition struct.
 * Represents a node in the transition matrix. Data is read in from a tm file
 * provided on the command line.
 * 
 * int nextState  The state to travel to next after the action is preformed.
 * char action  's' to save the data and path or 'd' to discard it.
 */
typedef struct transition {

    int nextState;
    char action;

} transition;


/**
 * Takes an array of characters and return its integer value.
 * Chops any decimal point values off with no rounding.
 *
 * @param str  An array of characters
 * @return  The integer value of str
 */
int strToInt( char* str );


/**
 * Reads line by line (starting at line 3) from the passed file, parsing it
 * into individual tokens. Creates a transition struct based on the static
 * layout of these tokens. If a transition was not read in from the tm file,
 * creates a struct to the error state, 99. Saves the transition to a 2D array,
 * tMatrix, with the current state as the row and the character class of that
 * token as the column.
 *
 * @param fp  A pointer to the tm file given through the command line.
 * @param states  The max number of states for this matrix given by the tm file.
 * @param tMatrix  The transition matrix which stores the entire parsed tm file.
 */
void buildTMatrix( FILE *fp, int states, transition tMatrix[states][N_CC] );


 /**
 * Prints out the 2D array, tMatix, according to provided guidelines.
 * Loops through the transition matrix and prints the nextState of the current
 * transition as well as the action to be preformed.
 *
 * @param states  The max number of states for this matrix given by the tm file.
 * @param tMatrix  The transition matrix which stores the entire parsed tm file.
 */
void displayTMatrix( int states, transition tMatrix[states][N_CC] );