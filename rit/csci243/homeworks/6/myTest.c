#include <stdio.h>
#include <stdlib.h>

#include "queueADT.h"



int cmp_int64_ascend( const void *a, const void *b ) {
    long int na = (long int) a;
    long int nb = (long int) b;

    return( na - nb );
}


int main( void ) {

    QueueADT queue2 = que_create( cmp_int64_ascend );

    printf( "Empty? %d\n", que_empty( queue2 ) );

    printf( "Inserting...\n" );
    que_insert( queue2, (void *)42 );
    que_insert( queue2, (void *)17 );
    que_insert( queue2, (void *)-12 );
    que_insert( queue2, (void *)9982 );
    que_insert( queue2, (void *)476 );
    que_insert( queue2, (void *)2912 );
    que_insert( queue2, (void *)-22 );
    que_insert( queue2, (void *)3291213 );
    que_insert( queue2, (void *)7782 );

    int numElements = 9;

    printf( "Empty? %d\n", que_empty( queue2 ) );

    printf( "Removing... ");
    for (int i=0; i < numElements; ++i) {
        printf( "%ld ", (long) que_remove( queue2 ) );
    }

    printf( "\nEmpty? %d\n", que_empty( queue2 ) );

    printf( "Destroying...\n" );
    que_destroy( queue2 );


    return 0;
}