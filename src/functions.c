#include "functions.h"
#include "types.h"

#define N_PARETI 5

void inizializza_stanza(Stanza* stanza)
{
    // Inizializza la griglia vuota
    for (int i = 0; i < DIMENSIONE; i++)
    {
        for (int j = 0; j < DIMENSIONE; j++)
        {
            Posizione pos = { j, i };
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

    srand(time(NULL));    // Imposta il seed per la generazione pseudocasuale

    // Genera buchi neri e botole casualmente
    for (int i = 0; i < 5; i++)
    {
        Posizione pos_buco = genera_posizione(*stanza);
        Posizione pos_botola = genera_posizione(*stanza);

        Casella buco_nero = { BucoNero, 'X', false };
        Casella botola = { Botola, 'O', false };

        stanza->griglia[pos_buco.y][pos_buco.x] = buco_nero;
        stanza->griglia[pos_botola.y][pos_botola.x] = botola;
    }
}

void inizializza_robot(Stanza *stanza, Robot *robot)
{
    Posizione pos = genera_posizione(*stanza);
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
    Posizione pos_pareti[N_PARETI][2] = {
        { { 2, 4 }, { 2, 8 } },
        { { 6, 3 }, { 12, 3 } },
        { { 4, 6 }, { 7, 6 } },
        { { 8, 10 }, { 8, 14 } },
        { { 12, 7 }, { 12, 12 } }
    };

    Casella parete = { Parete, '#' };

    for (int i = 0; i < N_PARETI; i++)
    {
        Posizione inizio = pos_pareti[i][0];
        Posizione fine = pos_pareti[i][1];

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

void disegna_stanza(Stanza stanza, Robot robot)
{
    for (int i = 0; i < DIMENSIONE; i++)
    {
        for (int j = 0; j < DIMENSIONE; j++)
        {
            // Disegna il robot nella mappa
            if (robot.pos.y == i && robot.pos.x == j)
                printf("%c ", robot.visuale);
            else
                printf("%c ", stanza.griglia[i][j].visuale);
        }

        printf("\n");
    }
}

// Genera una posizione casuale nella mappa
Posizione genera_posizione(Stanza stanza)
{
    Posizione pos;

    do
    {
        pos.y = rand() % (DIMENSIONE-2) + 1;
        pos.x = rand() % (DIMENSIONE-2) + 1;
    }
    while (stanza.griglia[pos.y][pos.x].tipo != Libera);  // Verificando che la casella sia di tipo 'Libera', assicura che le posizioni generate non sovrappongano spazi gia' occupati

    return pos;
}
