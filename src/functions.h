#ifndef Funzioni_h
#define Funzioni_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "types.h"

void inizializza_stanza(Stanza*);
void disegna_stanza(Stanza, Robot);
void inizializza_robot(Stanza*, Robot*);
void sposta_robot(Stanza*, Robot*, int, int);
void inizializza_pareti(Stanza*);
Posizione genera_posizione(Stanza);

#endif /* Funzioni_h */
