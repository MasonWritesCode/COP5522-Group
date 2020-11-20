#include <stdio.h>
#include <microtime.h>
#include <string.h>
#include <stdlib.h>

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
  if(argc != 1)
  {
    fprintf(stderr, "USAGE: %s Password Length\n", argv[1]);
    exit(1);
  }

  	double t, time1, time2;
	double totalTime = 0.00;
	FILE * fp;
	char * line = NULL;
  	size_t len = 0;
	ssize_t read;

	fp = fopen("PASSWORDFILE", "r");
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
  while(!solved) {
	  guess = makeGuess(guess, known, length, &unknown);
	  solved = checkGuess(guess, pw, known, length, &unknown);
  }
  time2 = microtime();

  t = time2-time1;
  totalTime += t;
  printf("The password is %s", guess);
  printf("Intermediate Time = %g us\t  Timer Resolution = %g us\t\n", t, get_microtime_resolution());

  free(pw);
  free(guess);
  free(known);

    }
  printf("TOTAL RUNTIME = %g us\n", totalTime);
    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);

  return 0;
}

