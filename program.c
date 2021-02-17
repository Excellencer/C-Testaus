/* Pullonpalautusautomaatti */
/* Pääohjelma */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "tiedostonkasittely.h"
#include "apufunktiot.h"

/*********************************ALKUVALIKKO*****************************************************/

int Alkuvalikko(void) {
	int valinta, virhe_lippu;
	char buffer[MAX];

	do {
		do{
			printf("PULLONPALAUTUSAUTOMAATTI\n\n"
			"Automaatti on valmis ottamaan vastaan pullot ja tölkit.\n\n"
			"1) Aloita palautus\n"
			"0) Lopeta\n\n"
			"Valitse: ");

			virhe_lippu = 0;
		
			valinta = lueSyoteInt(buffer, &virhe_lippu);
		}while(virhe_lippu != 0);

		if ((valinta > 1) || (valinta < 0)) {
			printf("\nVäärä valinta!\n\n");
		}

	} while ((valinta != 0) && (valinta != 1));

	return valinta;
}

/*********************************PALAUTUSVALIKKO*************************************************/

Solmu *Palautusvalikko(Pullo *pEka) {
	Solmu *pAlku = NULL;
	Pullo *pLiukuri = NULL, *pTietty = NULL;
	int valinta = 0, lopetus, i = 1;

	/* Lokitiedoston päällekirjoitus*/
	Loki();
	printf("LOKI PÄÄLLEKIRJOITETTU\n");

	do {
		pLiukuri = pEka;
		printf("Syötä uusi pullo tai tölkki.\n\n");
		
		while (pLiukuri != NULL) {
			printf("%d) %s %.2fl\n",i++ , pLiukuri->sTyyppi, pLiukuri->fTilavuus);
			pLiukuri = pLiukuri->pSeuraava;		
		}

		printf("%d) Lopeta syöttö ja tulosta kuitti.\n"
			"--> ", i);
		lopetus = i;
		i = 1;
		
		/* Kokonaisluku tarkistus */
		if (scanf("%d", &valinta) != 1) {
			printf("\nVäärä valinta!\n\n");

		/* Oikean välin tarkistus */
		} else if ((valinta < 1) || (valinta > lopetus)) {
			printf("\nVäärä valinta!\n\n");

		} else if (valinta < lopetus) {
			pTietty = Tiettyalkio(pEka, valinta);
			printf("Syötetty: %s %.2fl\n", pTietty->sTyyppi, pTietty->fTilavuus);

			pAlku = Palautus(pAlku, valinta);			
			Temploki(pTietty);
		}
		clearstream();
	} while (valinta != lopetus);

	return pAlku;
}

/*********************************KUITIN*TULOSTUS*************************************************/

void Tulostus(Pullo *pEka, Solmu *pAlku) {
	Pullo *pLiukuri = pEka;
	char pvm[17] = {'\0'};
	int kpl, maara, jnro = 1;
	float kokosumma = 0, summa = 0;
	
	/* Palautuksien määrä */
	maara = Maara();
 
	printf("\n\nKuitti %s\n"
		"Palautetut pullot ja tölkit yhteensä %d kappaletta.\n\n", PVM(pvm), maara);

	while (pLiukuri != NULL) {
		
		kpl = KPL(pAlku, jnro);

		if (kpl != 0) {
			summa = (pLiukuri->fPantti * kpl);

			printf("%s %.2fl\t\tpantit %d x %.2f = %.2f€\n",
			pLiukuri->sTyyppi, pLiukuri->fTilavuus, kpl, pLiukuri->fPantti, summa);
		}

		pLiukuri = pLiukuri->pSeuraava;
		kokosumma += summa;
		summa = 0;
		jnro++;	
	}

	if (kokosumma > 0) {
		printf("\nPantit yhteensä %.2f€\n\n", kokosumma);
		Paaloki(maara, kokosumma);
	}
}


/*********************************PÄÄOHJELMA******************************************************/

int main(void) {
	Solmu *pAlku = NULL;
	Pullo *pEka = NULL;
	int valinta;

	char tiedosto[] = "tuotetiedosto.txt";
	
	pEka = Lue(tiedosto);
	
	do {
		valinta = Alkuvalikko();
		if (valinta != 0) {
			pAlku = Palautusvalikko(pEka);
			Tulostus(pEka, pAlku);
		}

	pAlku = Listanvapautus(pAlku);

	} while (valinta != 0);

	pEka = Muistinvapautus(pEka);
	

	printf("Suljetaan pullonpalautusautomaatti.\n");

	return 0;
}

/* eof */
