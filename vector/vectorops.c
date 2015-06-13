/**
 * @file vectorops.c
 * Mathematical operations for vectors.
 */

#include <math.h>

#include "vector.h"

/**
 * Add two vectors together, element by element
 *
 * The two vectors should be of equal length
 *
 * @param a The first vector
 * @param b Second vector
 * @returns a+b
 */
vector* addV(vector *a, vector *b)
{
    int i;
    vector *c;
    c = CreateVector(len(a));

    for(i=0; i<len(a); i++) {
        setvalV(c, i, valV(a, i) + valV(b, i));
    }
    return c;
}

/**
 * Subtract vector b from vector a
 *
 * @param a The first vector
 * @param b The vector subtracted from a
 * @returns a-b
 */
vector* subtractV(vector *a, vector *b)
{
    int i;
    vector *c;
    c = CreateVector(len(a));

    for(i=0; i<len(a); i++) {
        setvalV(c, i, valV(a, i) - valV(b, i));
    }
    return c;
}

/**
 * @brief Calculate the dot product of two vectors
 * @param a A vector of arbitrary length
 * @param b A vector of the same length
 * @returns a dot b
 */
double dotV(vector *a, vector *b)
{
    int i;
    double result = 0;

    for(i=0; i<len(a); i++) {
        result += valV(a, i) * valV(b, i);
    }
    return result;
}

/**
 * @brief Multiply a vector by a scalar
 * @param k The constant to multiply each component by
 * @param v The vector to multiply
 * @returns k*v
 */
vector* scalarmultV(double k, vector *v)
{
    int i;
    vector *c;

    c = CreateVector(v->length);

    for(i=0; i<len(v); i++) {
        setvalV(c, i, k*valV(v, i));
    }

    return c;
}

/**
 * @brief Determine if vectors are equal
 *
 * Compare two vectors element by element to determine equality
 *
 * @param a The first vector
 * @param b Second vector
 * @returns 1 if equal, 0 if not equal
 */
int equalV(vector *a, vector *b)
{
    int i;
    double tol = 1e-10;

    if(a == b)
        return 1;

    if(len(a) != len(b)) {
        return 0;
    }

    for(i=0; i<len(a); i++) {
        if(fabs(valV(a, i) - valV(b, i)) >= tol)
            return 0;
    }

    return 1;
}

