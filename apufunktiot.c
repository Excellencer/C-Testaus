#include <stdio.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include "apufunktiot.h"

/* syötepuskurin tyhjennys */
void clearstream(void) {
	while (getchar() != '\n');
}

/* päivämäärän laskeminen ja muotoilu */
char *PVM(char *ptr) {

	/* Päivämäärän tulostuksen valinta */
	int paivamaara = TRUE;

	if (paivamaara == FALSE) {
		return ptr;
	
	} else {

		time_t aika;
		char pvmbufferi[17];
		struct tm *tm_pvm;

		time(&aika);
		tm_pvm = localtime(&aika);
		strftime(pvmbufferi, 17, "%d.%m.%Y %H:%M", tm_pvm);

		strcat(ptr, pvmbufferi);

		return ptr;
	}
}

int lueSyote(char *buffer){

	/* Tarkistetaan, että syötteen lukeminen onnistui
	eikä mene sallitun pituuden yli */
	if((fgets(buffer, MAX, stdin) == NULL) || (buffer[strlen(buffer)-1] != '\n')){
		printf("\nVäärä valinta!\n\n");
		clearstream();
		return 1;
	}
	
	/* Rivinvaihdon poisto syötteestä */
	if(strtok(buffer, "\n") == NULL){
		printf("\nVäärä valinta!\n\n");
		return 1;
	}

	return 0;
}

/* syötteen lukeminen kokonaislukuna */
int lueSyoteInt(char *buffer, int *virhe_lippu){
	char *loppu_ptr = NULL;
	long luku = 0;
	errno = 0;	

	if(lueSyote(buffer) == 0){
		luku = strtol(buffer, &loppu_ptr, 10);

		/* Syötteen parsimisen virheentarkistus */
		if((loppu_ptr == buffer || errno != 0) ||
		 (luku > INT_MAX || luku < INT_MIN)){
			printf("\nVäärä valinta!\n\n");
			*virhe_lippu = 1;
		}
	}
	else{
		*virhe_lippu = 1;
	}

	return (int)luku;
}

/* eof */
