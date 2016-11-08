/*****************************************************
 * File: vault.c
 *
 * Maintains information about database 'vaults' containing information on
 * collections of records. The information about each recording includes the
 * title, the artist, the acquisition cost and the current market value. Opens
 * a file, the 'vault', and manipulates that data based on user commands entered
 * via the manager C file.
 *
 * @author swa9846 : Stephen Allan
 ****************************************************/

#define _GNU_SOURCE

#include <assert.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "vault.h"
#include "file_tools.h"

static MoveType move;



/// open the vault file.
int v_open( const char * filename ) {

	Vault fileDesc;
	if (( fileDesc = open( filename, O_RDWR )) < 0 ) {
		perror( filename );
        return -1;
    }

	return fileDesc;
}


/// close the vault file.
int v_close( Vault vid ) {

	assert( vid > 0 );

	fsync( vid );
	if ( close( vid ) < 0 ) {
		perror( "close" );
		return -1;
	}

	return 0;
}


/// create an entry for the vault.
VaultEntry_T * v_create( char * title, char * artist, int value, int cost ) {

	assert( title != NULL );
	assert( artist != NULL );
	assert( value >= 0 );
	assert( cost >= 0 );

	VaultEntry_T *entry = malloc( sizeof( VaultEntry_T ) );

	assert( entry != NULL );

	if ( strlen(title) > TITLE_LEN ) {

		char *tmp = calloc( TITLE_LEN+1, sizeof(char) );

		assert( tmp != NULL );

		strncpy( tmp, title, TITLE_LEN-3 );
		strcat( tmp, "..." );

		strcpy( entry->title, tmp );
		free( tmp );
	}
	else
		strcpy( entry->title, title );


	if ( strlen(artist) > ARTIST_LEN ) {

		char *tmp = calloc( ARTIST_LEN+1, sizeof(char) );

		assert( tmp != NULL );

		strncpy( tmp, artist, ARTIST_LEN-3 );
		strcat( tmp, "..." );

		strcpy( entry->artist, tmp );
		free( tmp );
	}
	else
		strcpy( entry->artist, artist );


	entry->value = value;
	entry->cost = cost;

	return entry;
}


/// add an entry to the vault file.
int v_add( Vault vid, VaultEntry_T * entry ) {

	assert( entry != NULL );
	assert( vid > 0 );

	off_t offset = move_to( vid, 0, move = END );

	if ( write_entry( vid, entry, sizeof( VaultEntry_T ) ) < 0 )
		return -1;

	return ( offset / sizeof( VaultEntry_T ) );
}


/// get the entry at the index.
VaultEntry_T * v_get( Vault vid, size_t index ) {

	assert( index < v_size( vid ) );

	move_to( vid, index * sizeof( VaultEntry_T ), move = START );

	void *entry = malloc( sizeof( VaultEntry_T ) );

	assert( entry != NULL );

	read_entry( vid, entry, sizeof( VaultEntry_T ) );

	return entry;
}


/// update the entry at the index with new information.
int v_update( Vault vid, size_t index, VaultEntry_T * entry ) {

	assert( entry != NULL );
	assert( index < v_size( vid ) );

	off_t offset = move_to( vid, index * sizeof( VaultEntry_T ), move = START );

	if ( write_entry( vid, entry, sizeof( VaultEntry_T ) ) < 0 )
		return -1;

	return ( offset / sizeof( VaultEntry_T ) + 1 );
}


/// delete the entry at the index, replacing it with the last entry's content.
int v_delete( Vault vid, size_t index ) {

	if ( index >= v_size( vid ) )
		return -1;

	if ( index < ( v_size( vid ) - 1 ) ) {

		VaultEntry_T *buf = v_get( vid, v_size( vid ) - 1 );

		v_update( vid, index, buf );
		
		free( buf );
	}

	off_t size = move_to( vid, 0, move = END );
	if ( ftruncate( vid, size - sizeof( VaultEntry_T ) ) < 0 )
		return -2;

	fsync( vid );

	if ( index == v_size( vid ) )
		index -= 1;
	
	off_t offset = move_to( vid, (index+1) * sizeof( VaultEntry_T ), move = START );

	return ( offset / sizeof( VaultEntry_T ) );
}


/// return the number of entries in the vault file.
size_t v_size( Vault vid ) {

	off_t currIndex = move_to( vid, 0, move = HERE );

	off_t offset = move_to( vid, 0, move = END );

	move_to( vid, currIndex, move = START );

	return ( offset / sizeof( VaultEntry_T ) );
}


/// get the index associated with the current file offset into the vault.
size_t v_index( Vault vid ) {

	off_t offset = move_to( vid, 0, move = HERE );

	return ( offset / sizeof( VaultEntry_T ) );
}


/// set the file offset so it refers to the index-th record in the vault file.
size_t v_set_index( Vault vid, size_t index ) {

	assert( index < v_size( vid ) );

	off_t offset = move_to( vid, index * sizeof( VaultEntry_T ), move = START );

	return ( offset / sizeof( VaultEntry_T ) );
}


/// print the entry.
void v_print_entry( VaultEntry_T * entry ) {

	assert( entry != NULL );

	printf( "\"%s\", by %s\n", entry->title, entry->artist );
	printf( "\tis worth $%d and cost $%d dollars.\n", entry->value, entry->cost );
}

// end file
