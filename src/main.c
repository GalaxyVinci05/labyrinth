#include "functions.h"

int main(void)
{
    Stanza stanza;
    Robot robot;

    srand(time(NULL));    // Imposta il seed per la generazione pseudocasuale

    inizializza_stanza(&stanza);
    inizializza_robot(&stanza, &robot);
    disegna_stanza(&stanza, robot);

    int input;
    int passi = 0;
    
    do
    {
        switch (stanza.evento)
        {
            case DirRandom:
                printf("\nDirezione casuale!");
                break;
            case PosRandom:
                printf("\nBotola!");
                break;
            default:
                printf("\n-");
                break;
        }

        if (stanza.evento != Nessuno)
            stanza.evento = Nessuno;

        printf("\nN. Passi: %d", passi);
        printf("\nPremi INVIO per continuare...\n");
        printf("\n\n\n\n\n");
        input = getchar();

        // Se si incontra EOF termina arbitrariamente l'esecuzione.
        if (input == EOF)
            exit(0);

        while (input != '\n');

        muovi_robot(&stanza, &robot);
        disegna_stanza(&stanza, robot);
        passi++;
    }
    while (stanza.evento != GameOver && stanza.evento != Vinto);

    if (stanza.evento == Vinto)
        printf("\n-\nN. Passi: %d\nHai vinto!", passi);
    else
        printf("\n-\nN. Passi: %d\nHai perso!", passi);

    printf("\n\n\n\n\n");
    return 0;
}
