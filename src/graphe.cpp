#include "graphe.h"
#include <iostream>
#include <cassert>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

GrapheImage::GrapheImage()
{
    cout << "GrapheImage" << endl;
    largeur = 2; 
    hauteur = 2;
    test();

    intensiteMax = 0;
}

GrapheImage::GrapheImage(const string &nomFichier)
{
    this->imageVersGraphe(nomFichier);
}

void GrapheImage::copieImage(const string &nomFichier)
{
    this->imageVersGraphe(nomFichier);
    this->grapheVersImage(nomFichier);
}

unsigned int GrapheImage::posNoeud(const unsigned int& i, const unsigned int& j) const
{
    return (i*this->largeur)+j;
}

Arc* GrapheImage::ouestP(const unsigned int& i, const unsigned int& j) 
{
    unsigned int indiceNoeud = this->posNoeud(i,j);
    double valeurIndice = indiceNoeud-1;
    // Dans le bord gauche
    if((indiceNoeud % this->largeur) == 0)
    {
        valeurIndice = INFINITY;
        Arc* voisinGauche = new Arc(valeurIndice, 0, 0);
        return voisinGauche;
    }
    Arc* voisinGauche = new Arc(valeurIndice, 0, 0);
    return voisinGauche;
}

Arc* GrapheImage::estP(const unsigned int& i, const unsigned int& j) 
{
    unsigned int indiceNoeud = this->posNoeud(i,j);
    double valeurIndice = indiceNoeud+1;
    // Dans le bord droit
    if(((indiceNoeud+1) % this->largeur) == 0)
    {
        valeurIndice = INFINITY;
        Arc* voisinDroit = new Arc(valeurIndice, 0, 0);
        return voisinDroit;
    }
    Arc* voisinDroit = new Arc(valeurIndice, 0, 0);
    return voisinDroit;
}

Arc* GrapheImage::nordP(const unsigned int& i, const unsigned int& j) 
{

    unsigned int indiceNoeud = this->posNoeud(i,j);
    double valeurIndice = indiceNoeud-this->largeur;
    // Dans le bord nord
    if(indiceNoeud < largeur)
    {
        valeurIndice = INFINITY;
        Arc* voisinNord = new Arc(valeurIndice, 0, 0);
        return voisinNord;
    }
    Arc* voisinNord = new Arc(valeurIndice, 0, 0);
    return voisinNord;
}

Arc* GrapheImage::sudP(const unsigned int& i, const unsigned int& j) 
{

    unsigned int indiceNoeud = this->posNoeud(i,j);
    double valeurIndice = indiceNoeud-this->largeur;
    // Dans le bord sud
    if(indiceNoeud < largeur)
    {
        valeurIndice = INFINITY;
        Arc* voisinSud = new Arc(valeurIndice, 0, 0);
        return voisinSud;
    }
    Arc* voisinSud = new Arc(valeurIndice, 0, 0);
    return voisinSud;
}

void GrapheImage::imageVersGraphe(const string &nomFichier)
{
    // Ouverture du fichier en lecture
    ifstream fichier(nomFichier, std::ios::binary);

    // Vérification si l'ouverture du fichier a réussi
    if (!fichier.is_open())
    {
        cerr << "Impossible d'ouvrir le fichier." << endl;
        EXIT_FAILURE; // Erreur
    }

    string ligne;

    // Lecture de l'en-tête PGM
    fichier >> ligne;

    if (ligne != "P2")
    {
        cerr << "Format de fichier incorrect." << endl;
        fichier.close(); // Fermeture du fichier
        EXIT_FAILURE;    // Erreur
    }

    // Lecture et stockage de (largeur, hauteur, intensité maximale)
    fichier >> largeur >> hauteur >> intensiteMax;
    cout << "Largeur : " << largeur << endl;
    cout << "Hauteur : " << hauteur << endl;
    cout << "Intensité maximale : " << intensiteMax << endl;

    // On saute d’une ligne
    // getline(fichier, ligne); // pourquoi getline ? il y a un \n à la fin de la ligne ?

    // Lecture des intensités des pixels
    // Ajout des arcs pour chaque pixels
    unsigned int valeurPixel;
    // mon indice de ligne
    unsigned int i = 0; 
    // mon indice de colonne
    unsigned int j = 0;
    while (fichier >> valeurPixel)
    {

        //On vérifie l'intensité
        assert(valeurPixel <= intensiteMax);

        //Création d'un noeud sur la tas
        Arc* tableauArc[4];
        Arc* voisinOuest = ouestP(i, j);
        Arc* voisinEst = estP(i,j);
        Arc* voisinNord = nordP(i,j);
        Arc* voisinSud = sudP(i,j);

        tableauArc[0] = voisinOuest;
        tableauArc[1] = voisinEst;
        tableauArc[2] = voisinNord;
        tableauArc[3] = voisinSud;

        Noeud* nouveauNoeud = new Noeud(valeurPixel, tableauArc);

        if(j == this->largeur){
            i++;
            j=0;
        }
        j++;
    }
    // Fermeture du fichier
    fichier.close();
}

