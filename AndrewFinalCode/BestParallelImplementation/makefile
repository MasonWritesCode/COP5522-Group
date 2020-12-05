CC=mpicc
CFLAG=  -I. -Ofast -fopenmp

EXECUTABLE=passguessmpiomp

all: $(EXECUTABLE)

passguessmpiomp:  passguessmpiomp.c ../microtime.h
	$(CC) $(CFLAG) -c ../microtime.c
	$(CC) $(CFLAG) -o passguessmpiomp passguessmpiomp.c microtime.o

clean:
	rm -f *.o *~ coremakefile

realclean:
	rm -f *.o *~ core $(EXECUTABLE) $(EXECUTABLE2)
