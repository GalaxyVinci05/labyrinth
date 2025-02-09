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
    Bassa,
    Media,
    Alta  // = insuperabile
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
    bool calpestata;
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

#endif /* Tipi_h */
