#ifndef Ostacolo_h
#define Ostacolo_h

// Ostacolo_h -> Prototipi delle funzioni inerenti alla rilevazione degli ostacoli all'interno del labirinto

#include <stdlib.h>
#include <stdbool.h>
#include "strutture.h"

Ostacolo trova_ostacolo(Stanza*, Robot, Vettore2D);
int scegli_candidato(Ostacolo*, int);

#endif /* Ostacolo_h */
