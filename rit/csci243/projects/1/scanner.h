/*****************************************************
 * File: scanner.h
 *
 * A Header file for the functions in the scanner.c file
 *
 * @author swa9846 : Stephen Allan
 ****************************************************/

#include "classes.h"

#ifndef ERROR_STATE

#define ERROR_STATE 99
#include "transitionMatrix.h"

#endif



/**
 * Takes in a string and a character.
 * Appends the character to the end of the string
 * and re-adds the null terminator.
 *
 * @param str  The string to append to
 * @param c  The character to append
 */
void append( char* s, char c );


/**
 * Returns the character's integer classification specified in classes.h.
 *
 * @param c  The character to classify
 * @return  c's integer classification according to classes.h
 */
int classify( char c );


/**
 * Gathers characters from stdin and declares, according to the transition
 * matrix, whether it was a valid or invalid command.
 * 
 * @param start  The state at which to start reading input.
 * @param accept  The goal state for a valid input.
 * @param states  The max number of states for this matrix given by the tm file.
 * @param tMatrix  The transition matrix which stores the entire parsed tm file.
 */
void scan(int start, int accept, int states, transition tMatrix[states][N_CC]);