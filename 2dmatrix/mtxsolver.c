/**
 * @file mtxsolver.c
 * Set of functions to solve matrix equations
 */

#include <math.h>
#include <stdlib.h>

#include "2dmatrix.h"
#include "mtxsolver.h"
#include "../fortran.h"

void SwapRows(matrix*, int, int);
int FindPivot(matrix*, int);

/* Code from http://compprog.wordpress.com/2007/12/11/gaussian-elimination/ */

void ForwardSubstitution(matrix* a) {
    int i, j, k, max;
    int n = nRows(a);
    double t;
    for (i = 0; i < n; ++i) {
        max = i;
        for (j = i + 1; j < n; ++j)
            if (fabs(val(a, j, i)) > fabs(val(a, max, i)))
                max = j;

        for (j = 0; j < n + 1; ++j) {
            t = val(a, max, j);
            setval(a, val(a, i, j), max, j);
            setval(a, t, i, j);
        }

        for (j = n; j >= i; --j)
            for (k = i + 1; k < n; ++k)
                setval(a, val(a, k, j) - val(a, k, i)/val(a, i, i) * val(a, i, j), k, j);

    }
}

void ReverseElimination(matrix *a) {
    int i, j;
    int n = nRows(a);
    for (i = n - 1; i >= 0; --i) {
        setval(a, val(a, i, n)/val(a, i, i), i, n);
        setval(a, 1, i, i);
        for (j = i - 1; j >= 0; --j) {
            setval(a, val(a, j, n) - val(a, j, i) * val(a, i, n), j, n);
            setval(a, 0, j, i);
        }
    }
}

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

