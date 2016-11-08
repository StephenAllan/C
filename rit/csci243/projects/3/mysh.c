/*****************************************************
 * File: mysh.c
 *
 * A simple interactive shell program.
 *
 * @author swa9846 : Stephen Allan
 ****************************************************/


#define _GNU_SOURCE

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/wait.h>

#include "commands.h"

#define BANG "!"
#define HELP "help"
#define HISTORY "history"
#define OPEN_FILE "less"
#define QUIT "quit"
#define VERBOSE "verbose"



/*
 * Parses all command line arguments, accepting all valid flags (-v, -h). Loops
 * for user imput. Checks against internal commands, executes if possible. If
 * input does not match any internal command, forks a new process and exec's for
 * a bash shell command. If no command is found, attempts to read a file where
 * filename = input. Exits on Ctrl-D or "quit" command, frees all saved history.
 * 
 * @param argc - int containing number of command line arguments
 * @param argv - array of strings containing:
 *          (optional) turn verbose on [-v] (off by default)
 *          (optional) set size of history [-h N] (10 by default)
 * @return - 1 on failure, 0 otherwise
 */
int main( int argc, char *argv[] ) {
    bool verbose = false;
    int maxHistory = 10, opt;

    // parse command-line arguments
    opterr = 0;
    while ( (opt = getopt (argc, argv, "vh:")) != -1 ) {

        switch ( opt ) {
          case 'v':
            verbose = true;
            break;

          case 'h':
            maxHistory = atoi( optarg );
            if ( maxHistory < 0 )
                maxHistory = 10;
            break;

          case '?':
            if ( optopt == 'h' )
              fprintf( stderr, "Option -%c requires an argument.\n", optopt );
            else if ( isprint (optopt) )
              fprintf( stderr, "Unknown option `-%c'.\n", optopt );
            else
              fprintf( stderr, "Unknown option character `\\x%x'.\n", optopt );
            exit( 1 );

          default:
            fprintf( stderr, "Invalid Input.\n" );
            exit( 1 );
        }
    }


    char *c, *tok, buf[MAX_READ+1], cmd[MAX_READ+1];
    char str[MAX_READ+1], *history[maxHistory-1], *args[MAX_READ+1];
    size_t read = MAX_READ;
    int b, id, i, status, minHistory;

    // accept commands from stdin
    for ( int prompt = 1; true; ++prompt ) {
        printf( "mysh[%d]> ", prompt );
        c = fgets( buf, read, stdin );

        if ( c == NULL ) {
            if ( prompt <= maxHistory )
                quit( history, prompt-1, 0 );
            else
                quit( history, maxHistory, 0 );
        }

        else if ( buf[0] == '\n' ) {
            prompt -= 1;
            continue;
        }

        minHistory = prompt - maxHistory + 1;
        sscanf( buf, "%s \n", cmd );

        // Handle internal commands
        if ( verbose )
            printf( "\tcommand: %s\n", buf );

        // Check bang before modifying history
        if ( cmd[0] == BANG[0] ) {
            printf("~%s~", cmd);
            b = 0;
            sscanf( buf, "%c%d\n", cmd, &b );

            if ( b == 0 || (b >= minHistory && b < prompt) ) {
                char *bang;
                if ( b == 0 ) {
                    if ( prompt == 1 ) {
                        addToHistory( history, buf, prompt, maxHistory );
                        continue;
                    }
                    else if ( prompt <= maxHistory )
                        bang = strdup( history[prompt-2] );
                    else
                        bang = strdup( history[maxHistory-1] );
                }
                else if ( prompt <= maxHistory )
                    bang = strdup( history[b - 1] );
                else
                    bang = strdup( history[b - (minHistory-1)] );

                sscanf( bang, "%s \n", cmd );
                strncpy( buf, bang, MAX_READ );
                free( bang );
            }

            else {
                addToHistory( history, buf, prompt, maxHistory );
                continue;
            }
        }

        if ( strcmp(cmd, VERBOSE) == 0 ) {
            sscanf( buf, "%s %s\n", cmd, str );
            if ( strcmp(str, "on") == 0 )
                verbose = true;
            else if ( strcmp(str, "off") == 0 )
                verbose = false;
            else
                printf( "usage: verbose [on|off]\n" );

            addToHistory( history, buf, prompt, maxHistory );
            continue;
        }

        // add the command to the history list
        addToHistory( history, buf, prompt, maxHistory );

        // continue internal commands
        if ( strcmp(cmd, HELP) == 0 )
            help();

        else if ( strcmp(cmd, HISTORY) == 0 ) {
            if ( prompt <= maxHistory )
                displayHistory( history, 1, prompt );
            else
                displayHistory( history, minHistory, maxHistory );
        }

        else if ( strcmp(cmd, QUIT) == 0 ) {
            if ( prompt <= maxHistory )
                quit( history, prompt, 0 );
            else
                quit( history, maxHistory, 0 );
        }


        // Handle external commands
        else {
            // spawn a new process to exec
            id = fork();

            switch( id ) {
              case -1:
                perror( "fork" );
                if ( prompt <= maxHistory )
                    quit( history, prompt, 1 );
                else
                    quit( history, maxHistory, 1 );

              case 0:
                // gather all command-line arguments
                if ( verbose )
                    printf( "\tinput command tokens:\n" );

                tok = strtok( buf, " \n" );
                for ( i = 0; tok != NULL; ++i ) {
                    if ( verbose )
                        printf( "\t%d: %s\n", i, tok );

                    args[i] = tok;
                    tok = strtok( NULL, " \n" );
                }
                args[i] = (char *)0;

                // call exec with entered tokens
                if ( verbose ) {
                    printf( "\twait for pid %d: %s\n", getpid(), cmd );
                    printf( "\texecvp: %s\n", cmd );
                }
                execvp( cmd, args );

                // If exec fails:
                args[0] = OPEN_FILE;
                args[1] = cmd;
                args[2] = (char *)0;

                execvp( OPEN_FILE, args );
            }

            if ( id == 0 )
                _exit( 0 );

            // parent waits for child to die
            wait( &status );
            if ( status != 0 )
                fprintf( stderr, "command status: %d\n", status );
        }
    }

    return 0;
}