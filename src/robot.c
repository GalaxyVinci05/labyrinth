#include "../include/robot.h"
#include "../include/stanza.h"
#include "../include/ostacolo.h"

// Imposta la nuova posizione del robot all'interno della stanza.
// Input: stanza, robot
// Output: posizione del robot e caselle della stanza variate
void muovi_robot(Stanza *stanza, Robot *robot)
{
    Vettore2D direzione;

    // Imposta la casella corrente come calpestata
    stanza->griglia[robot->pos.y][robot->pos.x].calpestata = true;
    stanza->griglia[robot->pos.y][robot->pos.x].visuale = '.';

    direzione = scegli_direzione(stanza, *robot);

    // Somma alla posizione corrente del robot il vettore direzione
    robot->pos.y += direzione.y;
    robot->pos.x += direzione.x;

    switch (stanza->griglia[robot->pos.y][robot->pos.x].tipo)
    {
        case Botola:
            robot->pos = genera_posizione(stanza);              // La posizione del robot assume un valore casuale
            stanza->eventi[stanza->eventi_attivi] = PosRandom;  // Aggiunge l'evento
            stanza->eventi_attivi++;                            // Incrementa il contatore di eventi
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

// Sceglie la direzione del robot in base alla distanza e la priorita' degli ostacoli, oppure casualmente.
// Input: stanza, robot
// Output: una tra le quattro direzioni definite nella funzione
Vettore2D scegli_direzione(Stanza *stanza, Robot robot)
{
    // Array di vettori utilizzati per definire una "direzione" con 'y' e 'x': queste ultime verranno sommate alla 'y' e 'x' del robot
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
        stanza->eventi[stanza->eventi_attivi] = DirRandom;  // Aggiunge l'evento "Direzione casuale"
        stanza->eventi_attivi++;
        return genera_direzione(stanza, robot, direzioni);  // la funzione "scegli_direzione" restituira' un vettore "direzione" casuale
    }

    Ostacolo ostacoli[4];  // Contenitore per gli ostacoli trovati nelle 4 direzioni, con distanza associata
    int max_distanza = 0;  // Distanza massima trovata

    for (int i = 0; i < 4; i++)
    {
        ostacoli[i] = trova_ostacolo(stanza, robot, direzioni[i]);  // Individua l'ostacolo, la cui distanza e' il numero di caselle libere dal robot fino ad esso

        if (ostacoli[i].distanza > max_distanza)
            max_distanza = ostacoli[i].distanza;
    }

    return direzioni[scegli_candidato(ostacoli, max_distanza)];  // Se ci sono piu' ostacoli con distanza = max_distanza, la funzione "scegli_candidato" scegliera' una singola direzione
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
