/*
 * nn.c
 *
 *  Created on: 5 jul. 2016
 *      Author: ecesar
 *
 *      Descripció:
 *      Xarxa neuronal simple de tres capes. La d'entrada que són els pixels d'una
 *      imatge ppm (mirar descripció del format al comentari de readImg) de 50x50 (un total de 7500
 *      entrades). La capa oculta amb un nombre variable de neurones (amb l'exemple proporcionat 60
 *      funciona relativament bé, però si incrementem el nombre de patrons d'entrament caldrà variar-lo).
 *      Finalment, la capa de sortida (que ara té 6 neurones ja que només l'entrenem per reconéixer 6
 *      patrons, si es vol extendre caldrà augmentar aquest nombre).
 *      El programa passa per una fase d'entrenament en la qual processa un conjunt de patrons (en
 *      l'exemple proporcionat són 30 amb les lletres A, a, B, b, C, c, D, d, E, e, F i f, fent servir
 *      diferents fonts i mides). Un cop ha calculat els pesos entre la capa d'entrada i l'oculta i entre
 *      aquesta i la de sortida, passa a la fase de reconéixament, on llegeix 17 patrons d'entrada
 *      (es proporcionen exemples per aquests patrons), i intenta reconéixer de quina lletre es tracte.
 */

/*******************************************************************************
*    Aquest programa és una adaptació del fet per (el link a la pàgina i codi original el teniu a l'enunciat):
*
*    nn.c   1.0                                       � JOHN BULLINARIA  2004  *
*******************************************************************************/

/*      To compile use "cc nn.c -O -lm -o nn" and then run using "./nn"       */
/*      For explanations see:  http://www.cs.bham.ac.uk/~jxb/NN/nn.html       */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fcntl.h>
#include <string.h>
#include "nn-vo.h"
#include "common.h"

void freeDeltaWeights(double *DeltaWeightIH[], double *DeltaWeightHO[]){
	for( int i = 0; i < NUMHID; i++)
		free(DeltaWeightIH[i]);
	for( int i = 0; i < NUMOUT; i++)
		free(DeltaWeightHO[i]);
}

void freeWeights(double *WeightIH[],  double *WeightHO[]){
	for( int i = 0; i < NUMHID; i++)
		free(WeightIH[i]);
	for( int i = 0; i < NUMOUT; i++)
		free(WeightHO[i]);
}

void freeFList( int nf, char *flist[] ){
	for (int i = 0; i < nf; i++) free(flist[i]);
}

void freeTSet( int np, char **tset ){
	for( int i = 0; i < np; i++ ) free( tset[i] );
	free(tset);
}

/*
 * En primer lloc  el número màgic P6 (char *), després un comentari (al haver estat generades amb gimp),
 * després l'amplada de la imatge (char *), l'alçada (char *) i el valor màxim de color (char *),
 * després  un salt de línia i comença la llista de pixels.
 * Cada pixel está compost per tres bytes (valors RGB) codificats en binari.
 */
char *readImg( char *fname ){

	FILE *fd;
	char saux[100];
	int width, heigth, waste;
	char *img;


	if( (fd = fopen( fname, "rb" )) == NULL) return NULL;
	fscanf(fd,"%s\n", saux);
	if( strcmp("P6", saux) ) return NULL;
	fgets(saux,100,fd);
	fscanf(fd,"%d %d\n %d\n", &width, &heigth, &waste);

	img = (char *)malloc(width*heigth*3);
	printf("Reading Img %s (%d,%d) %d\n", fname, width, heigth, fread(img, 1, width*heigth*3, fd));
	fclose(fd);
	return img;
}

char **loadTrainingSet(int nf, char *ifileL[]){

	char **tset;

	tset = (char **)malloc(nf*sizeof(char *));
	int error = 0;

	for (int i = 0; i < nf; i++){
		if ((tset[i] = readImg( ifileL[i] )) == NULL) error = 1;
	}

	if (error) return NULL;
	return tset;
}

