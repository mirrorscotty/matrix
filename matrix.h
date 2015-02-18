/**
 * @file matrix.h
 * Include this file to include everything in the matrix library
 */

#ifndef MATRIX_H
#define MATRIX_H

#include "2dmatrix/2dmatrix.h"
#include "2dmatrix/mtxsolver.h"
#include "vector/vector.h"

matrix* CatColVector(int, ...);
vector* ExtractColumnAsVector(matrix*, int);

matrix* meshgridX(vector*, vector*);
matrix* meshgridY(vector*, vector*);

#endif

