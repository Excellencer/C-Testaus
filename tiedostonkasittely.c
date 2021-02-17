#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#include "tiedostonkasittely.h"
#include "apufunktiot.h"

/*********************************LUKU*****************************************************/

Pullo *Lue(char *tiedosto) {
	FILE* lukutiedosto;
	Pullo *pEka = NULL;
	char rivi[len];
	
	if ((lukutiedosto = fopen(tiedosto, "r")) == NULL) {
		perror("Tiedoston lukeminen epäonnistui.\n");
		exit(1);

	} else {
    
		/*Muistin varaus*/
		while(fgets(rivi, 50, lukutiedosto) != NULL) { 
			if (strcmp(rivi, "\n") != 0) {
				pEka = Lisays(pEka, rivi);

			} else {
				continue;

			}
		}
	}

	fclose(lukutiedosto);
	return pEka;

}

/*********************************TILAPÄISLOKIN*PÄÄLLEKIRJOITUS***********************************/
void Loki(void) {
	FILE* temptiedosto;
	if ((temptiedosto = fopen("tilapaistiedosto.txt", "w")) != NULL) {
		fprintf(temptiedosto, "Tilapäinen lokitiedosto\n\n");

	} else {
		perror("Tiedoston avaaminen epäonnistui.\n");
		exit(1);
	}
	
	fclose(temptiedosto);
}

/*********************************TILAPÄISLOKI****************************************************/

void Temploki(Pullo *pTietty) {
	FILE* temptiedosto;
	char pvm[17] = {'\0'};

	if ((temptiedosto = fopen("tilapaistiedosto.txt", "a")) != NULL) {
		fprintf(temptiedosto, "%s:%s-%.2fl:%.2f€.\n", 
		PVM(pvm), pTietty->sTyyppi, pTietty->fTilavuus, pTietty->fPantti);

	} else {
		perror("Tiedoston avaaminen epäonnistui.\n");
		exit(1);
	}
	
	fclose(temptiedosto);
}

/*********************************PÄÄLOKI*********************************************************/

void Paaloki(int maara, float summa) {
	FILE* lokitiedosto;
	char pvm[17] = {'\0'};

	if ((lokitiedosto = fopen("lokitiedosto.txt", "a")) != NULL) {
		fprintf(lokitiedosto, "%s - Palautukset %dkpl. Pantit %.2f€.\n",
		PVM(pvm), maara, summa);

	} else {
		perror("Tiedoston avaaminen epäonnistui.\n");
		exit(1);
	}
	
	fclose(lokitiedosto);
}

/*********************************PALAUTUSMÄÄRÄ***************************************************/

int Maara() {
	FILE* tiedosto;
	/* Ei oteta otsikkoa ja tyhjää riviä huomioon */
	int maara = -1;
	char rivi[50];
	
	if ((tiedosto = fopen("tilapaistiedosto.txt", "r")) != NULL) {

		while(fgets(rivi, sizeof(rivi), tiedosto) != NULL) {
		maara++;

		}

	} else {
		perror("Tiedoston lukeminen epäonnistui.\n");
		exit(1);
		
	}

	fclose(tiedosto);
	return maara;
}

/* eof */