void trainN(){

	char **tSet;
	char *fname[NUMPAT];

	initFileList( fname );

	if( (tSet = loadTrainingSet(NUMPAT,fname)) == NULL){
		printf("Error!!\n");
		exit(-1);
	}

    double *DeltaWeightIH[NUMHID], smallwt = 0.1;

	for( int i = 0; i < NUMHID; i++){
		if ((WeightIH[i] = (double *)malloc((NUMIN)*sizeof(double))) == NULL){
			printf("Out of Mem\n");
			exit(-1);
		}
		if ((DeltaWeightIH[i] = (double *)malloc((NUMIN)*sizeof(double))) == NULL){
			printf("Out of Mem\n");
			exit(-1);
		}
	}
	for(int j = 0; j < NUMIN; j++)
		for( int i = 0; i < NUMHID; i++){
			WeightIH[i][j] = 2.0 * ( rando() + 0.5 ) * smallwt;
			DeltaWeightIH[i][j] = 0.0;
		}

	double *DeltaWeightHO[NUMOUT];

	for( int i = 0; i < NUMOUT; i++){
		if ((WeightHO[i] = (double *)malloc((NUMHID)*sizeof(double))) == NULL){
			printf("Out of Mem\n");
			exit(-1);
		}
		if ((DeltaWeightHO[i] = (double *)malloc((NUMHID)*sizeof(double))) == NULL){
			printf("Out of Mem\n");
			exit(-1);
		}
	}
	for(int j = 0; j < NUMHID; j++)
		for( int i = 0; i < NUMOUT; i++){
			WeightHO[i][j] = 2.0 * ( rando() + 0.5 ) * smallwt;
			DeltaWeightHO[i][j] = 0.0;
		}

    double Error, eta = 0.2, alpha = 0.5;
	int ranpat[NUMPAT];
	double Hidden[NUMPAT][NUMHID], Output[NUMPAT][NUMOUT], DeltaO[NUMOUT], DeltaH[NUMHID];

    for( int epoch = 0 ; epoch < 1000000 ; epoch++) {    // iterate weight updates
        for( int p = 0 ; p < NUMPAT ; p++ )   // randomize order of individuals
            ranpat[p] = p ;
        for( int p = 0 ; p < NUMPAT ; p++) {
            int np = rand()%NUMPAT;
            int op = ranpat[p] ; ranpat[p] = ranpat[np] ; ranpat[np] = op ;
        }
        Error = 0.0 ;

        printf("."); fflush(stdout);

        for( int np = 0 ; np < NUMPAT ; np++ ) {    // repeat for all the training patterns
        	double DeltaO[NUMOUT], DeltaH[NUMHID];
        	int p = ranpat[np];
			for( int j = 0 ; j < NUMHID ; j++ ) {    // compute hidden unit activations
				double SumH = 0.0;
				for( int i = 0 ; i < NUMIN ; i++ ) SumH += tSet[p][i] * WeightIH[j][i];
				Hidden[p][j] = 1.0/(1.0 + exp(-SumH)) ;
			}
			for( int k = 0 ; k < NUMOUT ; k++ ) {    // compute output unit activations and errors
				double SumO = 0.0;
				for( int j = 0 ; j < NUMHID ; j++ ) SumO += Hidden[p][j] * WeightHO[k][j] ;
				Output[p][k] = 1.0/(1.0 + exp(-SumO)) ;   // Sigmoidal Outputs
				Error += 0.5 * (Target[p][k] - Output[p][k]) * (Target[p][k] - Output[p][k]) ;   // SSE
				DeltaO[k] = (Target[p][k] - Output[p][k]) * Output[p][k] * (1.0 - Output[p][k]) ;   // Sigmoidal Outputs, SSE
			}
			for( int j = 0 ; j < NUMHID ; j++ ) {     // update weights WeightIH
				double SumDOW = 0.0 ;
				for( int k = 0 ; k < NUMOUT ; k++ ) SumDOW += WeightHO[k][j] * DeltaO[k] ;
				DeltaH[j] = SumDOW * Hidden[p][j] * (1.0 - Hidden[p][j]) ;
				for( int i = 0 ; i < NUMIN ; i++ ) {
					DeltaWeightIH[j][i] = eta * tSet[p][i] * DeltaH[j] + alpha * DeltaWeightIH[j][i];
					WeightIH[j][i] += DeltaWeightIH[j][i] ;
				}
			}
			for( int k = 0 ; k < NUMOUT ; k ++ ) {    // update weights WeightHO
				for( int j = 0 ; j < NUMHID ; j++ ) {
					DeltaWeightHO[k][j] = eta * Hidden[p][j] * DeltaO[k] + alpha * DeltaWeightHO[k][j] ;
					WeightHO[k][j] += DeltaWeightHO[k][j] ;
				}
			}
        }
        if( !(epoch%100) ) printf("\nEpoch %-5d :   Error = %f \n", epoch, Error) ;
        if( Error < 0.0004 ) {
        	printf("\nEpoch %-5d :   Error = %f \n", epoch, Error) ; break ;  // stop learning when 'near enough'
        }
    }
    freeDeltaWeights(DeltaWeightIH, DeltaWeightHO);
	freeFList( NUMPAT, fname );
	freeTSet( NUMPAT, tSet );

    for( int p = 0 ; p < NUMPAT ; p++ ) {
    	printf("\n%d\t", p) ;
        for( int k = 0 ; k < NUMOUT ; k++ ) {
            printf("%f\t%f\t", Target[p][k], Output[p][k]) ;
        }
    }
    printf("\n");
}

