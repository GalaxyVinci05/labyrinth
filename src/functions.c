#include "functions.h"
#include "types.h"
#include <stdlib.h>

#define N_PARETI 4

void inizializza_stanza(Stanza* stanza)
{
    // Inizializza la griglia vuota
    for (int i = 0; i < DIMENSIONE; i++)
    {
        for (int j = 0; j < DIMENSIONE; j++)
        {
            Vettore2D pos = { j, i };
            Casella vuoto = { Libera, ' ', false, pos };

            stanza->griglia[i][j] = vuoto;
        }
    }

    // Imposta le pareti esterne
    for (int i = 0; i < DIMENSIONE; i++)
    {
        Casella parete = { Parete, '#', false };

        stanza->griglia[i][0] = parete;
        stanza->griglia[i][DIMENSIONE-1] = parete;
        stanza->griglia[0][i] = parete;
        stanza->griglia[DIMENSIONE-1][i] = parete;
    }

    // Inizializza le pareti interne
    inizializza_pareti(stanza);

    // Imposta l'uscita
    Casella uscita = { Uscita, 'E', false };
    stanza->griglia[DIMENSIONE-2][0] = uscita;

    // Genera buchi neri e botole casualmente
    for (int i = 0; i < 5; i++)
    {
        Vettore2D pos_buco = genera_posizione(stanza);
        Vettore2D pos_botola = genera_posizione(stanza);

        Casella buco_nero = { BucoNero, 'X', false };
        Casella botola = { Botola, 'O', false };

        stanza->griglia[pos_buco.y][pos_buco.x] = buco_nero;
        stanza->griglia[pos_botola.y][pos_botola.x] = botola;
    }
}

void inizializza_robot(Stanza *stanza, Robot *robot)
{
    Vettore2D pos = genera_posizione(stanza);
    Robot nuovo_robot = { '*', pos };

    *robot = nuovo_robot;
    stanza->griglia[pos.y][pos.x].calpestata = true;
}

void inizializza_pareti(Stanza *stanza)
{
    /*
    *  Struttura dati per inizializzare le pareti interne:
    *  Ogni coppia corrisponde a [posizione iniziale, posizione finale]
    *  { y_iniziale, x_iniziale }, { y_finale, x_finale }
    *  Ciascuna parete viene tracciata lungo il suo percorso pos iniziale -> pos finale
    *  E' previsto che si inserisca nella y o x finale un valore maggiore di quello nella y o x iniziale.
    *  Sono previste soltanto pareti orizzontali o verticali.
    */
    Vettore2D pos_pareti[N_PARETI][2] = {
        //{ { 2, 4 }, { 2, 8 } },
        //{ { 6, 3 }, { 12, 3 } },
        //{ { 4, 6 }, { 7, 6 } },
        //{ { 8, 10 }, { 8, 14 } },
        //{ { 12, 7 }, { 12, 12 } }
        { { 2, 3 }, { 9, 3 } },
        { { 8, 7 }, { 14, 7 } },
        { { 3, 7 }, { 3, 14 } },
        { { 10, 11 }, { 10, 13 } }
    };

    Casella parete = { Parete, '#' };

    for (int i = 0; i < N_PARETI; i++)
    {
        Vettore2D inizio = pos_pareti[i][0];
        Vettore2D fine = pos_pareti[i][1];

        // Parete orizzontale
        if (inizio.y == fine.y)
        {
            for (int x = inizio.x; x <= fine.x; x++)
                stanza->griglia[inizio.y][x] = parete;
        }
        // Parete verticale
        else if (inizio.x == fine.x)
        {
            for (int y = inizio.y; y <= fine.y; y++)
                stanza->griglia[y][inizio.x] = parete;
        }
        // Nessuna delle due: ignora
        else
            continue;
    }
}

void disegna_stanza(Stanza *stanza, Robot robot)
{
    for (int i = 0; i < DIMENSIONE; i++)
    {
        for (int j = 0; j < DIMENSIONE; j++)
        {
            // Disegna il robot nella mappa
            if (robot.pos.y == i && robot.pos.x == j)
                printf("%c ", robot.visuale);
            else
                printf("%c ", stanza->griglia[i][j].visuale);
        }

        printf("\n");
    }
}

