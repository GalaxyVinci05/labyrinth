#ifndef Robot_h
#define Robot_h

// Robot_h -> Dichiarazioni delle funzioni inerenti al movimento del robot

#include <stdio.h>
#include <stdbool.h>
#include "strutture.h"

void muovi_robot(Stanza*, Robot*);
Vettore2D scegli_direzione(Stanza*, Robot);
Vettore2D genera_direzione(Stanza*, Robot, Vettore2D*);

#endif /* Robot_h */
