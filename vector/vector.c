/**
 * @file vector.c
 * Define lots of functions for manipulating vectors of arbitrary length
 */

#include <stdlib.h>

#include "vector.h"

/**
 * @brief Create a 1d vector of length n
 * @param n Number of elements in the vector
 * @return The newly created vector
 */
vector* CreateVector(int n)
{
    vector *v;
    v = (vector*) calloc(1, sizeof(vector));

    v->v = (double*) calloc(n, sizeof(double));
    v->length = n;

    return v;
}

/**
 * @brief Free the memory allocated for the vector.
 * @param The pointer to the vector to deallocate memory for
 */
void DestroyVector(vector *v)
{
    free(v->v);
    free(v);
    return;
}

/**
 * @brief Make a vector of equally spaced points.
 * @param start The value of the first comonent of the vector
 * @param end The value of the last
 * @param nelem The total number of comonents
 * @returns The vector of points
 *
 * @see linspace
 */
vector* linspaceV(double start, double end, int nelem)
{
    vector *x;
    int i;

    x = CreateVector(nelem);
    for(i=0; i<nelem; i++) {
        setvalV(x, i, start + i*(end-start)/(nelem-1));
    }

    return x;
}

/**
 * @brief Copy a vector
 * @param v A pointer to the original vector
 * @returns A pointer to a new vector with the same components as v
 */
vector* CopyVector(vector *v)
{
    vector *new;
    int i;
    new = CreateVector(len(v));
    for(i=0; i<len(v); i++) {
        setvalV(new, i, valV(v, i));
    }
    return new;
}

/* Return the i-th value */
//double valV(vector *v, int i)
//{
//    if(i<0 || i>=v->length) {
//        /* Index out of bounds */
//        return 0;
//    }
//
//    return v->v[i];
//}
/* Replaced by a macro for efficiency */

/**
 * @brief Set the i-th value to "val"
 * @param v The vector to set the value in
 * @param i The index of the component to change
 * @param val The new value the component should have
 */
void setvalV(vector *v, int i, double val)
{
    if(i<0 || i>=v->length) {
        /* Index out of bounds */
        return;
    }

    v->v[i] = val;
    return;
}

/**
 * @brief Return the length of the vector
 * @param v The vector to get the length for
 * @returns The length of the vector
 */
int len(vector* v)
{
    return v->length;
}


