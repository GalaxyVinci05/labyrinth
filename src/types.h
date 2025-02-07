#ifndef Tipi_h
#define Tipi_h

#define DIMENSIONE 16

typedef enum
{
    Libera,
    Parete,
    BucoNero,
    Botola,
    Uscita
} TipoCasella;

typedef struct
{
    TipoCasella tipo;
    // Carattere con cui visualizzare la casella
    char visuale;
    bool calpestata;
} Casella;

typedef struct
{
    Casella griglia[DIMENSIONE][DIMENSIONE];
} Stanza;

#endif /* Tipi_h */
