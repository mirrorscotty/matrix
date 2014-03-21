#ifndef MTXSOLVER_H
#define MTXSOLVER_H

#include "2dmatrix.h"

void ForwardSubstitution(matrix*);
void ReverseElimination(matrix*);
matrix* SolveMatrixEquation(matrix*, matrix*);

#endif
