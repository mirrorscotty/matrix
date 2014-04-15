/**
 * @file 2dmatrixio.c
 * Contains all of the input/output functions for matricies
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "xstrtok.h"
#include "2dmatrix.h"

/**
 * @brief Print out a matrix
 * @param A The matrix to print
 */
void mtxprnt(matrix *A)
{
    int i, j;
    double v;
    
    for(i=0; i<nRows(A); i++) {
        printf("[ ");
        for(j=0; j<nCols(A); j++) {
            v = val(A, i, j);
            /* If the value is annoyingly close to zero, just print out zero
             * instead. */
            if(fabs(v) < 1e-14)
                printf("%e ", 0.0);
            else
                printf("%e ", v);
        }
        printf("]\n");
    }
}

/**
 * @brief Print a matrix out to some random file
 * @param A The matrix to print
 * @param filename The filename to print to
 */
void mtxprntfile(matrix *A, char *filename)
{
    int i, j;
    FILE *file;

    file = fopen(filename, "w");
    
    for(i=0; i<nRows(A); i++) {
        for(j=0; j<nCols(A)-1; j++) {
            fprintf(file, "%e,", val(A, i, j));
        }
        fprintf(file, "%e\n", val(A, i, nCols(A)-1));
    }
    fclose(file);
}

/**
 * @brief Load a matrix from a CSV file.
 * @param filename The filename to load data from
 * @param number of the first row to load.
 * @return A matrix containing all the values in the CSV file
 */
matrix* mtxloadcsv(char* filename, int row1)
{
    matrix *A;
    int maxlines = MAXROWS,
        maxchars = LINELENGTH,
        i, j,
        ncols = 1, /* Assume there's at least one column */
        nrows = 0;
    const char *delim = ",";
    char **buffer;
    char *number;
    FILE *fp; /* TODO: Actually open/read the file */

    /* Make a buffer to store all of the characters read from the file */
    buffer = (char**) calloc(sizeof(char*), maxlines);
    for(i=0; i<maxlines; i++)
        buffer[i] = (char*) calloc(sizeof(char), maxchars);

    /* Load in all the lines (up to the specified limits) */
    fp = fopen(filename, "r");
    for(i=0; i<maxlines; i++) {
        if(fgets(buffer[i], maxchars, fp) == NULL) {
            nrows = i;
            break;
        }
    }
    fclose(fp);

    /* Check the first line to see how many values there are. */
    i = row1;
    while(buffer[0][i]) {
        if(buffer[0][i] == delim[0])
            ncols++;
        i++;
    }

    /* Make a matrix that's hopefully the right size */
    A = CreateMatrix(nrows, ncols);
    /* Start putting values into it */
    for(i=row1; i<nrows; i++) {
        /* Get the first value and store it */
        number = xstrtok(buffer[i], delim);
            if(number[0] == '\0')
                setval(A, NAN, i, 0);
            else
                setval(A, atof(number), i, 0);

        /* Get the rest */
        j = 1;
        while((number = xstrtok(NULL, delim))) {
            if(number[0] == '\0' || number[0] == '\n')
                setval(A, NAN, i, j);
            else {
                setval(A, atof(number), i, j);
                //if(!atof(number))
                   //printf("%s",number);
            }
            j++;
        }
        for(; j<nCols(A); j++)
            setval(A, NAN, i, j);
    }

    for(i=0; i<maxlines; i++)
        free(buffer[i]);
    free(buffer);
    free(number);

    return A;
}

/**
 * @brief Create a matrix from a line of text.
 *
 * This takes a random string of characters of the format [4,5,2;5,1,4] and
 * turns it into a nifty matrix.
 *
 * @param raw The character pointer to the string of characters
 * @returns A matrix created from the input
 */
matrix* ParseMatrix(char* raw)
{
    char *processed, *tmp;
    char **rows;
    double **values;
    matrix *out;
    int i, j;
    int nrows, ncols;

    processed = calloc(sizeof(char), MAXROWS*LINELENGTH);
    tmp = processed;

    while(*raw) {
        if(*raw == '[')
            *tmp = ' ';
        else if(*raw == ']')
            *tmp = ' ';
        else
            *tmp = *raw;
        tmp++;
        raw++;
    }

    /* Allocate memory to store the rows of the matrix as strings */
    values = (double**) calloc(sizeof(double*), MAXROWS);
    rows = (char**) malloc(sizeof(char*)*MAXROWS);
    for(i=0; i<MAXROWS; i++) {
        values[i] = (double*) calloc(sizeof(double), MAXCOLS);
        rows[i] = (char*) calloc(sizeof(char), LINELENGTH);
    }

    /* Row 1: */
    i = 0;
    tmp = strtok(processed, ";");
    strncpy(rows[i], tmp, LINELENGTH);

    /* All subsequent rows */
    for(i=1; (tmp = strtok(NULL, ";")); i++) {
        strncpy(rows[i], tmp, LINELENGTH);
    }

    nrows = i;

    for(i=0; i<nrows; i++) {
        /* First column */
        j=0;
        tmp = strtok(rows[i], ",");
        values[i][j] = atof(tmp);

        ncols = 1;
        /* Rest of the columns */
        for(j=1; (tmp = strtok(NULL, ",")); j++) {
            if(j>ncols-1)
                ncols = j+1;
            values[i][j] = atof(tmp);
        }
    }

    out = CreateMatrix(nrows, ncols);
    for(i=0; i<nrows; i++) {
        for(j=0; j<ncols; j++)
            setval(out, values[i][j], i, j);
    }

    /* Free stuff */
    free(processed);
    for(i=0; i<MAXROWS; i++) {
        free(values[i]);
        free(rows[i]);
    }
    free(rows);
    free(values);
    
    return out;
}

