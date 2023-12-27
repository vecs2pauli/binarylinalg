#ifndef BINARYLINALG_UTILS_H
#define BINARYLINALG_UTILS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#define DEBUG_MODE false

void printlogstring();

/**
   \brief Prints a log statement to the console,
   provided `DEBUG_MODE` is set to `true`

   <b>Example usage:</b>
   ~~~~~~~~~~~~~{.c}
   int x = 42;
   ulog("Value of x: %i", x);
   # prints a newline, followed by ">>> LOG: Value of x: 42"
   ~~~~~~~~~~~~~

*/
#if DEBUG_MODE
    #define ulog printlogstring;printf
#else
    #define ulog
#endif


#endif // BINARYLINALG_UTILS_H
