#ifndef Tipi_h
#define Tipi_h

// Griglia 16x16
#define DIMENSIONE 16

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
    Bassa,  // casella gia' calpestata
    Alta    // parete
} PrioritaOstacolo;

typedef enum
{
    Su,
    Giu,
    Destra,
    Sinistra
} Direzione;

typedef struct
{
    int y;
    int x;
} Vettore2D;

typedef struct
{
    TipoCasella tipo;
    char visuale;    // Carattere con cui visualizzare la casella
    bool calpestata; // Se il robot e' gia' passato per questa casella
    Vettore2D pos;
} Casella;

typedef struct
{
    Casella griglia[DIMENSIONE][DIMENSIONE];
} Stanza;

typedef struct
{
    char visuale;
    Vettore2D pos;
} Robot;

typedef struct
{
    int distanza;
    // Vettore2D direzione;
    PrioritaOstacolo priorita;
} Ostacolo;

typedef struct
{
    bool botola;
    bool game_over;
    bool vinto;
} Evento;

#endif /* Tipi_h */
