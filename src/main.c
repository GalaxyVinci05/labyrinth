#include "../include/main.h"

int main(void)
{
    Stanza stanza;
    Robot robot = { '*', { 8, 8 }, { -1, -1 } };

    /*
    *  --- Struttura dati per creare le pareti interne ---
    *  Ogni coppia corrisponde a: { y_iniziale, x_iniziale }, { y_finale, x_finale }
    *  Ciascuna parete viene tracciata lungo il suo percorso posizione iniziale -> posizione finale
    *  E' previsto che si inserisca nella y o x finale un valore maggiore di quello nella y o x iniziale.
    */
    Vettore2D pareti[N_PARETI][2] = {
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

    srand(time(NULL));  // Imposta il seed per la generazione di numeri pseudocasuali

    inizializza_stanza(&stanza, pareti);
    disegna_stanza(&stanza, robot);

    int input, passi = 0;
    bool game_over = false, vinto = false;
    
    do
    {
        printf("\n-");

        // Gestione degli eventi
        if (stanza.eventi_attivi > 0)
        {
            for (int i = 0; i < stanza.eventi_attivi; i++)
            {
                switch (stanza.eventi[i])
                {
                    case DirRandom:
                        printf(" | Direzione casuale!");
                        break;
                    case PosRandom:
                        printf(" | Botola!");
                        break;
                    case GameOver:
                        printf("\nN. Passi: %d\nHai perso!", passi);
                        game_over = true;
                        break;
                    case Vinto:
                        printf("\nN. Passi: %d\nHai vinto!", passi);
                        vinto = true;
                        break;
                    default:
                        break;
                }

                // Reimposta l'evento
                if (stanza.eventi[i] != Nessuno)
                    stanza.eventi[i] = Nessuno;  
            }

            // Reimposta il contatore di eventi attivi
            stanza.eventi_attivi = 0;
        }

        if (!game_over && !vinto)
        {
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
    }
    while (!game_over && !vinto);

    printf("\n\n\n\n\n");
    return 0;
}
