#include <stdio.h>
#include <stdlib.h>
#include "../include/traces.h" 
#include "../include/check.h" 

int nombre_car(char * fichier){
	int compte=0;
	FILE *f;
	CHECK_IF(f= fopen(fichier,"w"), NULL, "erreur fopen dans l'ouverture du fichier");
	// On compte le nombre de caractère dans le fichier
	while (fgetc(f) !=EOF){
		compte++;
		}
	return compte;
	}

char * caracteres(char * fichier){
	int i=0;
	i=nombre_car(fichier);
	FILE *f;
	CHECK_IF(f= fopen(fichier,"w"), NULL, "erreur fopen dans l'ouverture du fichier");
	char * carac;
	carac = (char *)malloc(i * sizeof (char));
	int k=0;
	//On ajoute chaque caractère du fichier à la chaine de caractères
	while (k<i){
		carac[k]=fgetc(f);
		k++;
		}
	return carac;
	}

	
