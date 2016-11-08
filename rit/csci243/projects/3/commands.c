/*****************************************************
 * File: commands.c
 *
 * Internal commands handled by mysh.c
 *
 * @author swa9846 : Stephen Allan
 ****************************************************/


#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"



void help() {

    printf( "\nThe following are valid mysh commands.  Type 'help' to see this list.\n\n" );

    printf( "%10s  Repeat command N. (N is in history)\n", "!n" );
    printf( "%10s  Enter any non-internal command to have it run through bash.\n", "BASH" );
    printf( "%10s  Enter the name of a file to view it.\n", "Filename" );
    printf( "%10s  Display the help menu with possible shell commands.\n", "help" );
    printf( "%10s  Display the last N commands [execute with -h N].\n", "history" );
    printf( "%10s  Exit the shell.\n", "quit" );
    printf( "%10s  Toggle verbose mode [on|off].\n", "verbose" );
}


void addToHistory( char *history[], char *buf, int entry, int maxSize ) {

    if ( !maxSize )
        return;
    else if ( entry <= maxSize )
            history[entry-1] = strdup( buf );
    else {
        free( history[0] );
        for ( int i = 0; i < maxSize - 1; ++i )
            history[i] = history[i+1];
        history[maxSize-1] = strdup( buf );
    }
}


void displayHistory( char *history[], int numCmd, int maxSize ) {

    for ( int i = 0; i < maxSize; ++i ) {
        printf( "%6d: %s", numCmd, history[i] );
        ++numCmd;
    }
}


void quit( char *history[], int maxSize, int status ) {

    for ( int i = 0; i < maxSize; ++i )
            free( history[i] );

    printf( "\n" );
    exit( status );
}