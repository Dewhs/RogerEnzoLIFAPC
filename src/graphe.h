#ifndef GRAPHE_H
#define GRAPHE_H

#include "noeud.h"
#include <vector>
#include <string>


using namespace std;

class GrapheImage
{
    private :
    //Données-membres
    vector<Noeud*> tblNoeuds;

    // Fonction qui construit le graphe d'une image pgm
    void imageVersGraphe(const string& nomFichier);

    // Fonction qui calcule les voisins d'un pixel 
    void calculerVoisins(const unsigned int indiceNoeud, const unsigned int largeur, 
    const unsigned int hauteur, Arc* tblArc[4]);

    //Cette fonction est la pour le moment mais je la mettrai dans un fichier outils.h ou quelque chose du genre
    bool compareDouble(double a, double b, double epsilon);

    void test();

    double calculerCapacite(int intensiteP, int intensiteQ);

    double calculerCapacitePos(unsigned int posP,unsigned int posQ);

    public :
        GrapheImage();
        GrapheImage(const string& nomFichier);
        void testCalculVoisins();
        void testImageVersGraphe();
        ~GrapheImage();
};

#endif // GRAPHE_H