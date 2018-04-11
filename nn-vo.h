/*
 * nn.h
 *
 *  Created on: 14 jul. 2016
 *      Author: ecesar
 */

#ifndef NN_H_
#define NN_H_

/* Conjunt de constants necessàries per l'execució del programa. Si feu qualsevol extensió
 * caldrà fer els canvis corresponents (per exemple, si s'incrementa el nombre de patrons d'entrada
 * cal incrementar el valor de NUMPAT).
 */

const int NUMPAT = 43; 		//Patrons en el training set
const int NUMRPAT = 17;		//Patrons per reconéixer
const long NUMIN = 7500; 	//Neurones d'entrada. 50*50*3 (Número de pixels per 3 components de color)
const int NUMHID = 83;		//Neurones en la capa oculta
const int NUMOUT = 6;		//Neurones de sortida

/*Arrays on s'emmagatzemaran els pesos calculats durant la fase d'entrenament per a ser utilitzats posteriorment
 * en la fase de reconéixament (en un cas real, aquests valors haurien de ser emmagatzemats en un arxiu després
 * de la fase d'entrenament pel seu us posterior)
 */
double *WeightIH[NUMHID];	//Pesos entre neurones d'entrada i ocultes
double *WeightHO[NUMOUT];	//Pesos entre neurones ocultes i de sortida

double rando() { return ((double)(rand()/((RAND_MAX+1)*1.0))); }

#endif /* NN_H_ */
