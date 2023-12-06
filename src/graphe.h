#ifndef GRAPHE_H
#define GRAPHE_H

#include "noeud.h"
#include <vector>
#include <string>

using namespace std;

class GrapheImage
{
private:
#define ERREUR_POS 65535
    
    // Données-membres
    vector<Noeud *> tblNoeuds;
    unsigned int largeur, hauteur, intensiteMax;

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

    // Fonction qui construit le graphe d'une image pgm
    void imageVersGraphe(const string &nomFichier);

    // Fonction qui construit l'image à partir du graphe
    void grapheVersImage(const string &nomFichier);

    // Fonction de recherche d'un chemin entre deux noeuds
    // retourne un vecteur de pair contenant le chemin
    vector<pair <int, int> > trouverChemin();

    // Fonction qui permet le premier noeud d'entre si l'arc entre la source et un noeud est saturé
    int trouverEntree();

    //Fonction qui supprime ...
    void nettoyageChemin(vector<pair <int, int> > &chemin);

    // Fonction qui calcule la capacité d'un arc
    double calculerCapacite(int intensiteP, int intensiteQ);
    double calculerCapacitePos(unsigned int posP, unsigned int posQ);

    // Fonction qui calcule la capacité d'un arc entre un noeud et la source ou le puit
    double calculerCapacitePS(unsigned int posP, bool aSource);

    //Fonction qui récupere le flot minimum sur le chemin
    double getMinFlot(vector<pair <int, int> > &chemin);

    // Fonction qui calcule le flot
    double calculerFlot(unsigned int posP, unsigned int posQ, int aSource);

    // Incrementer le flot
    void incrementerFlot(double flot);

    //Affiche le chemin (affiche le chemin du premier noeud vers le puits noté 10)
    void afficherChemin(vector<pair <int, int> > &chemin);

    // tests
    void test();

    void testCalculPosNoeud();

    void testCalculVoisins();

    void testImageVersGraphe();

    void testCalculerCapacite();

    void testBinarisation();

    // Cette fonction est la pour le moment mais je la mettrai dans un fichier outils.h ou quelque chose du genre
    bool compareDouble(double a, double b, double epsilon);

public:
    //Constructeur par default
    GrapheImage();

    // Constructeur avec une image
    GrapheImage(const string &nomFichier);

    // Fonction qui affiche une image dans le terminal
    void affichageGrille() const;

    // Fonction de binarisation
    void binarisation(const string &nomFichier);

    //Destructeur
    ~GrapheImage();
};

#endif // GRAPHE_H