#include <stdio.h>
#include <microtime.h>
#include <string.h>
#include <stdlib.h>

char* makeGuess(char *guess, int* unknown) {

	int i = *unknown - 1;
	
        guess[i]++;
	
	return guess;
}

char checkGuess(char *guess, char pw, char *known, int length, int* unknown) {
	char isCorrect = 0;
	int i = *unknown - 1;

	if(guess[i] == pw) {
		// we found a matching character
		known[i] = 1;
		*unknown += 1;
		if (i == length - 1) {
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
	int lines = 0;

	fp = fopen("PASSWORDFILE", "r");
    	if (fp == NULL) {
  	  printf("FILE NOT FOUND. TRY AGAIN");
          exit(EXIT_FAILURE);
	}

    while(!feof(fp)) {
  	char ch = fgetc(fp);
  	if(ch == '\n'){
    	   lines++;
  	}
    }

    rewind(fp);

    char passwords [lines][1000];
    for (int x = 0; x < lines; x++){
        read = getline(&line, &len, fp);
 	long length = strlen(line);
	passwords[x][0] = (char) length;
	for (int y = 1; y < length; y++){
		passwords[x][y] = line[y-1];
	}
    }

    char *guess, *known;
    guess = init(1000);
    known = init(1000);

    int solved;
    int unknown;
    for(int j=0; j < lines; j++){
        unknown = 1;
	solved = 0;
  	time1 = microtime();
  	while(!solved) {
	  	guess = makeGuess(guess, &unknown);
	  	solved = checkGuess(guess, passwords[j][unknown], known, (int) passwords[j][0], &unknown);
  	}	
  	time2 = microtime();

  	t = time2-time1;
  	totalTime += t;
  	printf("The password is %s ", guess);
  	printf("Intermediate Time = %g us\t  Timer Resolution = %g us\t\n", t, get_microtime_resolution());
    }
  	free(guess);
  	free(known);

  printf("TOTAL RUNTIME = %g us\n", totalTime);
    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);

  return 0;
}

