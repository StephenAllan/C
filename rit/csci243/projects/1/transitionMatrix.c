/*****************************************************
 * File: transitionMatrix.c
 *
 * Used to build and/or display to stdin, a 2D array of the transition struct.
 * 
 * @author swa9846 : Stephen Allan
 ****************************************************/

#include <stdio.h>
#include <string.h>

#include "transitionMatrix.h"



int strToInt( char* str ) {
    int result = 0;
    for ( int i=0; str[i] != '\0'; ++i ) {
        if ( str[i] == '.' )
            return result;
        result = ( result * 10 + str[i] - '0' );
    }
    return result;
}


void buildTMatrix( FILE *fp, int states, transition tMatrix[states][N_CC] ) {
    int currState = 0, cClass;
    char buf[256], *ptr, *token;
    while ( ( ptr = fgets( buf, 255, fp ) ) != NULL ) {

        token = strtok( ptr, "\n \n \n" );
        while ( token != NULL ) {

            if ( strlen( token ) > 1 ) {
                transition t;
                sscanf( token, "%d/%d%c", &cClass, &t.nextState, &t.action );
                tMatrix[currState][cClass] = t;
            }
            else
                currState = strToInt( token );

            token = strtok( NULL, " " );
        }
    }

    for ( int i = 0; i < states; ++i ) {
        for ( int j = 0; j < N_CC; ++j ) {
            if ( tMatrix[i][j].action != 'd' && tMatrix[i][j].action != 's' ) {
                tMatrix[i][j].nextState = ERROR_STATE;
                tMatrix[i][j].action = 'd';
            }
        }
    }
}


void displayTMatrix( int states, transition tMatrix[states][N_CC] ) {
    printf( "%s\n%6s", "Scanning using the following matrix:", "0" );

    for ( int i = 1; i < N_CC; ++i ) {
        printf( "%5d", i );
    }
    printf( "\n" );


    for ( int i = 0; i < states; ++i ) {
        printf( "%2d", i );

        for ( int j = 0; j < N_CC; ++j ) {
            printf( "%4d%c", tMatrix[i][j].nextState, tMatrix[i][j].action );
        }

        printf( "\n" );
    }
 }