/**
 * @file 2dmatrixops.c
 * All the matrix operations (addition, multiplication, etc.)
 */

#include <stdarg.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "2dmatrix.h"

/**
 * Determine the element of a matrix with the largest magnitude and return it.
 * @param A Matrix to search
 * @returns Value of the largest (or smallest) element.
 */
double mtxextrm(matrix *x)
{
    double extrm = 0;
    int i, j;

    for(i=0; i<nRows(x); i++) {
        for(j=0; j<nCols(x); j++) {
            if(fabs(extrm) < fabs(val(x, i, j)))
                extrm = val(x, i, j);
        }
    }

    return extrm;
}

/**
 * @brief Transpose a matrix
 * @param x The matrix to transpose
 * @return The transpose of matrix x
 */
matrix* mtxtrn(matrix *x)
{
    matrix *xt;
    int rows = nRows(x);
    int cols = nCols(x);
    int i, j;

    xt = NULL;
/*
    if(nRows(x) != nCols(x)) {
        fprintf(stderr, "ERROR!");
        return xt;
    }
*/

    xt = CreateMatrix(cols, rows);

    for(i=0; i<cols; i++) {
        for(j=0; j<rows; j++) {
            setval(xt, val(x, j, i), i, j);
        }
    }

    return xt;
}

/**
 * @brief Multiply matricies using nifty index notation!
 *
 * Simply calculates A*B
 *
 * @param A The first matrix to multiply
 * @param B The second one!
 * @return A*B
 */
matrix* mtxmul(matrix *A, matrix *B)
{
    int Ar, Ac, Br, Bc;
    int i, j, k;
    matrix *C;

    C = NULL;

    Ar = nRows(A);
    Ac = nCols(A);
    Br = nRows(B);
    Bc = nCols(B);

    /* If the matricies dimensions aren't correct, return NULL */
    if(Ac != Br) {
        fprintf(stderr, "Error: Incompatible matrix dimensions.\n");
        return C;
    }

    /* Allocate Memory */
    C = CreateMatrix(Ar, Bc);

    /* Cik = AijBjk */
    for(i=0; i<Ar; i++) {
        for(k=0; k<Bc; k++) {
            for(j=0; j<Ac; j++) {
                C->array[i][k] += A->array[i][j] * B->array[j][k];
            }
        }
    }

    return C;
}

/**
 * @brief Multiply a matrix by a constant
 * This multiplies each element of a matrix by a constant.
 * @param A The matrix to multiply
 * @param k The scalar
 * @return The new matrix
 */
matrix* mtxmulconst(matrix *A, double k)
{
    int Ar, Ac;
    int i, j;
    matrix *C;

    Ar = nRows(A);
    Ac = nCols(A);

    C = CreateMatrix(Ar, Ac);

    for(i=0; i<Ar; i++) {
        for(j=0; j<Ac; j++) {
            setval(C, k*val(A, i, j), i, j);
        }
    }

    return C;
}

/**
 * @brief Add two matricies.
 * Todo: Add error checking to make sure the dimensions agree.
 * @param A Some random matrix
 * @param B Another random matrix with the same dimensions as A
 * @return A+B
 */
matrix* mtxadd(matrix *A, matrix *B)
{
    int rows = nRows(A);
    int cols = nCols(A);

    matrix *C;

    int i, j;

    C = CreateMatrix(rows, cols);

    for(i=0; i<rows; i++) {
        for(j=0; j<cols; j++) {
            setval(C, val(A, i, j) + val(B, i, j), i, j);
        }
    }

    return C;
}

/**
 * @brief Subtract two matricies.
 * Todo: Add error checking to make sure the dimensions agree.
 * @param A Some random matrix
 * @param B Another random matrix with the same dimensions as A
 * @return A-B
 */
