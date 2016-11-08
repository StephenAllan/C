/*****************************************************
 * File: tokenize.c
 *
 * Reads input from a tm file to build a transition matrix. Reads input from
 * stdin with the goal of reaching the accepting state if all entered characters
 * form a valid command. Reaches the error state if an invalid input series is
 * entered.
 *
 * @author swa9846 : Stephen Allan
 ****************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "classes.h"
#include "transitionMatrix.h"
#include "scanner.h"



/**
 * Reads in a transition matrix from a given file.
 * Creates a 2D array of structs that represent that data.
 * Prints out the parsed matrix to stdout.
 * Collects input from stdin and splits it up into valid and invalid tokens.
 *
 * @param argc  The number of command line arguments
 * @param argv  The command line arguments
 * @return  success exit code, 0 if no errors
 */
int main( int argc, char* argv[] ) {
    
    // Check for a given filename
    if ( argc == 1 ) {
        fprintf( stderr, "usage: ./tokenize tmfile\n" );
        return EXIT_FAILURE;
    }
    
    // Check that the file is real and readable
    FILE *fp = fopen( argv[1], "r" );
    if ( fp == NULL ) {
        perror( argv[1] );
        return EXIT_FAILURE;
    }


    // Gather info from the first three lines
    char buf[15], *ptr;

    ptr = fgets( buf, 14, fp );
    int states = strToInt( strtok( ptr, "states \n" ) );

    ptr = fgets( buf, 14, fp );
    int start = strToInt( strtok( ptr, "start \n" ) );

    ptr = fgets( buf, 14, fp );
    int accept = strToInt( strtok( ptr, "accept \n" ) );


    // Define, populate, and print out the transition matrix
    transition tMatrix[states][N_CC];

    buildTMatrix( fp, states, tMatrix );

    displayTMatrix( states, tMatrix );


    // Collect input from stdin and tokenize it according to the tMatrix
    scan( start, accept, states, tMatrix );


    // Close the file and exit the program
    fclose( fp );

    return 0;
}