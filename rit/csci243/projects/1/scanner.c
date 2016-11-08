/*****************************************************
 * File: scanner.c
 *
 * Scanner for a small subset of the C language:
 * identifiers, decimal integers, octal integers, block-style comments,
 * Classifies characters and tokenizes input based on their classifications
 * and a transtition matrix created in tokenzie.c.
 *
 * @author swa9846 : Stephen Allan
 ****************************************************/

#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "scanner.h"



void append( char* s, char c ) {
    int len = strlen( s );
    s[len] = c;
    s[len+1] = '\0';
}


int classify( char c ) {

    if ( c == '\n' )
        return CC_NEWLINE;

    else if ( isspace( c ) )
        return CC_WS;

    else if ( isalpha( c ) || c == '_' )
        return CC_ALPHA;

    else if ( isdigit( c ) ) {
        int num = c - '0';

        if ( num == 0 )
            return CC_DIG_0;
        
        else if ( num > 0 && num < 8 )
            return CC_DIG_1_7;
        
        else if ( num == 8 || num == 9 )
            return CC_DIG_8_9;
    }

    else if ( c == '/' )
        return CC_CHAR_SLASH;

    else if ( c == '*' )
        return CC_CHAR_STAR;

    else if ( c == '+' || c == '-' || c == '%' )
        return CC_ARITH_OP;

    else if ( c == EOF )
        return CC_EOF;

    else if ( isprint( c ) )
        return CC_OTHER;
    
    return CC_ERROR;
}


void scan(int start, int accept, int states, transition tMatrix[states][N_CC]) {
    char saved[256];
    saved[0] = '\0';

    char c;
    int currState = start, i = 0;
    while ( ( c = getchar() ) ) {

        if ( i == 0 ) {
            printf( "%d ", currState );
            ++i;
        }

        int charClass = classify( c );

        currState = tMatrix[currState][charClass].nextState;
        printf( "%d ", currState );

        if ( currState == ERROR_STATE ) {
            printf( "rejected\n" );
            saved[0] = '\0';

            while ( ( c = getchar() ) ) {
                charClass = classify( c );

                if ( charClass == CC_WS || charClass == CC_EOF ) {
                    currState = start;
                    i = 0;
                    break;
                }
            }
            continue;
        }

        else if ( charClass == CC_EOF ) {
            printf( "EOF\n" );
            break;
        }


        if ( tMatrix[currState][charClass].action == 's'
             || c == '/' || c == '+' || c == '-' || c == '%' || c == '*' )
            append( saved, c );

        if ( currState == accept ) {
            printf( "recognized \'%s\'\n", saved );
            if ( tMatrix[currState][charClass].action == 'd' )
                saved[0] = '\0';
            currState = start;
            i = 0;
        }
    }
}