matrix* mtxsub(matrix *A, matrix *B)
{
    int rows = nRows(A);
    int cols = nCols(A);

    matrix *C;

    int i, j;

    C = CreateMatrix(rows, cols);

    for(i=0; i<rows; i++) {
        for(j=0; j<cols; j++) {
            setval(C, val(A, i, j) - val(B, i, j), i, j);
        }
    }

    return C;
}

/**
 * @brief Multiply a matrix by -1 in place.
 * @param A The matrix to multiply by -1
 * @return A pointer to the same matrix A that was passed to this function*/
matrix* mtxneg(matrix *A)
{
    int i, j;
    for(i=0; i<nRows(A); i++) {
        for(j=0; j<nCols(A); j++) {
            setval(A, -1*val(A, i, j), i, j);
        }
    }
    return A;
}

/**
 * @brief Calculate the minor of the row,col element of a matrix.
 *
 * Code here courtesy of http://www.daniweb.com/software-development/c/code/216687
 * @param A The matrix to calculate stuff for
 * @param row The row of the element
 * @param col The column the element is in
 * @return The value of the minor
 */
matrix* CalcMinor(matrix* A, int row, int col) {
    int i, j, a, b;
    int order;
    matrix *minor;

    minor = NULL;
    order = nRows(A);

    if(order <= 1)
        return NULL;
    if(row >= order || col >= order)
        return NULL;
    if( !(minor = CreateMatrix(order-1, order-1)) )
        return NULL;

    a = b = 0;

    for(i=0; i<order; i++) {
        if(i != row) {
            b = 0;
            for(j=0; j<order; j++) {
                if(j != col) {
                    setval(minor, val(A, i, j), a, b);
                    b++;
                }
            }
        a++;
        }
    }

    return minor;
}

/**
 * @brief Calculate the determinant of a matrix
 *
 * Borrowed from the same site as CalcMinor
 * @param p The matrix to calculate the determiant of. Must be square.
 * @return The determinant of p
 * @see CalcMinor
 */
double CalcDeterminant(matrix *p)
{
    int i, order;
    double result;
    matrix *minor;

    result = 0;
    minor = NULL;
    order = nRows(p);

    if(order < 1) {
        fprintf(stderr, "CalcDeterminant(): Invalid Matrix.");
        return 0;
    }

    if(order == 1)
        return val(p, 0, 0);

    for(i=0; i<order; i++) {
        if( !(minor = CalcMinor(p, 0, i)) ) {
            fprintf(stderr, "CalcDeterminant(): Memory allocation failed.");
            return 0;
        }

        result += ( pow(-1, i) * p->array[0][i] * CalcDeterminant(minor));

        DestroyMatrix(minor);
    }

    return result;
}

/**
 * @brief Calculate the adjugate matrix of A
 *
 * @param A The matrix of interest
 * @return The adjugate matrix
 */
matrix* CalcAdj(matrix* A)
{
    int i, j;
    double cofactor;
    matrix *minor, *adj, *adjt;

    adj = CreateMatrix(nRows(A), nRows(A));
    for(i=0; i<nRows(A); i++) {
        for(j=0; j<nRows(A); j++) {
            minor = CalcMinor(A, i, j);
            cofactor = pow(-1, (i+j+2)) * CalcDeterminant(minor);
            DestroyMatrix(minor);
            setval(adj, cofactor, i, j);
        }
    }

    adjt = mtxtrn(adj);
    DestroyMatrix(adj);


    return adjt;
}

/**
 * @brief Calculate the inverse of A
 * This is a pretty slow algorithm and only works well for small matricies
 * @param A The original matrix
 * @returns The inverse of A
 */
matrix* CalcInv(matrix* A)
{
    matrix *inv, *adj;
    int i, j;
    double det;

    inv = CreateMatrix(nRows(A), nRows(A));

    /* If someone sticks a 1x1 matrix in here, do this. */
    if(nRows(A) == 1 && nCols(A) == 1) {
        setval(inv, 1/val(A, 0, 0), 0, 0);
        return inv;
    }

    det = CalcDeterminant(A);
    adj = CalcAdj(A);

    for(i=0; i<nRows(A); i++) {
        for(j=0; j<nRows(A); j++) {
            setval(inv, val(adj, i, j)/det, i, j);
        }
    }

    return inv;
}

