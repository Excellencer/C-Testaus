#ifndef TIEDOSTONKASITTELY_H
#define TIEDOSTONKASITTELY_H

#include "tietorakenne.h"

#define len 30

Pullo *Lue(char *tiedosto);
void Loki(void);
void Temploki( Pullo *pTietty);
void Paaloki(int maara, float summa);
int Maara();

#endif

/* eof */
