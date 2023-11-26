#ifndef GRAPHE_H
#define GRAPHE_H

#include "noeud.h"
#include <vector>


using namespace std;

class GrapheImage
{
    private :

    void imageVersGraphe(const string& nomFichier);

    //Cette fonction est la pour le moment mais je la mettrai dans un fichier outils.h ou quelque chose du genre
    bool compareDouble(double a, double b, double epsilon);

    vector<Noeud*> tblNoeuds;
        
    void test();

    double calculerCapacite(int intensiteP, int intensiteQ);
    double calculerCapacitePos(unsigned int posP,unsigned int posQ);

    void calculerVoisins(const unsigned int indiceNoeud, const unsigned int largeur, const unsigned int hauteur, const Arc* tblArc);

    public :
        GrapheImage();
        ~GrapheImage();

    


    
};

#endif // GRAPHE_H