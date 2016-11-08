/*****************************************************
 * File: amigonet.c
 *
 * Maintains a collection of users that have friend (“amigo”) connections
 * between them. Allows for the addition of users and for the adition and
 * removal of friends between users.
 *
 * @author swa9846 : Stephen Allan
 ****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "amigonet.h"

#define ALLOC_UNIT    5

typedef struct Amigonet_struct {
    User **users; 
    int numUsers;    
    int capacity;
} Amigonet;
static Amigonet *amigonet;

struct Friends_struct {
    User **lst;
    int numFriends;    
    int capacity;
};



void create_amigonet() {

    // initialize amigonet object
    amigonet = malloc( sizeof( struct Amigonet_struct ) );

    if( amigonet != NULL ) {
        amigonet->users = malloc( sizeof( struct User_struct ) * ALLOC_UNIT );
        amigonet->numUsers = 0;
        amigonet->capacity = ALLOC_UNIT;
    }
}


void destroy_amigonet() {

    // loop through all users and free alloc'd space
    for ( int i = 0; i < amigonet->numUsers; ++i ){
        free( amigonet->users[i]->amigos->lst);
        free( amigonet->users[i]->amigos);
        free( amigonet->users[i]);
    }

    // free amigonet
    free( amigonet->users );
    free( amigonet );
}


void addUser( const char *name ) {

    // check name and not duplicate
    if ( name == NULL || findUser( name ) != NULL )
        return;

    User *user = malloc( sizeof( struct User_struct ) );

    if( user != NULL ) {

        // assign name (view README.txt)
        user->name = name;

        // initialize friends struct
        user->amigos = malloc( sizeof( struct Friends_struct ) );
        if( user->amigos != NULL ) {

            user->amigos->lst = NULL;
            user->amigos->numFriends = 0;    
            user->amigos->capacity = 0;
        }
    }

    // realloc if needed
    if ( amigonet->numUsers >= amigonet->capacity ) {
        amigonet->users = realloc( amigonet->users,
                                  ( amigonet->capacity + ALLOC_UNIT ) *
                                  sizeof( struct User_struct )
                                 );

        if ( amigonet->users != NULL ) 
            amigonet->capacity += ALLOC_UNIT;
    }

    // add user to global array
    amigonet->users[amigonet->numUsers] = user;

    amigonet->numUsers += 1;
}


User *findUser( const char *name ) {

    for ( int i = 0; i < amigonet->numUsers; ++i ){
        if ( strcmp( amigonet->users[i]->name, name) == 0 )
            return amigonet->users[i];
    }

    return NULL;
}


/**
 * Ensure that there is enough space allocated for the user's friend list
 * inorder to add another friend.
 *
 * @param user  The user's whose friend list will be (re)sized
 */
static void allocateSpace( User *user ) {

    // initialize friends list if first friend
    if ( user->amigos->lst == NULL ) {
        user->amigos->lst = malloc( sizeof( struct User_struct ) * ALLOC_UNIT );

        if ( user->amigos->lst != NULL ) 
            user->amigos->capacity = ALLOC_UNIT;
    }

    // resize array if capacity was reached
    if ( user->amigos->numFriends >= user->amigos->capacity ) {
        user->amigos->lst = realloc( user->amigos->lst,
                                    ( user->amigos->capacity + ALLOC_UNIT ) *
                                    sizeof( struct User_struct )
                                   );

        if ( user->amigos->lst != NULL ) 
            user->amigos->capacity += ALLOC_UNIT;
    }
}


void addAmigo( User *user, User *amigo ) {

    // check users and that they are not already friends
    if ( user == NULL || amigo == NULL || (user == amigo) )
        return;

    for (int i = 0; i < user->amigos->numFriends; ++i ) {
        if ( strcmp( user->amigos->lst[i]->name, amigo->name ) == 0 )
            return;
    }


    // (re)size array if needed
    allocateSpace( user );
    allocateSpace( amigo );

    // add users to eachothers friends list
    user->amigos->lst[user->amigos->numFriends] = amigo;
    amigo->amigos->lst[amigo->amigos->numFriends] = user;

    user->amigos->numFriends += 1;
    amigo->amigos->numFriends += 1;
}


/**
 * Un-friends two users. Removes "friend" from "user's" friends list.
 *
 * @param user  The user to remove a friend from
 * @param user  The user to unfriend
 */
static void deleteFriend( User *user, User *friend ) {

    for ( int i = 0; i < user->amigos->numFriends; ++i ) {

        // check that they are friends
        if ( strcmp( user->amigos->lst[i]->name, friend->name ) == 0 ) {
            user->amigos->numFriends -= 1;

            // reorder array when removing
            for ( int j = i; j < user->amigos->numFriends; ++j ) {
                user->amigos->lst[j] = user->amigos->lst[j+1];
                user->amigos->lst[j+1] = NULL;
            }

            break;
        }
    }
}


void removeAmigo( User *user, User *ex_amigo ) {

    // check users and that they both have atleast 1 friend
    if ( user == NULL || ex_amigo == NULL ||
        (user->amigos->numFriends <= 0) || (ex_amigo->amigos->numFriends <= 0) )
        return;


    // remove eachother as friends
    deleteFriend( user, ex_amigo );
    deleteFriend( ex_amigo, user );
}


// Broken
size_t separation( const User *user1, const User *user2 ) {

    // check users and make sure they are friends
    if ( user1 == NULL || user2 == NULL )
        return -1;

    if ( strcmp( user1->name, user2->name) == 0 )
        return 0;

    int i;
    for (i = 0; i < user1->amigos->numFriends; ++i ) {
        if ( strcmp( user1->amigos->lst[i]->name, user2->name ) == 0 )
            break;
    }
    if ( i >= user1->amigos->numFriends )
        return -1;


    // for ( int maxDepth = 1; maxDepth < 6; ++maxDepth ) {
    //     size_t separation = search( user1, user2, maxDepth );
    //     printf( "%lu\n", separation );
    // }

    // for ( int i = 0; i < user1->amigos->numFriends; ++i ) {
    //     search( user1->amigos->lst[i], user2, depth - 1 );
    // }

    // else {

    //     for ( int i = 0; i < user1->amigos->numFriends; ++i ) {
    //         int size = amigonet->numUsers;

    //         int j;
    //         for ( j = 0; j < size; ++j ) {
    //             if ( strcmp(user1->amigos->lst[i]->name, visited[j].name) == 0)
    //                 break;
    //         }
    //         if ( j < size )
    //             continue;

    //         visited[] = user1->amigos->lst[i];
    //         search( user1->amigos->lst[i], user2, visited, depth + 1 );
    //     }
    // }

    // User *visited = malloc( sizeof( struct User_struct ) );
    // for ( int i = 0; i < user1->amigos->numFriends; ++i ) {
    //     size_t separation = search( user1, user2, visited, 0 );
    // }
    // free( visited );




    /*  For some reason this retuns an insanly high integer. Seems to occur with
        any negative numbers and neither casting nor parentheses help. */
    return -1;
}// Broken


void dump_data() { 

    // loop through all users, print data in required format
    for (int i = 0; i < amigonet->numUsers; ++i) {
        printf( "User %s; ", amigonet->users[i]->name );
        printf( "friends:");

        for (int j = 0; j < amigonet->users[i]->amigos->numFriends; ++j ) {
            printf( " %s", amigonet->users[i]->amigos->lst[j]->name );
        }
        printf("\n");
    }
}