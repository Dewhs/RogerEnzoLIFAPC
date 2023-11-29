#ifndef GRAPHE_H
#define GRAPHE_H

#include "noeud.h"
#include <vector>
#include <string>

using namespace std;

class GrapheImage
{
private:
    unsigned int largeur, hauteur, intensiteMax;

    // Données-membres
    vector<Noeud *> tblNoeuds;

    // Fonction qui construit le graphe d'une image pgm
    void imageVersGraphe(const string &nomFichier);

    // Fonction qui construit l'image à partir du graphe
    void grapheVersImage(const string &nomFichier);

    // Fonction qui calcule l'indice d'un noeud dans le tableau
    unsigned int posNoeud(const unsigned int& i, const unsigned int& j) const;

    //Fonction qui calcule les voisins d'un noeud
    Arc* estP(const unsigned int& i, const unsigned int& j);

    Arc* ouestP(const unsigned int& i, const unsigned int& j);
    
    Arc* nordP(const unsigned int& i, const unsigned int& j);
    
    Arc* sudP(const unsigned int& i, const unsigned int& j);
    
    // Fonction qui calcule la capacité d'un arc
    double calculerCapacite(int intensiteP, int intensiteQ);
    double calculerCapacitePos(unsigned int posP, unsigned int posQ);
    
    // tests
    void test();
    void testCalculVoisins();
    void testImageVersGraphe();
    void testCalculerCapacite();

    // Cette fonction est la pour le moment mais je la mettrai dans un fichier outils.h ou quelque chose du genre
    bool compareDouble(double a, double b, double epsilon);


public:
    GrapheImage();
    GrapheImage(const string &nomFichier);
    void affichageGrille() const;
    void copieImage(const string &nomFichier);
    ~GrapheImage();
};

#endif // GRAPHE_H