#include "graphe.h"


int main(int argc, char const *argv[])
{
    //GrapheImage g;
    GrapheImage g("src/imagePgmExemple.pgm");
    g.binarisation("100");
    //g.affichageGrille();
    // g.copieImage("src/imagePgmTest.pgm");
    
    return 0;
}