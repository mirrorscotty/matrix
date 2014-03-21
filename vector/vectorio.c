#include <stdio.h>
#include "vector.h"

/**
 * @brief Print the vector to stdout
 * @param A pointer to the vector to print
 */
void PrintVector(vector *v)
{
    int i;

    printf("[");
    for(i=0; i<len(v)-1; i++) {
        printf(" %g,", valV(v, i));
    }
    printf(" %g ]\n", valV(v, len(v)-1));
}