void GrapheImage::testImageVersGraphe() // à finir
{
    this->imageVersGraphe("src/imagePgmTest.pgm");

    // Test de la lecture du fichier (début)
    assert(this->tblNoeuds[0]->getIntensite() == 200);

    // Test de la lecture du fichier (fin)
    assert(this->tblNoeuds[8]->getIntensite() == 60);

    // Test des voisins du coin gauche
    assert(this->tblNoeuds[0]->getTblArc(0)->valeur == INFINITY);
    assert(this->tblNoeuds[0]->getTblArc(1)->valeur == 1); // fait un cout tu verra que ton 1 est affecter dans des variables de ton arc mais juste pas à valeur
    assert(this->tblNoeuds[0]->getTblArc(2)->valeur == INFINITY);
    assert(this->tblNoeuds[0]->getTblArc(3)->valeur == 3);

    // Test des voisins du coin droit
    assert(this->tblNoeuds[2]->getTblArc(0)->valeur == 1);
    assert(this->tblNoeuds[2]->getTblArc(1)->valeur == INFINITY);
    assert(this->tblNoeuds[2]->getTblArc(2)->valeur == INFINITY);
    assert(this->tblNoeuds[2]->getTblArc(3)->valeur == 5);

    cout << "[OK] Image vers Graphe !" << endl;
}

void GrapheImage::grapheVersImage(const string &nomFichier)
{
    // Ouverture du fichier en écriture
    ofstream fichier(nomFichier.substr(0, nomFichier.find_last_of(".")) + "Copie.pgm", std::ios::binary);

    // Vérification si l'ouverture du fichier a réussi
    if (!fichier.is_open())
    {
        cerr << "Impossible d'ouvrir le fichier." << endl;
        EXIT_FAILURE; // Erreur
    }

    // Ecriture de l'en-tête PGM
    fichier << "P2" << endl;
    fichier << largeur << " " << hauteur << endl;
    fichier << intensiteMax << endl;
    
    for (unsigned int j = 0; j < hauteur; j++)
    {
        for (unsigned int i = 0; i < largeur; i++)
        {
            fichier << tblNoeuds[i + j * largeur]->getIntensite() << " ";
        }
        fichier << endl;
    }
}

double GrapheImage::calculerCapacite(int intensiteP, int intensiteQ)
{
    int sigma = 1;
    return exp(-pow(intensiteP - intensiteQ, 2) / (2 * pow(sigma, 2)));
}

double GrapheImage::calculerCapacitePos(unsigned int posP, unsigned int posQ)
{
    return calculerCapacite(tblNoeuds[posP]->getIntensite(), tblNoeuds[posQ]->getIntensite());
}

