#ifndef Strutture_h
#define Strutture_h

// Strutture_h -> Definizioni di tutte le strutture dati e le costanti utilizzate nel programma

#define DIMENSIONE 16  // Griglia 16x16
#define N_PARETI 4     // Numero di pareti interne
#define N_EVENTI 5     // Numero di eventi possibili

typedef enum
{
    Libera,    // Visualizzato con ' '
    Parete,    // Visualizzato con '#'
    BucoNero,  // Visualizzato con 'X'
    Botola,    // Visualizzato con 'O'
    Uscita     // Visualizzato con ' '
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
} Vettore2D;  // Generico vettore per definire delle coordinate 'y' e 'x' nella griglia del labirinto

typedef struct
{
    TipoCasella tipo;
    char visuale;     // Carattere con cui visualizzare la casella nell'output del programma, in base al suo tipo
    bool calpestata;  // Visualizzato nel labirinto come '.'
    Vettore2D pos;    // Posizione della casella nella griglia
} Casella;

typedef struct
{
    Casella griglia[DIMENSIONE][DIMENSIONE];
    Evento eventi[N_EVENTI];  // Array contenente gli eventi attivi
    int eventi_attivi;        // Contatore di eventi attivi
} Stanza;

typedef struct
{
    char visuale;  // Visualizzato con '*'
    Vettore2D pos;
} Robot;

typedef struct
{
    int distanza;
    PrioritaOstacolo priorita;
} Ostacolo;

#endif /* Strutture_h */
