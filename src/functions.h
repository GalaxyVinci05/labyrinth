#ifndef Funzioni_h
#define Funzioni_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "types.h"

// Stanza
void inizializza_stanza(Stanza*);
void inizializza_pareti(Stanza*);
void disegna_stanza(Stanza*, Robot);

// Robot
void inizializza_robot(Stanza*, Robot*);
void muovi_robot(Stanza*, Robot*);
Ostacolo trova_ostacolo(Stanza*, Robot, Vettore2D);
Vettore2D scegli_direzione(Stanza*, Robot);
Vettore2D genera_direzione(Stanza*, Robot, Vettore2D*);
int scegli_candidato(Ostacolo*, int);

// Altre
Vettore2D genera_posizione(Stanza*);

#endif /* Funzioni_h */
