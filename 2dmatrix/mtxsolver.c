/**
 * @file mtxsolver.c
 * Set of functions to solve matrix equations
 */

#include <math.h>
#include <stdlib.h>

#include "2dmatrix.h"
#include "mtxsolver.h"
#include "../fortran.h"

/**
 * @brief Gaussian Elimination
 *
 * Solve an matrix equation of the form Ax=B, where x is the vector of
 * unknowns.
 *
 * @param A An nxm matrix that represents the coefficients on the x vector
 * @param B An nx1 matrix
 * @returns An nx1 matrix representing the solution to the equation
 */
matrix* SolveMatrixEquation(matrix *A, matrix *B)
{
    int n, nrhs, lda, ldb, info, pivot[nRows(A)],
        i, j;
    double a[nCols(A)][nRows(A)], b[nCols(B)][nRows(A)];
    matrix *result;
    
    n = nRows(A);
    lda = nCols(A);
    nrhs = nCols(B);
    ldb = nRows(B);

    for(i=0; i<nRows(A); i++)
        for(j=0; j<nCols(A); j++)
            a[j][i] = val(A, i, j);

    for(i=0; i<nRows(B); i++)
        for(j=0; j<nCols(B); j++)
            b[j][i] = val(B, i, j);

    dgesv_(&n, &nrhs, &a[0][0], &lda, pivot, &b[0][0], &ldb, &info);

    result = CreateMatrix(nRows(B), nCols(B));
    for(i=0; i<nRows(B); i++)
        for(j=0; j<nCols(B); j++)
            setval(result, b[j][i], i, j);

    return result;
}

