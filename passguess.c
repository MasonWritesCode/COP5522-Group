#include <stdio.h>
#include <microtime.h>
#include <string.h>
#include <stdlib.h>

char* makeGuess(char *guess, char *known, int length, int* unknown) {
	int i;

	// find the index of the first unknown character
	for(i = *unknown; i < length; i++) {
		if(known[i] == 0) {
					break;
		}
	}
	
	guess[i]++;
	
	//printf("guess is : %s\n", guess);
	return guess;
}

char checkGuess(char *guess, char *pw, char *known, int length, int* unknown) {
	int i;
	char isCorrect = 1;

	for(i = *unknown; i < length; i++) {
		if(guess[i] == pw[i]) {
			// we found a matching character
			known[i] = 1;
			unknown = unknown + 1;
					}
		else {
			// we found a character that did not match
			known[i] = 0;
			isCorrect = 0;
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