/**
 * @brief Apply a function to every value in a matrix
 *
 * No value is returned because the original matrix is operated on.
 *
 * @param A The matrix of values
 * @param func The function to apply. It should accept a single double as an
 * argument and return a double.
 */
void Map(matrix* A, double (*func)(double))
{
    int i, j;
    for(i=0; i<nRows(A); i++) {
        for(j=0; j<nCols(A); j++) {
            setval(A, (*func)(val(A, i, j)), i, j);
        }
    }
}

/**
 * @brief Make an agumented matrix from the two arguments
 * This is used to set up a matrix for the equation solver. Basically, matrix
 * B is stuck on the end of A like this: [A | B].
 * @param A The first matrix
 * @param B Second matrix
 * @returns A matrix composed of the first matrix on the left and the second
 * on the right.
 */
matrix* AugmentMatrix(matrix *A, matrix *B)
{
    int i, j;
    matrix *C;
    C = CreateMatrix(nRows(A), nCols(A)+nCols(B));
    for(i=0; i<nRows(A); i++) {
        for(j=0; j<nCols(A); j++) {
            setval(C, val(A, i, j), i, j);
        }
        for(j=0; j<nCols(B); j++) {
            setval(C, val(B, i, j), i, j+nCols(A));
        }
    }

    return C;
}

/**
 * @brief Pull out a column of a matrix.
 * @param A The matrix to pull the column from
 * @param col The column to get (numbering starts with 0)
 * @returns A column matrix containing the values from the desired column of A
 */
matrix* ExtractColumn(matrix* A, int col)
{
    matrix *B;
    int i;
    B = CreateMatrix(nRows(A), 1);

    for(i=0; i<nRows(A); i++) {
	setval(B, val(A, i, col), i, 0);
    }

    return B;
}

/**
 * @brief Pull out a row of a matrix.
 * @param A The matrix to pull the row from
 * @param row The row to get (numbering starts with 0)
 * @returns A row matrix containing the values from the desired column of A
 */
matrix* ExtractRow(matrix* A, int row)
{
    matrix *B;
    int i;
    B = CreateMatrix(1, nCols(A));

    for(i=0; i<nCols(A); i++) {
	setval(B, val(A, row, i), 0, i);
    }

    return B;
}

/**
 * Search through the matrix and delete any rows containing a NaN value.
 * @param A Matrix to search
 * @returns A new matrix containing only those rows without any NaN values.
 */
matrix* DeleteNaNRows(matrix *A)
{
    matrix *B;
    int *keep, /* List of rows to not delete */
        currow = 0, /* Current row */
        rows = 0, cols = 0, /* Dimensions of the output matrix */
        i, j;

    /* Allocate memory to store the indicies of the rows to output */
    cols = nCols(A);
    keep = (int*) calloc(sizeof(int), nRows(A));

    /* Figure out which rows contain only numerical values */
    for(i=0; i<nRows(A); i++) {
        keep[i] = 1;
        for(j=0; j<nCols(A); j++) {
            if(isnan(val(A, i, j)))
                keep[i] = 0;
        }
    }

    /* Count the total number of rows to output */
    for(i=0; i<nRows(A); i++) {
        rows += keep[i];
    }

    /* Make a matrix of the appropriate size */
    B = CreateMatrix(rows, cols);

    /* Copy over the values from the original matrix */
    for(i=0; i<nRows(A); i++) {
        if(keep[i]) {
            for(j=0; j<nCols(A); j++)
                setval(B, val(A, i, j), currow, j);
            currow++;
        }
    }

    free(keep);

    return B;
}

