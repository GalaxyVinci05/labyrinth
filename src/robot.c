#include "../include/robot.h"
#include "../include/stanza.h"
#include "../include/ostacolo.h"

void muovi_robott(Stanza *stanza, Robot *robot)
{
    Vettore2D direzione;

    stanza->griglia[robot->pos.y][robot->pos.x].calpestata = true;
    stanza->griglia[robot->pos.y][robot->pos.x].visuale = '.';

    direzione = scegli_direzione(stanza, *robot);

    robot->pos.y += direzione.y;
    robot->pos.x += direzione.x;

    switch (stanza->griglia[robot->pos.y][robot->pos.x].tipo)
    {
        case Botola:
            robot->pos = genera_posizione(stanza);
            stanza->eventi[stanza->eventi_attivi] = PosRandom;
            stanza->eventi_attivi++;
            break;
        case BucoNero:
            stanza->eventi[stanza->eventi_attivi] = GameOver;
            stanza->eventi_attivi++;
            break;
        case Uscita:
            stanza->eventi[stanza->eventi_attivi] = Vinto;
            stanza->eventi_attivi++;
            break;
        default:
            break;
    }
}

// Imposta la nuova posizione del robot all'interno della stanza.
// Input: stanza, robot
// Output: posizione del robot e caselle della stanza variate
void muovi_robot(Stanza *stanza, Robot *robot)
{
    Vettore2D direzione = scegli_direzione(stanza, *robot);
    Vettore2D pos_vecchia;
    
    if (robot->pos_precedente.y > -1)
    {
        stanza->griglia[robot->pos_precedente.y][robot->pos_precedente.x].calpestata = false;
        stanza->griglia[robot->pos_precedente.y][robot->pos_precedente.x].visuale = ' ';
    }
        
    pos_vecchia = robot->pos;

    robot->pos.y += direzione.y;
    robot->pos.x += direzione.x;

    robot->pos_precedente = pos_vecchia;
    stanza->griglia[pos_vecchia.y][pos_vecchia.x].calpestata = true;
    stanza->griglia[pos_vecchia.y][pos_vecchia.x].visuale = '.';

    switch (stanza->griglia[robot->pos.y][robot->pos.x].tipo)
    {
        case Botola:
            robot->pos = genera_posizione(stanza);
            stanza->eventi[stanza->eventi_attivi] = PosRandom;
            stanza->eventi_attivi++;
            break;
        case BucoNero:
            stanza->eventi[stanza->eventi_attivi] = GameOver;
            stanza->eventi_attivi++;
            break;
        case Uscita:
            stanza->eventi[stanza->eventi_attivi] = Vinto;
            stanza->eventi_attivi++;
            break;
        default:
            break;
    }

}

// Sceglie la direzione del robot in base alla distanza e la priorita' degli ostacoli.
// Input: stanza, robot
// Output: una tra le quattro direzioni definite nella funzione
Vettore2D scegli_direzione(Stanza *stanza, Robot robot)
{
    Vettore2D direzioni[4] = {
        { -1, 0 },  // Su'
        { 1, 0 },   // Giu'
        { 0, 1 },   // Destra
        { 0, -1 }   // Sinistra
    };

    // Sceglie una direzione casuale nel 30% dei casi
    int random = rand() % 10;
    if (random >= 7)
    {
        // Attiva l'evento "Direzione casuale"
        stanza->eventi[stanza->eventi_attivi] = DirRandom;
        stanza->eventi_attivi++;
        return genera_direzione(stanza, robot, direzioni);
    }    

    Ostacolo ostacoli[4];
    int max_distanza = 0;

    for (int i = 0; i < 4; i++)
    {
        // Salva gli ostacoli trovati nelle 4 direzioni
        ostacoli[i] = trova_ostacolo(stanza, robot, direzioni[i]);
        
        // Salva la distanza massima trovata
        if (ostacoli[i].distanza > max_distanza)
            max_distanza = ostacoli[i].distanza;
    }

    return direzioni[scegli_candidato(ostacoli, max_distanza)];
}

// Genera una direzione casuale per il robot.
// Input: stanza, robot, direzioni (definito nella funzione scegli_direzione)
// Output: una tra le quattro direzioni scelta casualmente
Vettore2D genera_direzione(Stanza *stanza, Robot robot, Vettore2D *direzioni)
{
    Vettore2D direzione;
    int n;

    do
    {
        n = rand() % 4;
        direzione = direzioni[n];
    }
    while (stanza->griglia[robot.pos.y + direzione.y][robot.pos.x + direzione.x].tipo == Parete);  // Previene che il robot sovrapponga una parete

    return direzione;
}
