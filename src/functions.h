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
void disegna_stanza(Stanza, Robot);

// Robot
void inizializza_robot(Stanza*, Robot*);
void sposta_robot(Stanza*, Robot*, int, int);
Ostacolo trova_ostacolo(Stanza, Posizione);

// Altre
Posizione genera_posizione(Stanza);

#endif /* Funzioni_h */
