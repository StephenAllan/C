/*****************************************************
 * File: racer.c
 *
 * A thread controlling a small figure that races across a character window
 *
 * @author swa9846 : Stephen Allan
 ****************************************************/


#if __STDC_VERSION__ >= 199901L
#   define _XOPEN_SOURCE 600
#else
#   define _XOPEN_SOURCE 500
#endif /* __STDC_VERSION__ */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#include "display.h"
#include "racer.h"



pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void initRacers( long milliseconds ) {
    clear();
    set_cur_pos( 1, 1 );

    (void) milliseconds;
}


Racer *makeRacer( char *name, int position ) {

    assert( strlen(name) <= MAX_NAME_LEN );

    Racer *newRacer = malloc( sizeof(Racer) );

    if ( newRacer != NULL ) {
        newRacer->dist = 1;
        newRacer->row = position;
        newRacer->graphic = strdup( name );
    }

    return newRacer;
}


void destroyRacer( Racer *racer ) {

    if ( racer != NULL ) {
        free( racer->graphic );
        free( racer );
    }
}


void *run( void *racer ) {

    if (racer == NULL)
        return NULL;

    Racer *rcr = (Racer *) racer;

    while ( rcr->dist <= FINISH_LINE ) {

        pthread_mutex_lock( &mutex );

        set_cur_pos( rcr->row , rcr->dist - 1);
        put(' ');

        set_cur_pos( rcr->row , rcr->dist );
        for ( size_t i = 0; i < strlen(rcr->graphic); ++i ) {
            put( rcr->graphic[i] );
        }

        ++rcr->dist;
        pthread_mutex_unlock( &mutex );

        usleep( (rand() % MAX_TIME) * 1000 );
    }

    return racer;
}