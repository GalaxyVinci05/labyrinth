#ifndef Stanza_h
#define Stanza_h

// Stanza_h -> Prototipi delle funzioni inerenti all'inizializzazione e l'aggiornamento della stanza

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "strutture.h"

void inizializza_stanza(Stanza*, Vettore2D[N_PARETI][2]);
void imposta_pareti(Stanza*, Vettore2D[N_PARETI][2]);
void disegna_stanza(Stanza*, Robot);
Vettore2D genera_posizione(Stanza*);

#endif /* Stanza_h */
