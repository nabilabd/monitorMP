//
//  Common.c
//  Assignment 2
//
//  Created by Karl Gemayel on 9/15/15.
//  Copyright © 2015 Karl Gemayel. All rights reserved.
//

#include "Common.h"
#include <stdlib.h>

//// Declare a variable that will hold error messages. This variable also
//// has a predefined length, meaning that error messages have a limited
//// size.
//#define ERR_MSG_LEN 1000
//char error_msg[ERR_MSG_LEN];

void Warning(char *fromFunction, char *msg) {
    fprintf(stderr, "WARNING in (%s): %s\n", fromFunction, msg);
}


void FatalError(char *fromFunction, char *msg) {
    fprintf(stderr, "FATAL ERROR in(%s): %s\n", fromFunction, msg);
    exit(1);
}
