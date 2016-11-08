/*****************************************************
 * File: mytest.c
 *
 * A main that calls and test functions in amigonet.c separatly.
 *
 * @author swa9846 : Stephen Allan
 ****************************************************/

#include <stdio.h>
#include <string.h>

#include "amigonet.h"



int main() {
    create_amigonet();

    // char name[] = "Steve";
    // addUser( name );

    addUser( "user1" );
    addUser( "user1" );
    addUser( "user2" );
    addUser( "user3" );
    addUser( "user4" );
    addUser( "user5" );
    addUser( "user6" );
    addUser( "user7" );
    addUser( "user8" );
    addUser( "user9" );
    addUser( "user10" );
    addUser( "user11" );

    // strncpy( name, "James", 6 );
    // User *usertmp = findUser( name );
    // if ( usertmp != NULL )
    //     printf( "James = %s\n", usertmp->name );


    User *user1 = findUser( "user1" );
    User *user2 = findUser( "user2" );
    User *user3 = findUser( "user3" );
    User *user4 = findUser( "user4" );
    User *user5 = findUser( "user5" );
    User *user6 = findUser( "user6" );
    User *user7 = findUser( "user7" );
    User *user8 = findUser( "user8" );
    User *user9 = findUser( "user9" );
    User *user10 = findUser( "user10" );
    User *user11 = findUser( "user11" );
    User *user12 = findUser( "user12" );
    

    addAmigo( user1, user1 );
    addAmigo( user1, user2 );
    addAmigo( user1, user3 );
    addAmigo( user1, user4 );
    addAmigo( user1, user5 );
    addAmigo( user1, user6 );
    addAmigo( user1, user7 );
    addAmigo( user1, user8 );
    addAmigo( user1, user9 );
    addAmigo( user1, user12 );
    addAmigo( user3, user7 );
    addAmigo( user3, user4 );
    addAmigo( user3, user7 );
    addAmigo( user5, user10 );


    removeAmigo( user3, user4 );
    removeAmigo( user5, user6 );
    removeAmigo( user9, user11 );


    dump_data();


    printf( "separation between %s and %s is %lu\n", user3->name, user3->name, separation( user3, user3 ) );
    // printf( "separation between %s and %s is %lu\n", user3->name, user7->name, separation( user3, user7 ) );
    // printf( "separation between %s and %s is %lu\n", user3->name, user5->name, separation( user3, user5 ) );


    destroy_amigonet();

    return 0;
}