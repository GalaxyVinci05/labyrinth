#include "functions.h"

int main(void)
{
    Stanza stanza;
    Robot robot;

    inizializza_stanza(&stanza);
    inizializza_robot(&stanza, &robot);

    disegna_stanza(stanza, robot);

    return 0;
}
