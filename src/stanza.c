#include "../include/stanza.h"

// Inizializza la stanza con tutti gli elementi del labirinto (pareti, buchi neri, botole, uscita).
// Input: stanza, pareti (struttura definita e descritta in main.c)
// Output: modifica le caselle della stanza con gli elementi del labirinto
void inizializza_stanza(Stanza *stanza, Vettore2D pareti[N_PARETI][2])
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

    // Imposta le pareti interne
    imposta_pareti(stanza, pareti);

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

// Imposta le pareti interne del labirinto.
// Input: stanza, pareti (struttura definita e descritta in main.c)
// Output: modifica le caselle della stanza con le pareti definite
void imposta_pareti(Stanza *stanza, Vettore2D pareti[N_PARETI][2])
{
    Casella parete = { Parete, '#', false };

    for (int i = 0; i < N_PARETI; i++)
    {
        Vettore2D inizio = pareti[i][0];
        Vettore2D fine = pareti[i][1];

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

// Disegna (o aggiorna) la stanza casella per casella, e il robot all'interno di essa.
// Input: stanza, robot
// Output: print della griglia del labirinto
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

// Genera una posizione casuale nella mappa.
// Input: stanza
// Output: posizione (y,x) generata casualmente
Vettore2D genera_posizione(Stanza *stanza)
{
    Vettore2D pos;

    do
    {
        pos.y = rand() % (DIMENSIONE-2) + 1;
        pos.x = rand() % (DIMENSIONE-2) + 1;
    }
    while (stanza->griglia[pos.y][pos.x].tipo != Libera);  // Verificando che la casella sia di tipo 'Libera', assicura che la posizione generata non sovrapponga caselle gia' occupate

    return pos;
}
