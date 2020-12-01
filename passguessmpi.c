#include <stdio.h>
#include <microtime.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>

MPI_Status status;

char* makeGuess(char *guess, char *known, int length, int* unknown) {

	int i = *unknown;
	
        guess[i]++;
	
	return guess;
}

char checkGuess(char *guess, char *pw, char *known, int length, int* unknown) {
	char isCorrect = 0;
	int i = *unknown;

	if(guess[i] == pw[i]) {
		// we found a matching character
		known[i] = 1;
		*unknown += 1;
		if (i == length) {
			isCorrect = 1;
		}
	}
	return isCorrect;
}

char* init(int length) {
	char* arr;
	arr = malloc(length * sizeof(char));
	return arr;
}

int main(int argc, char **argv){

int rank, size;


MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD,&size); 
printf("RANK %d\t and SIZE %d\n",rank, size);
  if(argc != 1)
  {
    fprintf(stderr, "USAGE: %s Password Length\n", argv[1]);
    exit(1);
  }

  if (rank == 0) {
 int c, lines =1;
FILE * fp = fopen("PASSWORDFILE", "r");

        /* count the newline characters */
    while ( (c=fgetc(fp)) != EOF ) {
        if ( c == '\n' )
            lines++;
    }
	printf("Line count-%d\n",lines);
MPI_Finalize();
}

if (rank >0) {
  double t, time1, time2, incrementer = 0, totalTime = 0.00;
 
	FILE * fp = fopen("PASSWORDFILE", "r");
	char * line = NULL;
  	size_t len = 0;
	ssize_t read;


    	if (fp == NULL) {
		printf("FILE NOT FOUND. TRY AGAIN");
        	exit(EXIT_FAILURE);
	}
	

  	
    while ((read = getline(&line, &len, fp)) != -1) {

 	long length = strlen(line);
	char solved = 0;
  	char *pw, *guess, *known;
	int unknown = 0;

  pw = init(length);
  guess = init(length);
  known = init(length);

  int i;
  for(i = 0; i < length; i++) {
  	pw[i] = line[i];
  }

  time1 = microtime();
printf("TIME1 is %f",time1);

  while(!solved) {

	  guess = makeGuess(guess, known, length, &unknown);
//incrementer+=1;
	  solved = checkGuess(guess, pw, known, length, &unknown);
  }
  time2 = microtime();
printf("TIME1 is %f",time1);

  t = time2-time1;
  totalTime += t;
  printf("The password is %s", guess);
  printf("Intermediate Time = %g us\t  Timer Resolution = %g us\t\n", t, get_microtime_resolution());

  free(pw);
  free(guess);
  free(known);

    }
MPI_Finalize();

  printf("TOTAL RUNTIME = %g us\n", totalTime);
 //printf("Performance = %g increments \n", incrementer);
    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}


  return 0;
}