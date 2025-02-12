#ifndef Strutture_h
#define Strutture_h

// Strutture_h -> Definizioni di tutte le strutture dati utilizzate nel programma

#define DIMENSIONE 16  // Griglia 16x16
#define N_PARETI 4
#define N_EVENTI 5

typedef enum
{
    Libera,
    Parete,
    BucoNero,
    Botola,
    Uscita
} TipoCasella;

typedef enum
{
    Bassa,  // Casella gia' calpestata
    Alta    // Parete
} PrioritaOstacolo;

typedef enum
{
    Nessuno,
    DirRandom,  // Il robot ha scelto una direzione casuale
    PosRandom,  // Il robot e' entrato in una botola
    GameOver,   // Il robot e' entrato in un buco nero
    Vinto       // Il robot e' uscito dall'uscita in basso a sinistra della stanza
} Evento;

typedef struct
{
    int y;
    int x;
} Vettore2D;

typedef struct
{
    TipoCasella tipo;
    char visuale;    // Carattere con cui visualizzare la casella nell'output del programma
    bool calpestata;
    Vettore2D pos;
} Casella;

typedef struct
{
    Casella griglia[DIMENSIONE][DIMENSIONE];
    Evento eventi[N_EVENTI];
    int eventi_attivi;
} Stanza;

typedef struct
{
    char visuale;
    Vettore2D pos;
    Vettore2D pos_precedente;
} Robot;

typedef struct
{
    int distanza;
    PrioritaOstacolo priorita;
} Ostacolo;

#endif /* Tipi_h */
