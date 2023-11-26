#include "graphe.h"
#include <iostream>
#include <cassert>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

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
    unsigned int largeur, hauteur, intensiteMax;

    // Lecture de l'en-tête PGM
    getline(fichier, ligne); // Lecture de la première ligne (doit être "P2" pour un fichier PGM)
    if (ligne != "P2")
    {
        cerr << "Format de fichier incorrect." << endl;
        fichier.close(); // Fermeture du fichier
        EXIT_FAILURE;    // Erreur
    }

    // Lecture et stockage de (largeur, hauteur, intensité maximale)
    fichier >> largeur >> hauteur >> intensiteMax;

    // On saute d’une ligne
    getline(fichier, ligne);

    // Lecture des intensités des pixels
    // Ajout des arcs pour chaque pixels
    unsigned int pixelValue;
    Arc * nouveauTblArc[4];
    for (unsigned int i = 0; i < (largeur * hauteur); i++)
    {
        fichier >> pixelValue; // Lecture des pixels mot par mot

        // assert (pixelValue < intensiteMax);
        Noeud* nouveauNoeud = new Noeud(pixelValue);
        this->calculerVoisins(i, largeur, hauteur, *nouveauTblArc);
        nouveauNoeud->setTblArc(nouveauTblArc);
        //Ajout du pixel dans le tableau
        this->tblNoeuds.push_back(nouveauNoeud);
    }

    // Fermeture du fichier
    fichier.close();
}


bool GrapheImage::compareDouble(double a, double b, double epsilon)
{
    return fabs(a - b) < epsilon;
}

GrapheImage::GrapheImage()
{
    cout << "GrapheImage" << endl;
    test();
}

void GrapheImage::test()
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
    cout << "[OK] [0,0] [1,0]" << endl;
    assert(compareDouble(calculerCapacitePos(0, 3), 5.00797 * pow(10, -159), epsilon * pow(10, -159)));
    cout << "[OK] [0,0] [0,1]" << endl;
    assert(compareDouble(calculerCapacitePos(1, 2), 0, epsilon));
    cout << "[OK] [1,0] [2,0]" << endl;
    assert(compareDouble(calculerCapacitePos(1, 4), 2.74879 * pow(10, -43), epsilon * pow(10, -43)));
    cout << "[OK] [1,0] [1,1]" << endl;
    assert(compareDouble(calculerCapacitePos(2, 5), 0, epsilon));
    cout << "[OK] [2,0] [2,1]" << endl;
    assert(compareDouble(calculerCapacitePos(3, 4), 5.00797 * pow(10, -159), epsilon * pow(10, -159)));
    cout << "[OK] [0,1] [1,1]" << endl;
    assert(compareDouble(calculerCapacitePos(3, 6), 2.00501 * pow(10, -37), epsilon * pow(10, -37)));
    cout << "[OK] [0,1] [0,2]" << endl;
    assert(compareDouble(calculerCapacitePos(4, 5), 0, epsilon));
    cout << "[OK] [1,1] [2,1]" << endl;
    assert(compareDouble(calculerCapacitePos(4, 7), 0, epsilon));
    cout << "[OK] [1,1] [1,2]" << endl;
    assert(compareDouble(calculerCapacitePos(5, 8), 1.61609 * pow(10, -147), epsilon * pow(10, -147)));
    cout << "[OK] [2,1] [2,2]" << endl;
    assert(compareDouble(calculerCapacitePos(6, 7), 0, epsilon));
    cout << "[OK] [0,2] [1,2]" << endl;
    assert(compareDouble(calculerCapacitePos(7, 8), 1, epsilon));
    cout << "[OK] [1,2] [2,2]" << endl;

    tblNoeuds.clear();

    // Test assignation
    for (unsigned int i = 0; i < 9; i++)
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
    }

    cout << "##############################" << endl;
    cout << "[OK] All test passed !" << endl;
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

GrapheImage::~GrapheImage()
{
    cout << "~GrapheImage" << endl;
}