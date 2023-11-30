#ifndef GRAPHE_H
#define GRAPHE_H

#include "noeud.h"
#include <vector>
#include <string>

using namespace std;

class GrapheImage
{
private:
    #define ERREUR_POS 	65535
    unsigned int largeur, hauteur, intensiteMax;

    // Données-membres
    vector<Noeud *> tblNoeuds;

    // Fonction qui construit le graphe d'une image pgm
    void imageVersGraphe(const string &nomFichier);

    // Fonction qui construit l'image à partir du graphe
    void grapheVersImage(const string &nomFichier);

    // Fonction qui calcule l'indice d'un noeud dans le tableau
    // à partir de la position [i,j]
    unsigned int posNoeud(const unsigned int i, const unsigned int j) const;
    unsigned int posOuest(const unsigned int i, const unsigned int j) const;
    unsigned int posEst(const unsigned int i, const unsigned int j) const;
    unsigned int posNord(const unsigned int i, const unsigned int j) const;
    unsigned int posSud(const unsigned int i, const unsigned int j) const;
    // ou de l'indiceGlobal d'un noeud initial (pos)
    unsigned int posOuest(const unsigned int pos) const;
    unsigned int posEst(const unsigned int pos) const;
    unsigned int posNord(const unsigned int pos) const;
    unsigned int posSud(const unsigned int pos) const;

    // Fonction qui calcule les arcs voisins d'un noeud
    Arc *ajouterOuestP(const unsigned int &i, const unsigned int &j);
    Arc *ajouterEstP(const unsigned int &i, const unsigned int &j);
    Arc *ajouterNordP(const unsigned int &i, const unsigned int &j);
    Arc *ajouterSudP(const unsigned int &i, const unsigned int &j);

    // Fonction qui calcule la capacité d'un arc
    double calculerCapacite(int intensiteP, int intensiteQ);
    double calculerCapacitePos(unsigned int posP, unsigned int posQ);

    // tests
    void test();
    void testCalculPosNoeud();
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