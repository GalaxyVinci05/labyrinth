#include "../include/ostacolo.h"

// Trova l'ostacolo lungo una direzione.
// Input: stanza, robot, dir(ezione) -> una tra le quattro direzioni definite in scegli_direzione in robot.c
// Output: l'ostacolo trovato (definizione struttura in strutture.h)
Ostacolo trova_ostacolo(Stanza *stanza, Robot robot, Vettore2D dir)
{
    Ostacolo ostacolo = { 0 };
    Vettore2D pos_temp = robot.pos;
    Casella casella_temp;

    do
    {
        pos_temp.y += dir.y;
        pos_temp.x += dir.x;

        casella_temp = stanza->griglia[pos_temp.y][pos_temp.x];
        ostacolo.distanza++;
    }
    while (casella_temp.tipo != Parete && !casella_temp.calpestata);

    if (casella_temp.tipo == Parete)
        ostacolo.priorita = Alta;
    else if (casella_temp.calpestata)
        ostacolo.priorita = Bassa;

    return ostacolo;
}

// (Chiamata in robot.c) Se ci sono piu' direzioni con distanza massima da un ostacolo, sceglie una tra queste.
// Input: ostacoli (gli ostacoli trovati in tutte le direzioni), max_distanza (la distanza massima totale trovata)
// Output: indice della direzione ottimale scelta
int scegli_candidato(Ostacolo *ostacoli, int max_distanza)
{
    int candidati[4];
    int n = 0, indice_scelto = 0;

    // Salva tutti gli indici che hanno la distanza massima
    for (int i = 0; i < 4; i++)
    {
        if (ostacoli[i].distanza == max_distanza)
        {
            candidati[n] = i;
            n++;
        }
    }

    // Se e' l'unico candidato, rimane tale
    indice_scelto = candidati[0];

    // Ignorato se n = 1
    for (int i = 1; i < n; i++)
    {
        int indice_temp = candidati[i];

        // Sceglie in base alla priorita'
        if (ostacoli[indice_temp].priorita < ostacoli[indice_scelto].priorita)
            indice_scelto = indice_temp;

        // Se sono uguali, sceglie casualmente tra il candidato e l'indice salvato
        else if (ostacoli[indice_temp].priorita == ostacoli[indice_scelto].priorita)
            indice_scelto = (rand() % 2 ? indice_temp : indice_scelto);
    }

    return indice_scelto;
}
