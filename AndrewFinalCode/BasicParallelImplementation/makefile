CC=mpicc
CFLAG=  -I. -Ofast

EXECUTABLE=passguessmpi

all: $(EXECUTABLE)

passguessmpi:  passguessmpi.c ../microtime.h
        $(CC) $(CFLAG) -c ../microtime.c
        $(CC) $(CFLAG) -o passguessmpi passguessmpi.c microtime.o

clean:
        rm -f *.o *~ core

realclean:
        rm -f *.o *~ core $(EXECUTABLE)
