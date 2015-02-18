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

/**
 * Pull out a column of a matrix and store it as a vector.
 * @param A Source matrix
 * @param col Number of the column to grab. The first column is column 0.
 * @returns A vector with length equal to the number of rows in A
 */
vector* ExtractColumnAsVector(matrix *A, int col)
{
    vector *v;
    int i;

    v = CreateVector(nRows(A));

    for(i=0; i<len(v); i++)
        setvalV(v, i, val(A, i, col));

    return v;
}

matrix* meshgridX(vector* x, vector *y)
{
    int i, j;
    matrix *X;
    X = CreateMatrix(len(y), len(x));
    for(i=0; i<len(y); i++)
        for(j=0; j<len(x); j++)
            setval(X, valV(x, j), i, j);
    return X;
}

matrix* meshgridY(vector* x, vector *y)
{
    int i, j;
    matrix *Y;
    Y = CreateMatrix(len(y), len(x));
    for(i=0; i<len(y); i++)
        for(j=0; j<len(x); j++)
            setval(Y, valV(y, i), i, j);
    return Y;
}

