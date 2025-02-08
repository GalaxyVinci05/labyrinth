#include "functions.h"

int main(void)
{
    Stanza stanza;
    Robot robot;
    bool game_over = false;

    inizializza_stanza(&stanza);
    inizializza_robot(&stanza, &robot);

    int input;
    int passi = 0;
    
    do
    {
        disegna_stanza(stanza, robot);

        printf("\nN. Passi: %d", passi);
        printf("\nPremi INVIO per continuare...\n");
        input = getchar();

        // Se si incontra EOF termina arbitrariamente l'esecuzione.
        if (input == EOF)
            exit(0);

        while (input != '\n');
        passi++;
    }
    while (!game_over);

    return 0;
}
