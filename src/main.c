#include "functions.h"

int main(void)
{
    Stanza stanza;
    Robot robot;
    Evento evento;

    srand(time(NULL));    // Imposta il seed per la generazione pseudocasuale

    inizializza_stanza(&stanza);
    inizializza_robot(&stanza, &robot);
    disegna_stanza(&stanza, robot);

    int input;
    int passi = 0;
    
    do
    {
        printf("\nN. Passi: %d", passi);
        printf("\nPremi INVIO per continuare...\n");
        input = getchar();

        // Se si incontra EOF termina arbitrariamente l'esecuzione.
        if (input == EOF)
            exit(0);

        while (input != '\n');

        muovi_robot(&stanza, &robot, &evento);
        disegna_stanza(&stanza, robot);
        passi++;

        if (evento.botola)
        {
            printf("\nBotola!\n");
            evento.botola = false;
        }
    }
    while (!evento.game_over && !evento.vinto);

    if (evento.vinto)
    {
        printf("\nHai vinto!\n");
        printf("\nN. Passi: %d", passi);
    }
    else
    {
        printf("\nHai perso!\n");
        printf("\nN. Passi: %d", passi);
    }

    return 0;
}
