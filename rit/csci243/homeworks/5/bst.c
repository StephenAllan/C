/*****************************************************
 * File: bst.c
 *
 * This program reads integer values from stdin and builds a binary search
 * tree with those values. The program requires a command line argument that
 * will specify how many integers to read. After reading all of the values,
 * they are echoed back to stdout. The integers are then inserted into a
 * binary search tree in the order that they were entered. Finally, the tree
 * is traversed with preorder, inorder, and postorder traversals.
 *
 * @author swa9846 : Stephen Allan
 ****************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "bst.h"



/**
 * Takes an array of characters and return its integer value.
 * Chops any decimal point values off with no rounding.
 *
 * @param str  An array of characters
 * @return  The integer value of str
 */
int strToInt( char* str ) {
    int result = 0;
    for ( int i=0; str[i] != '\0'; ++i ) {
        if ( str[i] == '.' )
            return result;
        result = ( result * 10 + str[i] - '0' );
    }
    return result;
}


/**
 * Inserts one node into the binary search tree.
 * New values lower than curr are inserted into left subtrees while
 * larger values are instered into right subtrees.
 *
 * @param curr  The current node to check against the newNode
 * @param newNode  The node to be inserted into the binary search tree
 */
void insertNode( TreeNode *curr, TreeNode *newNode ) {

    if ( newNode->data <= curr->data ) {
        if ( curr->left == NULL )
            curr->left = newNode;
        else
            insertNode( curr->left, newNode );
    }

    else if ( newNode->data > curr->data ) {
        if ( curr->right == NULL )
            curr->right = newNode;
        else
            insertNode( curr->right, newNode );
    }
}


void build_tree( TreeNode** root, const int elements[], const int count ) {

    for ( int i = 1; i < count; ++i ) {

        TreeNode *newNode = malloc( sizeof( TreeNode ) );
        newNode->data = elements[i];
        newNode->left = NULL;
        newNode->right = NULL;

        insertNode( *root, newNode );
    }
}


void traverse( const TreeNode* root, const TraversalType type ) {

    if ( type == PREORDER ) {
        if ( root == NULL )
            return;
        printf( "%d\n", root->data );   // Parent
        traverse( root->left, type );   // Left subtree
        traverse( root->right, type );  // Right subtree
    }

    else if ( type == INORDER ) {
        if ( root == NULL )
            return;
        traverse( root->left, type );   // Left subtree
        printf( "%d\n", root->data );   // Parent
        traverse( root->right, type );  // Right subtree
    }

    else if ( type == POSTORDER ) {
        if ( root == NULL )
            return;
        traverse( root->left, type );   // Left subtree
        traverse( root->right, type );  // Right subtree
        printf( "%d\n", root->data );   // Parent
    }

    return;
}


void cleanup_tree( TreeNode* root ) {

    if ( root == NULL )
        return;

    cleanup_tree( root->left );     // Left subtree
    cleanup_tree( root->right );    // Right subtree

    free( root );                   // Free parent
}


/**
 * Checks for proper command line arguments and then askes user for input
 * integer values. Repeats the values to stdout and then creates a root node
 * with the first entered integer. Builds a binary search tree with all entered
 * values and then traverses the tree with preorder, inorder and postorder
 * traversals. Finally, it frees all memory allocated on the heap and exits.
 *
 * @param argc  The number of command line arguments
 * @param argv  The command line arguments
 * @return  success exit code, 0 if no errors
 */
int main( int argc, char* argv[] ) {

    // Check for a given integer value
    if ( argc == 1 ) {
        printf( "Usage: bst #\n" );
        return EXIT_FAILURE;
    }

    // Convert argument into int and check that the value is positive
    int numElements = strToInt( argv[1] );
    if ( numElements <= 0 ) {
        printf( "# must be greater than 0\n" );
        return EXIT_FAILURE;
    }


    // Define an array size for the elements.
    int elements[numElements + 1];

    // Get all the elements from stdin
    printf( "Enter %d integer values to place in tree:\n", numElements );
    for ( int i = 0; i < numElements; ++i ) {
        scanf( "%d", &elements[i] );
    }

    // Repeat entered values to stdout
    printf( "Input values:\n" );
    for ( int i = 0; i < numElements; ++i ) {
        printf( "%d\n", elements[i] );
    }


    // Create a root node
    TreeNode *root = malloc( sizeof( TreeNode ) );
    root->data = elements[0];
    root->left = NULL;
    root->right = NULL;


    // Build the binary search tree with entered values
    TreeNode **rootPtr = &root;
    build_tree( rootPtr, elements, numElements );


    TraversalType tType;
    // Traverse the tree with a preorder traversal
    printf( "Preorder:\n" );
    traverse( root, tType = PREORDER );

    // Traverse the tree with an inorder traversal
    printf( "Inorder:\n" );
    traverse( root, tType = INORDER );

    // Traverse the tree with a postorder traversal
    printf( "Postorder:\n" );
    traverse( root, tType = POSTORDER );


    // Free all allocated memory for treeNodes and exit main
    cleanup_tree( root );

    return 0;
}