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
} Posizione;

typedef struct
{
    TipoCasella tipo;
    char visuale;    // Carattere con cui visualizzare la casella
    bool calpestata;
    Posizione pos;
} Casella;

typedef struct
{
    Casella griglia[DIMENSIONE][DIMENSIONE];
} Stanza;

typedef struct
{
    char visuale;
    Posizione pos;
} Robot;

typedef struct
{
    int distanza;
    Direzione direzione;
    PrioritaOstacolo priorita;
} Ostacolo;

#endif /* Tipi_h */
