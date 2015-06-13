VPATH=2dmatrix vector
CC=gcc
CFLAGS=-ggdb -Wall -O2
OBJ=2dmatrix/2dmatrix.o 2dmatrix/2dmatrixio.o 2dmatrix/2dmatrixops.o 2dmatrix/mtxsolver.o 2dmatrix/xstrtok.o vector/vector.o vector/vectorio.o vector/vectorops.o other.o

all: matrix.a

-include $(OBJ:.o=.d)

matrix.a: $(OBJ)
	ar -cvr $@ $?

doc: Doxyfile
	doxygen Doxyfile

clean:
	rm -rf matrix.a doc
	rm -rf $(OBJ)
	rm -rf $(OBJ:.o=.d)

%.o: %.c
	$(CC) -c $(CFLAGS) $*.c -o $*.o
	$(CC) -MM $(CFLAGS) $*.c > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

