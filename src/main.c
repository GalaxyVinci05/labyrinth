/*
*  --- Labirinto ---
*
*  Il seguente programma consiste in un algoritmo per il cammino di un robot in un labirinto.
*  Il labirinto e' composto dai seguenti elementi:
*  - Pareti esterne ed interne
*  - 5 botole (posizionate casualmente)
*  - 5 buchi neri (posizionati casualmente)
*  - 1 uscita
*
*  Il robot ad ogni passo puo' scegliere una direzione da seguire, secondo i seguenti criteri:
*  - Si preferisce la direzione con la distanza maggiore dalla parete rispetto al robot (nel caso di piu' direzioni con distanza massima, viene scelta casualmente una tra queste)
*  - Si prende in considerazione il percorso del robot: esso preferira' non ripercorrere le caselle calpestate, a meno che' non ci siano altre direzioni preferibili (ad esempio se si trova in un vicolo cieco)
*  - Se il robot si trova davanti all'uscita e non vi sono pareti ad ostacolarlo, preferira' la direzione verso cui si trova l'uscita
*
*  Ad ogni passo tuttavia, vi e' il 30% di probabilita' che il robot ignori *tutti* i criteri per la scelta della direzione, e ne scelga una casualmente (pareti permettendo)
*
*  Gli eventi che possono verificarsi sono i seguenti:
*  - Scelta casuale della direzione del robot
*  - Il robot entra in una botola: viene dunque spostato in una casella libera nel labirinto scelta casualmente
*  - Game Over: il robot entra a contatto con un buco nero
*  - Vittoria: il robot esce dal labirinto attraverso l'uscita
*/

#include "../include/main.h"

int main(void)
{
    Stanza stanza;
    Robot robot = { '*', { 8, 8 } };

    /*
    *  --- Struttura dati per creare le pareti interne ---
    *  Ogni coppia corrisponde a: { y_iniziale, x_iniziale }, { y_finale, x_finale }
    *  Ciascuna parete viene tracciata lungo il suo percorso posizione iniziale -> posizione finale
    *  E' previsto che si inserisca nella y o x finale un valore maggiore di quello nella y o x iniziale.
    */
    Vettore2D pareti[N_PARETI][2] = {
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
            // Per ogni evento, esegui l'azione corrispondente
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

            while (input != '\n');  // Attende che sia premuto INVIO per continuare

            muovi_robot(&stanza, &robot);
            disegna_stanza(&stanza, robot);  // Aggiorna la stanza
            passi++;
        }
    }
    while (!game_over && !vinto);

    printf("\n\n\n\n\n");
    return 0;
}