void GrapheImage::testCalculerCapacite()
{
    const unsigned int testSize = 9;
    const double epsilon = 0.00001;

    int intensites[testSize] = {248, 234, 0, 221, 248, 77, 234, 51, 51};
    tblNoeuds.resize(testSize);
    for (unsigned int i = 0; i < testSize; i++)
    {
        tblNoeuds[i] = new Noeud(intensites[i]);
    }

    // Test de calculerCapacite avec aroundi à l'ordre de grandeur près
    assert(compareDouble(calculerCapacitePos(0, 1), 2.74879 * pow(10, -43), epsilon * pow(10, -43)));
    // cout << "[OK] [0,0] [1,0]" << endl;
    assert(compareDouble(calculerCapacitePos(0, 3), 5.00797 * pow(10, -159), epsilon * pow(10, -159)));
    // cout << "[OK] [0,0] [0,1]" << endl;
    assert(compareDouble(calculerCapacitePos(1, 2), 0, epsilon));
    // cout << "[OK] [1,0] [2,0]" << endl;
    assert(compareDouble(calculerCapacitePos(1, 4), 2.74879 * pow(10, -43), epsilon * pow(10, -43)));
    // cout << "[OK] [1,0] [1,1]" << endl;
    assert(compareDouble(calculerCapacitePos(2, 5), 0, epsilon));
    // cout << "[OK] [2,0] [2,1]" << endl;
    assert(compareDouble(calculerCapacitePos(3, 4), 5.00797 * pow(10, -159), epsilon * pow(10, -159)));
    // cout << "[OK] [0,1] [1,1]" << endl;
    assert(compareDouble(calculerCapacitePos(3, 6), 2.00501 * pow(10, -37), epsilon * pow(10, -37)));
    // cout << "[OK] [0,1] [0,2]" << endl;
    assert(compareDouble(calculerCapacitePos(4, 5), 0, epsilon));
    // cout << "[OK] [1,1] [2,1]" << endl;
    assert(compareDouble(calculerCapacitePos(4, 7), 0, epsilon));
    // cout << "[OK] [1,1] [1,2]" << endl;
    assert(compareDouble(calculerCapacitePos(5, 8), 1.61609 * pow(10, -147), epsilon * pow(10, -147)));
    // cout << "[OK] [2,1] [2,2]" << endl;
    assert(compareDouble(calculerCapacitePos(6, 7), 0, epsilon));
    // cout << "[OK] [0,2] [1,2]" << endl;
    assert(compareDouble(calculerCapacitePos(7, 8), 1, epsilon));
    // cout << "[OK] [1,2] [2,2]" << endl;

    tblNoeuds.clear();

    cout << "[OK] Calcul Capacite !" << endl;
}

void GrapheImage::testCalculVoisins()
{
    cout << "######################" << endl;
    // Test sur un image 2 * 2
    cout << "Debut du test des fonctions pour le calcule des voisins" << endl;

    Arc* voisinGaucheTest = this->ouestP(0,0);
    Arc* voisinDroitTest = this->estP(0,0);
    Arc* voisinNordTest = this->nordP(0,0);
    Arc* voisinSudTest = this->sudP(0,0);
    assert(voisinGaucheTest->valeur == INFINITY);
    assert(voisinDroitTest->valeur == 1);
    assert(voisinNordTest->valeur ==INFINITY);
    assert (voisinSudTest->valeur == 2);

    cout << "[OK] Calcul voisin !" << endl;
}

void GrapheImage::test()
{

    cout << "##############################" << endl;
    cout << "Tests" << endl;

    // testImageVersGraphe();
    testCalculVoisins();
    // testCalculerCapacite();

    cout << "--------------------------" << endl;
    cout << "[OK] All test passed !" << endl;
}

void GrapheImage::affichageGrille() const
{
        unsigned int indiceLargeur = 0;
        unsigned int indiceNoeud = 0;
        while(indiceNoeud < this->tblNoeuds.size())
        {
                if(indiceLargeur >= this->largeur)
                {
                        // Saute une ligne
                        cout << "" << endl;
                        // Remise a zero
                        indiceLargeur = 0;
                }
                //Affichage intensite avec un espace en plus
                cout << this->tblNoeuds[indiceNoeud]->getIntensite() << " ";
                indiceLargeur ++; indiceNoeud ++;
        }
        // Ajout du endline (c'est plus jolie)
        cout << "" << endl;
}

GrapheImage::~GrapheImage()
{
    unsigned int i = 0;
    while (i < this->tblNoeuds.size())
    {
        delete this->tblNoeuds[i];
        i++;
    }
    this->tblNoeuds.clear();
    // cout << this->tblNoeuds.size() << endl;
    // cout << "Destructeur Graphe" << endl;
}

bool GrapheImage::compareDouble(double a, double b, double epsilon)
{
    return fabs(a - b) < epsilon;
}

// Test assignation
/*for (unsigned int i = 0; i < 9; i++)
 {
     if (i == 0)
     {
         double ouest = calculerCapacite(intensites[i], intensites[i + 1]);
         double est = INFINITY;
         double nord = INFINITY;
         double sud = calculerCapacite(intensites[i], intensites[i + int(sqrt(testSize))]);
         cout << "Ouest : " << ouest << endl;
         cout << "Est : " << est << endl;
         cout << "Nord : " << nord << endl;
         cout << "Sud : " << sud << endl;
     }

     // tblNoeuds.push_back(new Noeud(intensites[i]));
 }*/
