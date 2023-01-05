#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h> 
// ceil, floor : #include <math.h>


#include "../include/traces.h" 
#include "../include/check.h" 

#include "elt.h"

#define HEAP_ALLOCATION_OFFSET 5

typedef struct {
	unsigned int nbElt;
	unsigned int nbMaxElt;
	T_elt * tree;	
} T_heap;

#define iPARENT(i) 			(i-1)/2
#define iLCHILD(i) 			(2*i)+1
#define iRCHILD(i) 			(2*i)+2
#define iLASTINTERNAL(n)	n/2 -1
#define isINTERNAL(i,n) 	(2*i<(n-1))
#define isLEAF(i,n) 			(2*i>=(n-1))
#define isINTREE(i,n)		(i<n)
#define isROOT(i)				(i==0)
#define nbINTERNALS(n) 		n/2
#define nbLEAVES(n) 			ceil((double)n/2)
#define VALP(pHeap, i)		pHeap->tree[i]		
#define VAL(heap, i)			heap.tree[i]		

T_heap * newHeap(unsigned int nbMaxElt);
void freeHeap(T_heap *p); 
T_heap * initHeap(T_elt t[], int n) ;
void showHeap(T_heap *p);
void showHeap_rec(T_heap *p, int root, int indent); 

void swap(T_heap *p, int i, int j);
void siftUp(T_heap *p, int k);
void addElt(T_heap *p, T_elt e);
void buildHeapV1(T_heap * p);

void siftDown(T_heap *p, int k);
T_elt getMax(const T_heap *p);
T_elt removeMax(T_heap *p);
void buildHeapV2(T_heap * p); 

void heapSortV1(T_heap *p);
void heapSortV2(T_heap *p);
 

// Tout est déjà écrit ! //////////////////////////////////////////////////

T_heap * newHeap(unsigned int nbMaxElt){

	T_heap * pAux;
	CHECK_IF(pAux = malloc(sizeof(T_heap)), NULL, "erreur malloc");
	CHECK_IF(pAux->tree = malloc(nbMaxElt * sizeof(T_elt)), NULL, "erreur malloc");
	pAux->nbElt = 0; 
	pAux->nbMaxElt = nbMaxElt; 
	
	return pAux; 

}

void freeHeap(T_heap *p) {
	free(p->tree);
	free(p);
}


T_heap * initHeap(T_elt t[], int n) {
	T_heap *pAux = newHeap(n + HEAP_ALLOCATION_OFFSET); 
	memcpy(pAux->tree, t, n * sizeof(T_elt)); 
	pAux->nbMaxElt = n + HEAP_ALLOCATION_OFFSET;
	pAux->nbElt = n; 
	return pAux; 
}

void showHeap(T_heap *p) {

	printf("Affichage du tas (nbElt : %d)\n",p->nbElt);
	showHeap_rec(p,0,0); 
}

void showHeap_rec(T_heap *p, int root, int indent) {
	// affiche récursivement en mode pseudo graphique 
	// ordre de récurrence  : taille du sous-arbre 
	int i; 
	
	if (! isINTREE(root,p->nbElt)) return;  
	
	showHeap_rec(p, iRCHILD(root), indent+1);
	for(i=0;i<indent;i++) {
		printf("\t"); 
	}
	printf("%s(i:%d)\n",toString(VALP(p,root)), root);
	showHeap_rec(p, iLCHILD(root), indent+1);
}

void swap(T_heap *p, int i, int j) {
	T_elt aux; 
	aux = p->tree[i]; 
	p->tree[i] = p->tree[j];
	p->tree[j] = aux; 
}



void siftDownPointeur(T_heap *p, int k,T_elt *data) {
	
	int n = p->nbElt; 
	int i; 
	if (! isINTREE(k,n)) return; 
	 
	while ( ! isLEAF(k,n) ) {
		if (isINTREE(iRCHILD(k),n) && (eltCmp(data[VALP(p,iRCHILD(k))],data[VALP(p,iLCHILD(k))]) < 0)  ) i = iRCHILD(k); 
		else i = iLCHILD(k); 
		
		if (eltCmp(data[VALP(p,k)],data[VALP(p,i)]) > 0) {
			swap(p, k,i);
			k = i; 
		} else break;  
		
	}
}

