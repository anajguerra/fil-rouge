#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 256


int * comptage(char argv[]){
	int i=0;
	int k=0;
	int * occurence = NULL;
	occurence = (int *) malloc(MAXLEN * sizeof (int));
	for (i=0;i<MAXLEN;i++){
	occurence[i]=0;
	}
	while (argv[k]!='\0'){
	occurence[argv[k]]++;
	k++;
	}
	return occurence;
	}


