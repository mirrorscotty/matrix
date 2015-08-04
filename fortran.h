#ifndef FORTRAN_H
#define FORTRAN_H

void dgesv_(int *n, /* Number of linear equations */
            int *nrhs, /* Number of columns in the "b" matrix */
            double *a, /* dimension (lda, n) matrix */
            int *lda, /* Leading dimension of A */
            int *ipivot, /* Integer array of dimension (n) */
            double *b, /* Right hand side matrix (ldb, nrhs) */
            int *ldb, /* Leading dimension of "b" */
            int *info); /* Returns zero on successful exit */

#endif

