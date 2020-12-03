CC=mpicc
CFLAG=  -I. -Ofast -fopenmp

EXECUTABLE=passguessmpi
EXECUTABLE2=passguessmpi_mason

all: $(EXECUTABLE) $(EXECUTABLE2)

passguessmpi:  passguessmpi.c microtime.h
	$(CC) $(CFLAG) -c microtime.c
	$(CC) $(CFLAG) -o passguessmpi passguessmpi.c microtime.o

passguessmpi_mason:  passguessmpi_mason.c microtime.h
	$(CC) $(CFLAG) -c microtime.c
	$(CC) $(CFLAG) -o passguessmpi_mason passguessmpi_mason.c microtime.o
clean:
	rm -f *.o *~ core

realclean:
	rm -f *.o *~ core $(EXECUTABLE) $(EXECUTABLE2)
