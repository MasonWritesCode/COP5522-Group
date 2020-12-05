CC=gcc
CFLAG=  -I. -Ofast -fopenmp

EXECUTABLE=passguessnonoptseq

all: $(EXECUTABLE)

passguessnonoptseq:  passguessnonoptseq.c ../microtime.h
        $(CC) $(CFLAG) -c ../microtime.c
        $(CC) $(CFLAG) -o passguessnonoptseq passguessnonoptseq.c microtime.o

clean:
        rm -f *.o *~ core

realclean:
        rm -f *.o *~ core $(EXECUTABLE)
