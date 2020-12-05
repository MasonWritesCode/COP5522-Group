CC=mpicc
CFLAG=  -I. -Ofast -fopenmp

EXECUTABLE=passguessoptseq

all: $(EXECUTABLE)

passguessoptseq:  passguessoptseq.c ../microtime.h
	$(CC) $(CFLAG) -c ../microtime.c
	$(CC) $(CFLAG) -o passguessoptseq passguessoptseq.c microtime.o

clean:
    rm -f *.o *~ core

realclean:
	rm -f *.o *~ core $(EXECUTABLE)
