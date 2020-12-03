#include <stdio.h>
#include <microtime.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>

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

int rank, size, linesPerNode,fileLines;

MPI_Status status;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD,&size); 
//printf("RANK %d\t and SIZE %d\n",rank, size);



  if (rank == 0) {
	double t, time1, time2,totalTime;;
	FILE * fp;
	char * line = NULL;
  	size_t len = 0;
	ssize_t read;
	int dest, c,linesLastNode,done;
	fileLines = 0;


fp = fopen("PASSWORDFILE.txt", "r");

	while ( (c=fgetc(fp)) != EOF ) {
		if ( c != '\n' )
		{
	    		read = getline(&line, &len, fp);
						fileLines++;
  		}
    	}
	//printf("fileLines-%d\n",fileLines);
	//printf("size is %d",size);
	if (fileLines % (size-1) == 0) 
	{ 
		//printf("EQUAL");
		linesPerNode = fileLines/(size-1);
		linesLastNode= linesPerNode;
		//printf ("Lines and last: %d and %d\n",linesPerNode,linesLastNode);
	}
	else { 
		//printf("UNEQUAL");
		linesPerNode = fileLines/(size-1);
		linesLastNode = (fileLines - (linesPerNode * (size -2)));
		//printf ("Lines and last: %d and %d\n",linesPerNode,linesLastNode);
	}

//rewind(fp);
	

 for (dest=1; dest < size; dest++)
    {
	if (dest == (size -1) ) {
		linesPerNode = linesLastNode;
	}
		MPI_Send(&linesPerNode,1,MPI_INT,dest,1,MPI_COMM_WORLD);
		MPI_Send(&fileLines,1,MPI_INT,dest,1,MPI_COMM_WORLD);
//printf("linesPerNode %d and rank %d", linesPerNode,dest);
	
    }
	time1 = microtime();
	for (dest=1; dest < size; dest++)
    {
	
	MPI_Recv(&done,1,MPI_INT,dest,1,MPI_COMM_WORLD,&status);
    }
	time2 = microtime();
	t = time2-time1;
	printf("TOTAL RUNTIME = %g us\n", t);
	
	fclose(fp);
	MPI_Finalize();

}

if (rank > 0) {
	double t, time1, time2,totalTime = 0.00;
	FILE * fp = fopen("PASSWORDFILE.txt", "r");
	char * line = NULL;
  	size_t len = 0;
	ssize_t read;
	int endLine, startLine, curFileLine,linesPerNode;
  	
	MPI_Recv(&linesPerNode,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
  	MPI_Recv(&fileLines,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
	//printf("RANK %d LINESPER %d FILESIZE %d\n",rank,linesPerNode,fileLines);

 if (rank != (size -1)) { 
	startLine = (linesPerNode * rank)-(linesPerNode -1);
 	endLine = startLine + linesPerNode;
	//printf("start: %d and end: %d\n",startLine, endLine);
 	}
 	else {
		//printf("LAST NODE:%d\t",rank);  
		startLine = (fileLines - linesPerNode)+1;
		
 		endLine = fileLines + 1; 
		//printf("start: %d and end: %d\n",startLine, endLine);
	}
    curFileLine=0;
    while ((read = getline(&line, &len, fp)) != -1) {
	curFileLine++;
	if ((startLine <= curFileLine) && (curFileLine < endLine)) {
		//printf("start %d and curfileline %d and end line %d\n",startLine,curFileLine,endLine);
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
 
  while(!solved) {

	  guess = makeGuess(guess, known, length, &unknown);

	  solved = checkGuess(guess, pw, known, length, &unknown);
  }

//printf("The password on rank %d is %s\t", rank,guess);


 //printf("rank %d time %g\n",rank,t);
  //totalTime += t;

  free(pw);
  free(guess);
  free(known);

    }
	}
int done=1;
MPI_Send(&done,1,MPI_INT,0,1,MPI_COMM_WORLD);
		
//printf("linesPerNode %d and rank %d", linesPerNode,dest);
	
   
fclose(fp);
MPI_Finalize();


    if (line)
        free(line);
		
	}
	exit(EXIT_SUCCESS);

  return 0;
}