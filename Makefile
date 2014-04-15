VPATH=2dmatrix vector
CC=gcc
CFLAGS=-ggdb -Wall -O2
OBJ=2dmatrix.o 2dmatrixio.o 2dmatrixops.o mtxsolver.o xstrtok.o vector.o vectorio.o vectorops.o other.o

all: matrix.a

matrix.a: $(OBJ)
	ar -cvq $@ $?

doc: Doxyfile
	doxygen Doxyfile

2dmatrix.o: 2dmatrix.h

2dmatrixio.o: 2dmatrix.h

2dmatrixops.o: 2dmatrix.h xstrtok.h

mtxsolver.o: mtxsolver.h

xstrtok.o: xstrtok.h

vector.o: vector.h

vectorio.o: vector.h

vectorops.o: vector.h

other.o: matrix.h 2dmatrix.h vector.h

clean:
	rm -rf matrix.a $(OBJ) doc