void muovi_robot(Stanza *stanza, Robot *robot)
{
    Vettore2D direzione;
    direzione = scegli_direzione(stanza, *robot);

    robot->pos.y += direzione.y;
    robot->pos.x += direzione.x;

    stanza->griglia[robot->pos.y][robot->pos.x].calpestata = true;
}

// Genera una posizione casuale nella mappa
Vettore2D genera_posizione(Stanza *stanza)
{
    Vettore2D pos;

    do
    {
        pos.y = rand() % (DIMENSIONE-2) + 1;
        pos.x = rand() % (DIMENSIONE-2) + 1;
    }
    while (stanza->griglia[pos.y][pos.x].tipo != Libera);  // Verificando che la casella sia di tipo 'Libera', assicura che le posizioni generate non sovrappongano spazi gia' occupati

    return pos;
}

// Dir(ezione): utilizza Vettore2D come direzione ( {0,1} {0,-1} {1,0} {-1,0} )
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
    while (casella_temp.tipo == Libera && !casella_temp.calpestata);

    if (casella_temp.tipo == Parete)
        ostacolo.priorita = Alta;
    else if (casella_temp.tipo == BucoNero)
        ostacolo.priorita = Media;
    else if (casella_temp.calpestata)
        ostacolo.priorita = Bassa;

    return ostacolo;
}

// Sceglie la direzione in base alla distanza e la priorita' degli ostacoli
Vettore2D scegli_ddirezione(Stanza *stanza, Robot robot)
{
    Vettore2D direzioni[4] = {
        { -1, 0 },  // Su'
        { 1, 0 },   // Giu'
        { 0, 1 },   // Destra
        { 0, -1 }   // Sinistra
    };

    Ostacolo ostacoli[4];
    int indice_dir = 0;

    for (int i = 0; i < 4; i++)
    {
        ostacoli[i] = trova_ostacolo(stanza, robot, direzioni[i]);
        
        if (ostacoli[i].distanza > ostacoli[indice_dir].distanza)
            indice_dir = i;
        else if (ostacoli[i].distanza == ostacoli[indice_dir].distanza)
        {
            if (ostacoli[i].priorita < ostacoli[indice_dir].priorita)
                indice_dir = i;
            else
                indice_dir = rand() % 4;
        }
    }

    // TODO: add candidates and choose random iterative between them

    return direzioni[indice_dir];
}

// TODO: remove (generated)
Vettore2D scegli_direzione(Stanza *stanza, Robot robot)
{
    Vettore2D direzioni[4] = {
        { -1, 0 },  // Su
        { 1, 0 },   // Giù
        { 0, 1 },   // Destra
        { 0, -1 }   // Sinistra
    };

    Ostacolo ostacoli[4];
    // Ottieni gli ostacoli per ogni direzione
    for (int i = 0; i < 4; i++)
    {
        ostacoli[i] = trova_ostacolo(stanza, robot, direzioni[i]);
    }
    
    // Trova il massimo valore di distanza
    int max_distanza = -1;
    for (int i = 0; i < 4; i++)
    {
        if (ostacoli[i].distanza > max_distanza)
            max_distanza = ostacoli[i].distanza;
    }
    
    // Raccogli gli indici che hanno la distanza massima
    int candidati[4];
    int num_candidati = 0;
    for (int i = 0; i < 4; i++)
    {
        if (ostacoli[i].distanza == max_distanza)
        {
            candidati[num_candidati] = i;
            num_candidati++;
        }
    }
    
    // Se c'è un solo candidato, lo scegliamo
    int indice_scelto = candidati[0];
    
    // Se ce ne sono più di uno, scegliamo quello con la priorità migliore.
    // Supponendo che un valore minore di Priorita sia migliore (ad esempio, Bassa = 0 < Media = 1 < Alta = 2)
    for (int i = 1; i < num_candidati; i++)
    {
        int idx = candidati[i];
        if (ostacoli[idx].priorita < ostacoli[indice_scelto].priorita)
        {
            indice_scelto = idx;
        }
        // Se la priorità è anch'essa uguale, possiamo decidere casualmente
        else if (ostacoli[idx].priorita == ostacoli[indice_scelto].priorita)
        {
            if (rand() % 2)
            {
                indice_scelto = idx;
            }
        }
    }

    int random = rand() % 10;
    if (random > 7)
    {
        int n = rand() % 4;
        return direzioni[n];
    }
    
    return direzioni[indice_scelto];
}

