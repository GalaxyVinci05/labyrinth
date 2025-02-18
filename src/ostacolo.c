#include "../include/ostacolo.h"

// Trova l'ostacolo lungo una direzione.
// Input: stanza, robot, dir(ezione) -> una tra le quattro direzioni definite in "scegli_direzione" in robot.c
// Output: l'ostacolo trovato (definizione struttura in strutture.h)
Ostacolo trova_ostacolo(Stanza *stanza, Robot robot, Vettore2D dir)
{
    Ostacolo ostacolo = { 0 };        // Inizializza la distanza a 0
    Vettore2D pos_temp = robot.pos;   // Variabile di controllo per verificare la distanza dell'ostacolo
    Casella casella_temp;             // Variabile di controllo per verificare il tipo di casella su cui si fa il controllo con "pos_temp"
    bool casella_calpestata = false;  // Variabile di controllo per verificare se e' stata trovata una casella calpestata
    bool esci = false;


    do
    {
        pos_temp.y += dir.y;
        pos_temp.x += dir.x;

        casella_temp = stanza->griglia[pos_temp.y][pos_temp.x];

        // Incrementa la distanza dall'ostacolo se non e' stata trovata una casella calpestata
        if (!casella_calpestata)
            ostacolo.distanza++;

        // Se viene trovata una casella calpestata, smette *soltanto* di incrementare la distanza, poiche' abbiamo gia' trovato l'ostacolo
        if (casella_temp.calpestata && !casella_calpestata)
        {
            casella_calpestata = true;
        }

        // Se e' stata trovata una parete, interrompe il ciclo e mantiene la distanza salvata
        if (casella_temp.tipo == Parete)
        {
            // Se e' stata trovata una casella calpestata in precedenza, imposta la priorita' bassa, poiche' le caselle calpestate possono essere ripercorse nel caso in cui non ci siano direzioni preferibili
            // Se invece la parete e' il primo ostacolo trovato, imposta la priorita' alta, poiche' le pareti sono ostacoli inoltrepassabili
            ostacolo.priorita = casella_calpestata ? Bassa : Alta;
            esci = true;
        }
        // Se invece e' stata trovata l'uscita, imposta la distanza dell'"ostacolo" in modo tale che la direzione in cui si trova l'uscita sia sempre preferita, e poi interrompe il ciclo
        else if (casella_temp.tipo == Uscita)
        {
            ostacolo.distanza = DIMENSIONE;
            esci = true;
        }
    }
    while (!esci);

    return ostacolo;
}

// (Chiamata in robot.c) Se ci sono piu' direzioni con distanza massima rispetto ad un ostacolo, sceglie una tra queste.
// Input: ostacoli (gli ostacoli trovati in tutte le direzioni), max_distanza (la distanza massima totale trovata)
// Output: indice della direzione ottimale scelta
int scegli_candidato(Ostacolo *ostacoli, int max_distanza)
{
    int candidati[4];
    int n = 0, indice_scelto = 0;

    // Salva tutti gli indici che hanno la distanza massima, ed incrementa il contatore di direzioni equidistanti
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

        // Se hanno la stessa priorita', sceglie casualmente tra il candidato e l'indice salvato
        else if (ostacoli[indice_temp].priorita == ostacoli[indice_scelto].priorita)
            indice_scelto = rand() % 2 ? indice_temp : indice_scelto;
    }

    return indice_scelto;
}