void siftDown(T_heap *p, int k) {

	int n = p->nbElt; 
	int i; 
	if (! isINTREE(k,n)) return; 
	 
	while ( ! isLEAF(k,n) ) {
		if (isINTREE(iRCHILD(k),n) && (eltCmp(VALP(p,iRCHILD(k)),VALP(p,iLCHILD(k))) < 0)  ) i = iRCHILD(k); 
		else i = iLCHILD(k); 
		
		if (eltCmp(VALP(p,k),VALP(p,i)) > 0) {
			swap(p, k,i);
			k = i; 
		} else break;  
		
	}
}

void addEltPointeur(T_heap *p, T_elt e) {
	p->tree[p->nbElt] = e; 
	p->nbElt++; 
	siftDownPointeur(p,p->nbElt-1);
}




T_elt getMin(const T_heap *p){
	return p->tree[0];
}


T_elt removeMinPointeur(T_heap *p) {
	T_elt aux; 
	aux = p->tree[0]; 
	swap(p,0,p->nbElt-1);
	p->nbElt--; 
	siftDownPointeur(p,0);
	return aux; 

}

void addElt(T_heap *p, T_elt e) {
	p->tree[p->nbElt] = e; 
	p->nbElt++; 
	siftDown(p,p->nbElt-1);
}


void buildHeapPointeur(T_heap *p){
	int k;
	for(k=0;k < p->nbMaxElt; k++) {
		if(p-> tree[k] != 0){
		siftDownPointeur(p, k);
		}
	}	
}

void buildHeap(T_heap *p){
	int k;
	for(k=0;k < p->nbMaxElt; k++) {
		if(p-> tree[k] != 0){
		siftDown(p, k);
		}
	}	
}






void heapsort(T_heap *p){
	int k = 0;
	int i = 0;
	int Newnoeud = 128;
	int temp;
	int nbtotchar = 0;
	
	T_heap *t = NewHeap(256);
	for(k;k < p->nbMaxElt; k++) {
		if(p-> tree[k] != 0){
		addEltPointeur(t, k);
		nbtotchar += p->tree[k];
		}
	}
	buildHeapPointeur(t);
	
	//init hufftree -256
	T_heap *Hufftree = NewHeap(255);
	for(i; i<256; i++){
		Hufftree->Tree[i] = -256;	
	}
	
	
	while(t->nbElt > 1){
		temp = removeMinPointeur(t);
		Hufftree-> tree[temp] = -Newnoeud;
		Hufftree->nbElt ++;
		p[Newnoeud] += p[temp];
		
		temp = removeMinPointeur(t);
		Hufftree-> tree[temp] = +Newnoeud;
		Hufftree->nbElt ++;
		p[Newnoeud] += p[temp];
		
		addElt(t, Newnoeud);
		
		Newnoeud ++;
	}
	
	p[Newnoeud] = nbtotchar;
}


char* codageBitsFromTableAscii(T_heap *p, char c){
	rep = malloc( 8 * sizeof(char));
	while(p->tree[c]!=-256){
		if(p->tree[c]<0){
			strcat(rep, "0");
			c = -p->tree[c];
		}
		else{
			strcat(rep, "1");
			c = p->tree[c];
		}
	}
	return rep;
}


int getRoot(T_heap *p){
	int k = p->nbElt; 
	for(k; k>0; k--){
		if(p->tree[k]!=-256){
			return k+1;
		}
	}
	if(k==0){
		return NULL;
	}
}


char* decodageBits(T_heap *p, char * input){
	int i=0;
	int k;
	int root;
	
	rep = malloc(sizeof(input)); 
	
	for(i; i<strlen(input); i++){
		k = 0;
		root = getRoot(p);
		for(k; k<p->nbElt; k++){
		
			if((p->tree[k] == root) && (k>=128)) {
				root = k;
				k = 0;
				i++;
			}
			if((p->tree[k] == -root) && (k<128)){
				strcat(rep, "k");
				i++;
				
			}
			
		}
		
	}
	return rep;
	
}























