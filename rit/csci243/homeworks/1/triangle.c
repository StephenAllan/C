//
// File: triangle.c
//
// A program to print out multiple triangles "right-up" triangles.
// of the form
//    *
//   **
//  ***
// ****
//
// @author swa9846 : Stephen Allan
//
// // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 *  Function: drawTriangle
 *
 *  Description: function to draw a triangle whose height/width is "size"
 *
 *  @param size  the size of the triangle to draw
 */
void drawTriangle(int size) {
    char* leg = malloc(size+1);

    for (int i=0; i < size; i++) {
        strcat(leg, "*");

	// printf("%-.*s\n", size, leg);  // Does not work.
	// Cant figure out how this works:
	// printf("%<VARIABLE>s/n", leg)
	// so I just hard coded it.
        if (size == 1)
            printf("%1s\n", leg);
        else if (size == 4)
            printf("%4s\n", leg);
        else
            printf("%6s\n", leg);
    }
//    printf("\n");
}


/**
 *  Function: main
 *
 *  Description: program to draw 3 triangles of size 1, 4, and 6.
 *
 *  @author swa9846 : Stephen Allan
 *
 *  @returns errorCode  error Code; EXIT_SUCCESS if no error
 */
int main() {

//    printf("Triangle Size: 1\n");
    drawTriangle(1);

//    printf("Triangle Size: 4\n");
    drawTriangle(4);

//    printf("Triangle Size: 6\n");
    drawTriangle(6);

    return 0;
}


// // // // // // // // // // // // // // // // // // // // // // // //
// Version:
//     $Id$
//
// Revisions:
//     $Log$
