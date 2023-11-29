#include "graphe.h"


int main(int argc, char const *argv[])
{
    
    GrapheImage g("src/imagePgmTest.pgm");
    g.affichageGrille();
    g.copieImage("src/imagePgmTest.pgm");
    return 0;
}