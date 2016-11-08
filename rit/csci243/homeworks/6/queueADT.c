/*****************************************************
 * File: queueADT.c
 *
 * A self ordering queue. Create, destroy, insert and remove from the queue at
 * will. Can use the standard FIFO ordering of a queue or a specific comparison
 * function passed during creation.
 *
 * @author swa9846 : Stephen Allan
 ****************************************************/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#define QUEUE_ALLOC_UNIT    5

typedef int (*cmpFunct)( const void*a, const void*b );

struct queueStruct {
    void **elements;
    int numElements;    
    int capacity;
    cmpFunct cmp;
};
typedef struct queueStruct *QueueADT;

#define _QUEUE_IMPL_
#include "queueADT.h"



QueueADT que_create( int (*cmp)( const void*a, const void*b ) ) {

    QueueADT queue = (QueueADT) malloc( sizeof( struct queueStruct ) );

    if( queue != NULL ) {
        queue->elements = NULL;
        queue->numElements = 0;
        queue->capacity = 0;
        queue->cmp = cmp;
    }

    return queue;
}


void que_destroy( QueueADT queue ) {

    assert( queue != NULL );

    if( queue->elements != NULL )
        free( queue->elements );

    free( queue );
}


void que_clear( QueueADT queue ) {
    
    if( queue->elements != NULL ) {

        free( queue->elements );
        queue->elements = NULL;
    }

    queue->numElements = 0;
    queue->capacity = 0;
}


void que_insert( QueueADT queue, void *data ) {

    if( queue->elements == NULL ) {
        queue->elements = malloc(
                                sizeof( struct queueStruct ) * QUEUE_ALLOC_UNIT
                                );

        assert( queue->elements != 0 );

        queue->capacity = QUEUE_ALLOC_UNIT;
    }

    if( queue->numElements >= queue->capacity ) {

        void *newMem;
        newMem = (void *) realloc(
                            queue->elements,
                            ( queue->capacity + QUEUE_ALLOC_UNIT ) *
                                sizeof( struct queueStruct )
                            );

        assert( newMem != NULL );

        queue->elements = newMem;
        queue->capacity += QUEUE_ALLOC_UNIT;
    }


    if ( queue->cmp == NULL )
        queue->elements[queue->numElements] = data;

    else if ( que_empty( queue ) )
        queue->elements[queue->numElements] = data;

    else {

        int i;
        for ( i = 0; i < queue->numElements; ++i ) {
            if ( queue->cmp( queue->elements[i], data ) >= 0 ) {

                if ( i < queue->numElements - 1 ) {

                    for ( int j = queue->numElements; j > i; --j ) {
                        queue->elements[j] = queue->elements[j-1];
                    }
                    queue->elements[i] = data;
                }

                else {    
                    queue->elements[i+1] = queue->elements[i];
                    queue->elements[i] = data;
                }

                break;
            }
        }

        if ( i == queue->numElements )
            queue->elements[queue->numElements] = data;
    }

    queue->numElements += 1;
}


void *que_remove( QueueADT queue ) {

    assert( queue->numElements > 0 );

    void *data = queue->elements[0];

    for (int i = 0; i < queue->numElements; ++i) {
        queue->elements[i] = queue->elements[i+1];
        queue->elements[i+1] = NULL;
    }

    queue->numElements -= 1;

    return data;
}


bool que_empty( QueueADT queue ) {

    return( queue->numElements == 0 );
}