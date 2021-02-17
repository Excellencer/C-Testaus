#ifndef TIETORAKENNE_H /* include guard */
#define TIETORAKENNE_H

/* PULLO TIETUE */
struct Alkio {
	char *sTyyppi;
	float fTilavuus;
	float fPantti;
	struct Alkio *pSeuraava;
};

/* PALAUTUS TIETUE */
struct Node {
	int iNro;
	struct Node *pSeuraava;
};

typedef struct Alkio Pullo;
typedef struct Node Solmu;

Pullo *Lisays(Pullo *pEka, char rivi[255]);
Solmu *Palautus(Solmu *pAlku, int nro);
int KPL(Solmu* pAlku, int nro);
Pullo *Tiettyalkio(Pullo *pLiukuri, int nro);
Pullo *Muistinvapautus(Pullo *pEka);
Solmu *Listanvapautus(Solmu *pAlku);

#endif 

/* eof */
