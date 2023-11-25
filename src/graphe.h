#ifndef GRAPHE_H
#define GRAPHE_H

#include "noeud.h"
#include <vector>

using namespace std;

class GrapheImage
{
    private :

    //Cette fonction est la pour le moment mais je la mettrai dans un fichier outils.h ou quelque chose du genre
    bool compareDouble(double a, double b, double epsilon);

    vector<Noeud*> tblNoeuds;
        
    void Test();

    double calculerCapacite(int posP, int posQ);


    public :
        GrapheImage();
        ~GrapheImage();

    


    
};

#endif // GRAPHE_H