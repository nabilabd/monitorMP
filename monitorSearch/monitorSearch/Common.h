//
//  Common.h
//  Assignment 2
//
//  Created by Karl Gemayel on 9/15/15.
//  Copyright © 2015 Karl Gemayel. All rights reserved.
//

#ifndef Common_h
#define Common_h

#include <stdlib.h>
#include <stdio.h>


/*************** File Description *****************\
 *                                                *
 * This file defines global types, variables, and *
 * functions that can be used by any other file.  *
 \**************************************************/


// Define true and false values
typedef enum {TRUE, FALSE} BOOL;

// Define the return values for a function executing successfully or not.
#define SUCCESS 0
#define FAIL 1

/*
 * Print a warning message, stating what function generated it.
 *
 * @param fromFunction name of originating function
 * @param msg the warning message
 */
void Warning(char *fromFunction, char *msg);

/*
 * Print a fatal error message, and exit the program.
 *
 * @param fromFunction name of originating function
 * @param msg the error message.
 */
void FatalError(char *fromFunction, char *msg);


#endif /* Common_h */
