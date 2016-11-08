/*****************************************************
 * File: pt-cruisers.c
 *
 * A demonstration of the use of threads.
 *
 * @author swa9846 : Stephen Allan
 ****************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "display.h"
#include "racer.h"



// Name: main
//
// Arguments
//   argc: int containing number of command line arguments
//   argv: array of strings containing...
//             - (optional) base 10 character representation of an
//                 int seed value for random number generator (srand(3))
//             - string names of Racers
//
// Run a race with a bunch of Racers
// Examples:
//   ./pt-cruisers Jack Jill # races Jack against Jill
//   ./pt-cruisers 90125 Manny Moe Jack # races three Racers with seed 90125
//
// If the first argument represents a non-integer numeric value, the
// decimal digits at the start of the argument string are used as an
// integer seed and the rest is ignored. (See sscanf.)
// A usage error on Standard Error results if no racer names are given. The
// format is
//   fprintf( stderr, "Usage: %s [ random-seed ] names...\n", argv[ 0 ] );
//
// Post: All memory allocated in this program has been freed.
//
int main( int argc, char *argv[] ) {

    if ( argc == 1 ) {
        fprintf( stderr, "Usage: %s [ random-seed ] names...\n", argv[0] );
        return 1;
    }


    int seed = atoi( argv[1] );
    long i, t, numThreads;

    if ( seed == 0 )
        i = 1;
    else {
        i = 2;
        if ( !argv[i] ) {
            fprintf( stderr, "Usage: %s [ random-seed ] names...\n", argv[0] );
            return 1;
        }
        srand( seed );
    }

    initRacers( 0 );

    numThreads = argc - i;
    pthread_t threads[numThreads];
    Racer *racers[numThreads];

    // spawn all threads
    for( t = 0; t < numThreads; ++t ) {
        racers[t] = makeRacer( argv[i], t+1 );
        int rc = pthread_create( &threads[t], NULL, run, (void *)racers[t] );

        // if the creation failed, exit
        if ( rc ) {
           fprintf( stderr, "ERROR; pthread_create() returned %d\n", rc );
           return 1;
        }

        ++i;
    }

    // join all threads back to main and free
    for( t = 0; t < numThreads; ++t ) {
        pthread_join( threads[t], NULL );
        destroyRacer( racers[t] );
    }

    set_cur_pos( numThreads, 1 );
    printf( "\n" );

    return 0;
}