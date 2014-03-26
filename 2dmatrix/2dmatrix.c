/**
 * @file 2dmatrix.c
 * This file contains all sorts of nifty matrix functions. All of the matricies
 * here have indicies that start with 0 instead of 1.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>

#include "2dmatrix.h"

/**
 * @brief Create a matrix of equally spaced points
 *
 * This is the equivalent of the Matlab linspace command.
 * 
 * @param start First value
 * @param end Last value
 * @param Number of points to put in the matrix
 * @return Row matrix containing "nelem" points
 */
matrix* linspace(double start, double end, int nelem)
{
    matrix* x;
    int i;
    
    x = CreateMatrix(1, nelem);
    for(i=0; i<nelem; i++) {
        setval(x, start + i*(end-start)/(nelem-1), 0, i);
    }

    return x;
}
    
/**
 * @brief Get the number of columns in a 1D matrix of doubles.
 * @param A The matrix!
 * @return Number of columns 
 */
int nCols(matrix *A)
{
    return A->cols;
}

/**
 * @brief Return the number of rows in a two dimensional matrix of doubles.
 *
 * @param A The matrix of interest
 * @return Number of rows
 */
int nRows(matrix *A)
{
    return A->rows;
}

/**
 * @brief Get the value of a specific element in a matrix.
 *
 * @param A The matrix containing the values
 * @param row The row to pull the value from
 * @param col The column to pull the value from
 * @return The value stored at row, col in matrix A
 */
double val(matrix *A, int row, int col)
{
    if((row >= nRows(A)) ||  (col >= nCols(A)) || (row < 0) || (col < 0)) {
        //fprintf(stderr, "Error: index out of bounds. (%d, %d)\n", row, col);
        return NAN;
    }
    return A->array[row][col];
}

/**
 * Set the value of a particular element of a matrix.
 *
 * @param A The matrix to set the value in
 * @param value The value to set
 * @param row The row
 * @param col Column
 */
void setval(matrix *A, double value, int row, int col)
{
    if((row >= nRows(A)) ||  (col >= nCols(A)) || (row < 0) || (col < 0)) {
        //fprintf(stderr, "Error: index out of bounds. (%d, %d)\n", row, col);
        return;
    }
    A->array[row][col] = value;
}

/**
 * @brief Make a matrix!
 *
 * Create a matrix of the specified dimensions and initialize all the values
 * and initialize all the values to zero.
 * 
 * @param row The number of rows
 * @param col Number of columns
 * @returns The new matrix
 */
matrix* CreateMatrix(int row, int col)
{
    matrix *A;
    int i;
    A = NULL;

    if((row == 0) || (col == 0)) {
        printf("Matrix too small.");
        return A;
    }

    A = (matrix*) malloc(sizeof(matrix));
    if(!A) {
        fprintf(stderr, "Memory allocation error: %s\n", strerror(errno));
    }

    A->array = NULL;
    A->rows = 0;
    A->cols = 0;

    A->array = (double**) calloc(row, sizeof(double*));
    if(!A->array) {
        fprintf(stderr, "Memory allocation error: %s\n", strerror(errno));
        return A;
    }

    for(i=0; i<row; i++) {
        A->array[i] = (double*) calloc(col, sizeof(double));
        if(!A->array[i]) {
            fprintf(stderr, "Failed to allocate %lu bytes: %s\n", (unsigned long) sizeof(double)*col, strerror(errno));
            return A;
        }
    }

    A->rows = row;
    A->cols = col;
    
    return A;
}

/**
 * @brief Make a matrix of ones.
 * 
 * Basically does the same thing as CreateMatrix, only it initializes each value
 * to one instead of zero.
 *
 * @param row Number of rows
 * @param col Number of columns
 * @returns A matrix
 */
matrix* CreateOnesMatrix(int rows, int cols)
{
    int i, j;
    matrix *A;
    A = CreateMatrix(rows, cols);
    for(i=0; i<rows; i++) {
        for(j=0; j<cols; j++) {
            setval(A, 1, i, j);
        }
    }
    return A;
}

/**
 * @brief Make a copy of a matrix in a new memory location.
 * @param source The matrix to copy
 * @return A pointer to the newly created copy.
 */
matrix* CopyMatrix(matrix *source)
{
    int i, j;
    matrix *dest;
    dest = CreateMatrix(nRows(source), nCols(source));
    for(i=0; i<nRows(source); i++) {
        for(j=0; j<nCols(source); j++) {
            setval(dest, val(source, i, j), i, j);
        }
    }
    return dest;
}

/**
 * @brief Free the memory allocated by CreateMatrix
 * @param A The matrix to destroy
 */
void DestroyMatrix(matrix *A)
{
    int i;

    for(i=0; i<A->rows; i++) {
        free(A->array[i]);
    }
    free(A->array);
    free(A);
}

