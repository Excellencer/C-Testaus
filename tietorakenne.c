#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tietorakenne.h"

/*********************************LISÄYS**********************************************************/

Pullo *Lisays(Pullo *pEka, char rivi[255]) {
	Pullo *pLiukuri, *pUusin;
	char *token = NULL;

    /* Muistin varaus */
	if ((pUusin = (Pullo*)malloc(sizeof(Pullo))) == NULL) {
		perror("Muistin varaaminen epäonnistui.");
		exit(1);
	}
	
	/* Tuotetiedoston rivin parsiminen */
	token = strtok(rivi, " ");
	if((pUusin->sTyyppi = malloc(strlen(token)+1)) == NULL) {
		perror("Muistin varaaminen epäonnistui.");
		exit(1);
	}

	strcpy(pUusin->sTyyppi, token);
    pUusin->fTilavuus = atof(strtok(NULL, " "));
    pUusin->fPantti = atof(strtok(NULL, " "));

	pUusin->pSeuraava = NULL;
    
	if (pEka == NULL) {
		pEka = pUusin;
        
	} else {

		pLiukuri = pEka;
		while (pLiukuri->pSeuraava != NULL) {
			pLiukuri = pLiukuri->pSeuraava;
		}
 		pLiukuri->pSeuraava = pUusin;
	}
    
	return pEka;
}

/*********************************PALAUTUS********************************************************/

Solmu *Palautus(Solmu *pAlku, int nro) {
	Solmu *pLiukuri, *pUusin;

	/* Muistin varaus */
	if ((pUusin = (Solmu*)malloc(sizeof(Solmu))) == NULL) {
		perror("Muistin varaaminen epäonnistui.");
		exit(1);
	}
		
	pUusin->iNro = nro;
	pUusin->pSeuraava = NULL;
 
	if (pAlku == NULL) {
		pAlku = pUusin;
        
	} else {

		pLiukuri = pAlku;
		while (pLiukuri->pSeuraava != NULL) {
			pLiukuri = pLiukuri->pSeuraava;
		}
 		pLiukuri->pSeuraava = pUusin;
	}
    
	return pAlku;
}

/****************************TIETYN*ALKION*PALAUTUS***********************************************/

Pullo *Tiettyalkio(Pullo *pLiukuri, int nro) {
	int i = 1;

	while (pLiukuri != NULL) {
		if(i == nro) {
			return pLiukuri;
		}		
		pLiukuri = pLiukuri->pSeuraava;
		i++;
	}

	/* Mikäli alkion nro jota ei jostain syystä ole listalla. */
	return pLiukuri;
}

/****************************KAPPALEMÄÄRÄ***********************************************************/

int KPL(Solmu *pAlku, int nro) {
	int kpl = 0;

	while (pAlku != NULL) {
		if(pAlku->iNro == nro) {
			kpl++;
		}		
		pAlku = pAlku->pSeuraava;
	}

	return kpl;
}

/****************************MUISTINVAPAUTUS******************************************************/

Pullo *Muistinvapautus(Pullo *pEka) {
	Pullo *del = pEka;
	while (del != NULL) {
		pEka = del->pSeuraava;
		free(del);
		del = pEka;
	}

	return pEka;
}

/****************************LISTANVAPAUTUS*******************************************************/

Solmu *Listanvapautus(Solmu *pAlku) {
	Solmu *poisto = pAlku;
	while (poisto != NULL) {
		pAlku = poisto->pSeuraava;
		free(poisto);
		poisto = pAlku;
	}

	return pAlku;
}

/* eof */
