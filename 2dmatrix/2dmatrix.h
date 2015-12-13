/**
 * @file 2dmatrix.h
 * Define a data structure for a two-dimensional matrix of arbitrary size
 */

#ifndef _2DMATRIX_H
#define _2DMATRIX_H

///Maximum number of rows to allow
#define MAXROWS 800000
///Maximum number of columns
#define MAXCOLS 100
///The length of each line of text that is parsed
#define LINELENGTH 100

/**
 * @brief Add a value to an element in a matrix
 *
 * Macro to shorten code where a number is added to the current value of an
 * element in a matrix.
 *
 * @param A The matrix to add the value in
 * @param VAL The value to add
 * @param I The row of the matrix the component is located in
 * @param J The column of the matrix
 */
#define addval(A, VAL, I, J) setval((A), (VAL) + val((A), (I), (J)), (I), (J))

/**
 * @struct matrix
 * @brief A data structure for holding two-dimensional matricies
 * @var matrix::array
 * A pointer to the raw data
 * @var matrix::rows
 * Number of rows in the matrix
 * @var matrix::cols
 * Number of columns
 */
typedef struct {
    double **array;
    int rows;
    int cols;
} matrix;

void DestroyMatrix(matrix*);
int nCols(matrix*);
int nRows(matrix*);
double val(matrix*, int, int);
void setval(matrix*, double, int, int);
matrix* CreateMatrix(int, int);
matrix* CreateOnesMatrix(int, int);
matrix* linspace(double, double, int);
matrix* CopyMatrix(matrix*);

matrix* CalcMinor(matrix*, int, int);
double CalcDeterminant(matrix*);
double mtxextrm(matrix*);
matrix* mtxtrn(matrix*);
matrix* mtxmul(matrix*, matrix*);
matrix* mtxmulconst(matrix*, double k);
matrix* mtxadd(matrix*, matrix*);
matrix* mtxsub(matrix*, matrix*);
matrix* mtxneg(matrix*);
matrix* CalcAdj(matrix*);
matrix* CalcInv(matrix*);
matrix* ExtractColumn(matrix*, int);
matrix* ExtractRow(matrix*, int);
matrix* AugmentMatrix(matrix*, matrix*);
matrix* DeleteNaNRows(matrix*);

void Map(matrix*, double (*func)(double));

matrix* ParseMatrix(char*);
void mtxprnt(matrix*);
void mtxprntfile(matrix*, char*);
void mtxprntfilehdr(matrix*, char*, char*);
matrix* mtxloadcsv(char*, int);

//#define val(MATRIX, ROW, COL) (MATRIX)->array[(int) (ROW)][(int) (COL)]

#endif

