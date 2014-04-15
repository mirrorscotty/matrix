/**
 * @file other.c
 * Functions that don't belong in any of the subdirectories. Currently,
 * there's just one.
 */

#include <stdarg.h>
#include <stdlib.h>

#include "matrix.h"

/**
 * @brief Smash several vectors together as column vectors into a matrix.
 *
 * @param n Number of vectors to smash.
 * @returns An n by l matrix containing the smashed vectors
 */
matrix* CatColVector(int n, ...)
{
    int i, j;
    va_list args;
    vector** v;
    matrix* result;
    int lmax = 0; /* Maximum vector length */
    v = (vector**) calloc(sizeof(vector*), n);

    va_start(args, n); /* Start getting the vectors */
    for(i=0; i<n; i++) {
        v[i] = va_arg(args, vector*);
        if(lmax < len(v[i]))
            lmax = len(v[i]);
    }
    va_end(args); /* Over it! */

    /* Create a matrix large enough to hold all the elements of the longest
     * vector. */
    result = CreateMatrix(lmax, n);

    for(i=0; i<n; i++)
        for(j=0; j<len(v[i]); j++)
            setval(result, valV(v[i], j), j, i);

    /* Cleanup */
    free(v);

    return result;
}

