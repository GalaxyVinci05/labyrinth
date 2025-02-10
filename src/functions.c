#include "functions.h"
#include "types.h"

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
    // stanza->griglia[pos.y][pos.x].calpestata = true;
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

    Casella parete = { Parete, '#', false, true };

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
    Vettore2D pos_casuale;
    Casella nuova_casella;

    stanza->griglia[robot->pos.y][robot->pos.x].calpestata = true;
    stanza->griglia[robot->pos.y][robot->pos.x].visuale = '.';

    direzione = scegli_direzione(stanza, *robot);

    robot->pos.y += direzione.y;
    robot->pos.x += direzione.x;

    switch (stanza->griglia[robot->pos.y][robot->pos.x].tipo)
    {
        case Botola:
            pos_casuale = genera_posizione(stanza);
            robot->pos = pos_casuale;
            stanza->evento = PosRandom;
            break;
        case BucoNero:
            stanza->evento = GameOver;
            break;
        case Uscita:
            stanza->evento = Vinto;
            break;
        default:
            break;
    }
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
    while (casella_temp.tipo != Parete && !casella_temp.calpestata);

    if (casella_temp.tipo == Parete)
        ostacolo.priorita = Alta;
    else if (casella_temp.calpestata)
        ostacolo.priorita = Bassa;

    return ostacolo;
}

// Sceglie la direzione in base alla distanza e la priorita' degli ostacoli
Vettore2D scegli_direzione(Stanza *stanza, Robot robot)
{
    Vettore2D direzioni[4] = {
        { -1, 0 },  // Su'
        { 1, 0 },   // Giu'
        { 0, 1 },   // Destra
        { 0, -1 }   // Sinistra
    };

    int random = rand() % 10;
    if (random >= 7)
    {
        stanza->evento = DirRandom;
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

Vettore2D genera_direzione(Stanza *stanza, Robot robot, Vettore2D *direzioni)
{
    Vettore2D direzione;
    int n;

    do
    {
        n = rand() % 4;
        direzione = direzioni[n];
    }
    while (stanza->griglia[robot.pos.y + direzione.y][robot.pos.x + direzione.x].tipo == Parete);

    return direzione;
}

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