void printRecognized(int p, double Output[]){
	int imax = 0;

	for( int i = 1; i < NUMOUT; i++)
		if ( Output[i] > Output[imax] )
			imax = i;
	printf("El patró %d és una %c\t", p, 'A' + imax);
    for( int k = 0 ; k < NUMOUT ; k++ )
        printf("\t%f\t", Output[k]) ;
    printf("\n");

}

void runN(){
	char **rSet;
	char *fname[NUMRPAT];

	initRunFileList( fname );

	if( (rSet = loadTrainingSet(NUMRPAT,fname)) == NULL){
		printf("Error!!\n");
		exit(-1);
	}

	double Hidden[NUMHID], Output[NUMOUT];

    for( int p = 0 ; p < NUMRPAT ; p++ ) {    // repeat for all the recognition patterns
        for( int j = 0 ; j < NUMHID ; j++ ) {    // compute hidden unit activations
            double SumH = 0.0;
            for( int i = 0 ; i < NUMIN ; i++ ) SumH += rSet[p][i] * WeightIH[j][i];
            Hidden[j] = 1.0/(1.0 + exp(-SumH)) ;
        }

        for( int k = 0 ; k < NUMOUT ; k++ ) {    // compute output unit activations
            double SumO = 0.0;
            for( int j = 0 ; j < NUMHID ; j++ ) SumO += Hidden[j] * WeightHO[k][j] ;
            Output[k] = 1.0/(1.0 + exp(-SumO)) ;   // Sigmoidal Outputs
        }
        printRecognized(p, Output);
    }

	freeFList(NUMRPAT, fname);
	freeTSet( NUMRPAT, rSet );
}

int main() {
	clock_t start = clock();
	// srand(start); 		//Comentat porta a resultats deterministes (però en el cas real ha d'aparéixer)
	trainN();
	runN();

	freeWeights(WeightIH, WeightHO);
	clock_t end = clock();
	printf("\n\nGoodbye! (%f sec)\n\n", (end-start)/(1.0*CLOCKS_PER_SEC)) ;

    return 1 ;
}

/*******************************************************************************/


