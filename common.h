double Target[NUMPAT][NUMOUT] = {{1,0,0,0,0,0},{1,0,0,0,0,0},{1,0,0,0,0,0},{1,0,0,0,0,0},{1,0,0,0,0,0},{1,0,0,0,0,0},{1,0,0,0,0,0},{1,0,0,0,0,0}, //A
								 {0,1,0,0,0,0},{0,1,0,0,0,0},{0,1,0,0,0,0},{0,1,0,0,0,0},{0,1,0,0,0,0},{0,1,0,0,0,0},{0,1,0,0,0,0}, //B
								 {0,0,1,0,0,0},{0,0,1,0,0,0},{0,0,1,0,0,0},{0,0,1,0,0,0},{0,0,1,0,0,0},{0,0,1,0,0,0},{0,0,1,0,0,0}, //C
								 {0,0,0,1,0,0},{0,0,0,1,0,0},{0,0,0,1,0,0},{0,0,0,1,0,0},{0,0,0,1,0,0},{0,0,0,1,0,0},{0,0,0,1,0,0}, //D
								 {0,0,0,0,1,0},{0,0,0,0,1,0},{0,0,0,0,1,0},{0,0,0,0,1,0},{0,0,0,0,1,0},{0,0,0,0,1,0},{0,0,0,0,1,0}, //E
								 {0,0,0,0,0,1},{0,0,0,0,0,1},{0,0,0,0,0,1},{0,0,0,0,0,1},{0,0,0,0,0,1},{0,0,0,0,0,1},{0,0,0,0,0,1}  //F
								};


/* Inicialització de la llista de patrons a reconéixer per la xarxa, si voleu extendre el conjunt caldrà
 * afegir les línies corresponents (i canviar la constant NUMRPAT a nn.h)
 */
void initRunFileList(char *flist[]){
	for (int i = 0; i < NUMRPAT; i++) flist[i] = (char *)malloc(25);

	strcpy(flist[0], "./rset/A3-r.ppm");
	strcpy(flist[1], "./rset/A4-r.ppm");
	strcpy(flist[2], "./rset/B3-r.ppm");
	strcpy(flist[3], "./rset/B4-r.ppm");
	strcpy(flist[4], "./rset/C2-r.ppm");
	strcpy(flist[5], "./rset/D3-r.ppm");
	strcpy(flist[6], "./rset/D4-r.ppm");
	strcpy(flist[7], "./rset/E3-r.ppm");
	strcpy(flist[8], "./rset/E4-r.ppm");
	strcpy(flist[9], "./rset/F3-r.ppm");
	strcpy(flist[10], "./rset/F4-r.ppm");
	//Demanem patrons d'entrament per tal de demostrar que els reconeix.
	strcpy(flist[11], "./tset/A1-t.ppm");
	strcpy(flist[12], "./tset/B2-t.ppm");
	strcpy(flist[13], "./tset/C1-t.ppm");
	strcpy(flist[14], "./tset/D2-t.ppm");
	strcpy(flist[15], "./tset/E1-t.ppm");
	strcpy(flist[16], "./tset/F2-t.ppm");
}

/* Inicialització de la llista de patrons a llegir per entrenar la xarxa, si voleu extendre el conjunt caldrà
 * afegir les línies corresponents (i canviar la constant NUMPAT a nn.h)
 */
void initFileList(char *flist[]){
	for (int i = 0; i < NUMPAT; i++) flist[i] = (char *)malloc(25);

	strcpy(flist[0], "./tset/A1-t.ppm");
	strcpy(flist[1], "./tset/A2-t.ppm");
	strcpy(flist[2], "./tset/A3-t.ppm");
	strcpy(flist[3], "./tset/A4-t.ppm");
	strcpy(flist[4], "./tset/A5-t.ppm");
	strcpy(flist[5], "./tset/A6-t.ppm");
	strcpy(flist[6], "./tset/A7-t.ppm");
	strcpy(flist[7], "./tset/A8-t.ppm");
	strcpy(flist[8], "./tset/B1-t.ppm");
	strcpy(flist[9], "./tset/B2-t.ppm");
	strcpy(flist[10], "./tset/B3-t.ppm");
	strcpy(flist[11], "./tset/B4-t.ppm");
	strcpy(flist[12], "./tset/B5-t.ppm");
	strcpy(flist[13], "./tset/B6-t.ppm");
	strcpy(flist[14], "./tset/B7-t.ppm");
	strcpy(flist[15], "./tset/C1-t.ppm");
	strcpy(flist[16], "./tset/C2-t.ppm");
	strcpy(flist[17], "./tset/C3-t.ppm");
	strcpy(flist[18], "./tset/C4-t.ppm");
	strcpy(flist[19], "./tset/C5-t.ppm");
	strcpy(flist[20], "./tset/C6-t.ppm");
	strcpy(flist[21], "./tset/C7-t.ppm");
	strcpy(flist[22], "./tset/D1-t.ppm");
	strcpy(flist[23], "./tset/D2-t.ppm");
	strcpy(flist[24], "./tset/D3-t.ppm");
	strcpy(flist[25], "./tset/D4-t.ppm");
	strcpy(flist[26], "./tset/D5-t.ppm");
	strcpy(flist[27], "./tset/D6-t.ppm");
	strcpy(flist[28], "./tset/D7-t.ppm");
	strcpy(flist[29], "./tset/E1-t.ppm");
	strcpy(flist[30], "./tset/E2-t.ppm");
	strcpy(flist[31], "./tset/E3-t.ppm");
	strcpy(flist[32], "./tset/E4-t.ppm");
	strcpy(flist[33], "./tset/E5-t.ppm");
	strcpy(flist[34], "./tset/E6-t.ppm");
	strcpy(flist[35], "./tset/E7-t.ppm");
	strcpy(flist[36], "./tset/F1-t.ppm");
	strcpy(flist[37], "./tset/F2-t.ppm");
	strcpy(flist[38], "./tset/F3-t.ppm");
	strcpy(flist[39], "./tset/F4-t.ppm");
	strcpy(flist[40], "./tset/F5-t.ppm");
	strcpy(flist[41], "./tset/F6-t.ppm");
	strcpy(flist[42], "./tset/F7-t.ppm");
}

