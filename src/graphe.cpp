#include "graphe.h"
#include <iostream>
#include <cassert>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>

using namespace std;

GrapheImage::GrapheImage()
{
    // On appelle les tests
    test();
    largeur = 0;
    hauteur = 0;
    intensiteMax = 0;
}

GrapheImage::GrapheImage(const string &nomFichier)
{
    this->imageVersGraphe(nomFichier);
    this->binarisation("Binariser");

    // ---------------------- TEST ---------------------- //

    // this->tblNoeuds[0]->flotSource = 9999999;
    // this->tblNoeuds[0]->flotPuit = 9999999;
    // this->tblNoeuds[0]->getTblArc(1)->flot = 9999999;
    // this->tblNoeuds[0]->getTblArc(3)->flot = 9999999;
    // this->tblNoeuds[1]->flotPuit = 9999999;
    // this->tblNoeuds[1]->flotSource = 9999999;
    // this->tblNoeuds[1]->getTblArc(1)->flot = 9999999;
    // this->tblNoeuds[1]->getTblArc(3)->flot = 9999999;
    // this->tblNoeuds[3]->flotPuit = 9999999;
    // this->tblNoeuds[2]->flotPuit = 9999999;
    // this->tblNoeuds[4]->flotPuit = 9999999;
    // this->tblNoeuds[6]->flotPuit = 9999999;
    // this->tblNoeuds[5]->flotPuit = 9999999;
    // this->tblNoeuds[7]->flotPuit = 9999999;
    // this->tblNoeuds[8]->flotPuit = 9999999;

    // vector<pair<int, int>> chemin = trouverChemin();

    // cout << "calculer flot" << endl;
    // cout << "flot source : " << this->calculerFlot(0, 0, 1) << endl;
    // cout << "flot puit : " << this->calculerFlot(0, 0, -1) << endl;

    // cout << "calculerMinFlot : " << this->getMinFlot(chemin) << endl;

    // cout << "chemin.size() : " << chemin.size() << endl;
    // for (unsigned int i = 0; i < chemin.size(); i++)
    // {
    //     cout << i << " : " << chemin[i].first << " "
    //          << " -> " << chemin[i].second << endl;
    // }

    // afficherChemin(chemin);
}

// ------------------- Fonction de recherche d'un chemin entre deux noeuds ------------------- //

vector<pair <int, int> > GrapheImage::trouverChemin()
{
    // on crée la file qui va contenir les noeuds à visiter
    // on crée un vecteur de pair qui va contenir le chemin
    queue<int> file;
    vector<pair <int, int> > chemin;

    // on verifie que la capcaié de la source est bien supérieur au flot
    // tant que la capacité de la source est inferieur au flot et que la valeur de la position globale du noeud d'entrée est inferieur à la taille du tableau de noeud
    // on incrémente de 1 la valeur de la position globale du noeud d'entrée

    int indiceNoeud = trouverEntree();
    if (indiceNoeud == -1)
    {
        return chemin;
    }
    file.push(indiceNoeud);

    // on a notre position globale du noeud d'entrée

    // on peut commencer notre recherche de chemin
    // les noeuds vue sont marqués à 1
    // les noeuds visités sont marqués à 2

    // tant que la file n'est pas vide
    while (!file.empty())
    {
        // on récupère le noeud en tête de file
        int indiceNoeud = file.front();
        // on le supprime de la file
        file.pop();

        // on le marque comme visité
        this->tblNoeuds[indiceNoeud]->setMarque(2);
        // on verifie si la capacitePuit > flotPuit
        if (this->tblNoeuds[indiceNoeud]->capacitePuit > this->tblNoeuds[indiceNoeud]->flotPuit)
        {
            // si oui on ajoute le noeud au chemin et on retourne le chemin
            chemin.push_back(make_pair(indiceNoeud, this->tblNoeuds.size() + 1));
            this->nettoyageChemin(chemin);
            return chemin;
        }

        int j = 0;
        // sinon on ajoute les noeud voisins non vue et non visité à la file
        for (unsigned int i = 0; i < 4; i++)
        {
            j++;
            if (this->tblNoeuds[indiceNoeud]->getTblArc(i)->valeur != ERREUR_POS)
            {
                if (this->tblNoeuds[this->tblNoeuds[indiceNoeud]->getTblArc(i)->valeur]->getMarque() == 0)
                {
                    j--;
                    file.push(this->tblNoeuds[indiceNoeud]->getTblArc(i)->valeur);
                    chemin.push_back(make_pair(indiceNoeud, this->tblNoeuds[indiceNoeud]->getTblArc(i)->valeur));
                    // on les marque comme vue
                    this->tblNoeuds[this->tblNoeuds[indiceNoeud]->getTblArc(i)->valeur]->setMarque(1);
                }
            }
        }
        // si j = 4 alors on a pas de voisin non vue et non visité
        if (j == 4)
        {
            // on marque le noeud comme visité
            this->tblNoeuds[indiceNoeud]->setMarque(2);

            // on clear la file
            while (!file.empty())
            {
                file.pop();
            }

            indiceNoeud = this->trouverEntree();
            if (indiceNoeud == -1)
            {
                return chemin;
            }
            file.push(indiceNoeud);
        }
        // fin de la boucle
    }

    // on retourne un vecteur vide
    return chemin;
}

void GrapheImage::nettoyageChemin(vector<pair <int, int> > &chemin)
{
    int tmp = this->tblNoeuds.size() + 1;
    int cheminSize = chemin.size();
    for (int i = cheminSize - 1; i >= 0; i--)
    {
        if (chemin[i].second != tmp)
        {
            chemin.erase(chemin.begin() + i);
        }
        else
        {
            tmp = chemin[i].first;
        }
    }
}

int GrapheImage::trouverEntree()
{
    // on cherche le noeud d'entrée
    for (unsigned int i = 0; i < this->tblNoeuds.size(); i++)
    {
        // si la capacité de la source est supérieur au flot de la source
        if (this->tblNoeuds[i]->capaciteSource > this->tblNoeuds[i]->flotSource && this->tblNoeuds[i]->getMarque() == 0)
        {
            // on retourne la position globale du noeud d'entrée
            return i;
        }
    }
    // sinon on retourne -1
    return -1;
}

// ------------------- Fonction pour calculer les indices globaux  ------------------- //
unsigned int GrapheImage::posNoeud(const unsigned int i, const unsigned int j) const
{
    return (j * this->largeur) + i;
}

// position [i,j] du noeud initial
unsigned int GrapheImage::posOuest(const unsigned int i, const unsigned int j) const
{
    if (i == 0)
    {
        return ERREUR_POS;
    }
    return (j * this->largeur) + (i - 1);
}

unsigned int GrapheImage::posEst(const unsigned int i, const unsigned int j) const
{
    if (i + 1 == largeur)
    {
        return ERREUR_POS;
    }
    return (j * this->largeur) + (i + 1);
}

unsigned int GrapheImage::posNord(const unsigned int i, const unsigned int j) const
{
    if (j == 0)
    {
        return ERREUR_POS;
    }
    return ((j - 1) * this->largeur) + i;
}

unsigned int GrapheImage::posSud(const unsigned int i, const unsigned int j) const
{
    if (j + 1 == hauteur)
    {
        return ERREUR_POS;
    }
    return ((j + 1) * this->largeur) + i;
}

// indiceGlobal du noeud initial
unsigned int GrapheImage::posOuest(const unsigned int pos) const
{
    if (pos % this->largeur == 0)
    {
        return ERREUR_POS;
    }
    return pos - 1;
}

unsigned int GrapheImage::posEst(const unsigned int pos) const
{
    if ((pos + 1) % this->largeur == 0)
    {
        return ERREUR_POS;
    }

    return pos + 1;
}

unsigned int GrapheImage::posNord(const unsigned int pos) const
{
    if (pos < this->largeur)
    {
        return ERREUR_POS;
    }
    return pos - this->largeur;
}

unsigned int GrapheImage::posSud(const unsigned int pos) const
{
    if (pos >= (hauteur * largeur) - largeur)
    {
        return ERREUR_POS;
    }
    return pos + this->largeur;
}

// ------------------- Fonction pour calculer les voisins ------------------- //
Arc *GrapheImage::ajouterOuestP(const unsigned int &i, const unsigned int &j)
{
    unsigned int indiceNoeud = this->posNoeud(i, j);
    double valeurIndice = posOuest(indiceNoeud);
    // Dans le bord gauche
    if ((indiceNoeud % this->largeur) == 0)
    {
        valeurIndice = ERREUR_POS;
        Arc *voisinGauche = new Arc(valeurIndice, 0, 0);
        return voisinGauche;
    }
    Arc *voisinGauche = new Arc(valeurIndice, 0, 0);
    return voisinGauche;
}

Arc *GrapheImage::ajouterEstP(const unsigned int &i, const unsigned int &j)
{
    unsigned int indiceNoeud = this->posNoeud(i, j);
    double valeurIndice = posEst(indiceNoeud);
    // Dans le bord droit
    if (((indiceNoeud + 1) % this->largeur) == 0)
    {
        valeurIndice = ERREUR_POS;
        Arc *voisinDroit = new Arc(valeurIndice, 0, 0);
        return voisinDroit;
    }
    Arc *voisinDroit = new Arc(valeurIndice, 0, 0);
    return voisinDroit;
}

Arc *GrapheImage::ajouterNordP(const unsigned int &i, const unsigned int &j)
{

    unsigned int indiceNoeud = this->posNoeud(i, j);
    double valeurIndice = posNord(indiceNoeud);
    // Dans le bord nord
    if (indiceNoeud < largeur)
    {
        valeurIndice = ERREUR_POS;
        Arc *voisinNord = new Arc(valeurIndice, 0, 0);
        return voisinNord;
    }
    Arc *voisinNord = new Arc(valeurIndice, 0, 0);
    return voisinNord;
}

Arc *GrapheImage::ajouterSudP(const unsigned int &i, const unsigned int &j)
{

    unsigned int indiceNoeud = this->posNoeud(i, j);
    double valeurIndice = posSud(indiceNoeud);
    // Dans le bord sud
    if (indiceNoeud >= (hauteur * largeur) - largeur)
    {
        valeurIndice = ERREUR_POS;
        Arc *voisinSud = new Arc(valeurIndice, 0, 0);
        return voisinSud;
    }
    Arc *voisinSud = new Arc(valeurIndice, 0, 0);
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

    // Lecture des intensités des pixels
    // Ajout des arcs pour chaque pixels
    unsigned int valeurPixel;
    // mon indice de ligne
    unsigned int i = 0;
    // mon indice de colonne
    unsigned int j = 0;
    while (fichier >> valeurPixel)
    {
        // On vérifie l'intensité
        assert(valeurPixel <= intensiteMax);

        // Création du tableau de voisin (Arc)
        Arc *tableauArc[4];
        Arc *voisinOuest = ajouterOuestP(i, j);
        Arc *voisinEst = ajouterEstP(i, j);
        Arc *voisinNord = ajouterNordP(i, j);
        Arc *voisinSud = ajouterSudP(i, j);

        tableauArc[0] = voisinOuest;
        tableauArc[1] = voisinEst;
        tableauArc[2] = voisinNord;
        tableauArc[3] = voisinSud;

        Noeud *nouveauNoeud = new Noeud(valeurPixel, tableauArc);
        this->tblNoeuds.push_back(nouveauNoeud);

        if (i == this->largeur)
        {
            j++;
            i = 0;
        }
        i++;
    }
    // Ajout des capacitées pour chaque arc
    for (unsigned int i = 0; i < this->tblNoeuds.size(); i++)
    {
        // Parcours du tableau de noeud
        for (unsigned int j = 0; j < 4; j++)
        {
            if (!(this->tblNoeuds[i]->getTblArc(j)->capacite == ERREUR_POS))
            {
                this->tblNoeuds[i]->getTblArc(j)->capacite = this->calculerCapacite(
                    i, this->tblNoeuds[i]->getTblArc(j)->valeur);
            }
        }

        this->tblNoeuds[i]->capaciteSource = this->calculerCapacitePS(i, true);
        this->tblNoeuds[i]->capacitePuit = this->calculerCapacitePS(i, false);
    }

    // Fermeture du fichier
    fichier.close();
}

void GrapheImage::grapheVersImage(const string &nomFichier)
{
    // Ouverture du fichier en écriture
    ofstream fichier(nomFichier.substr(0, nomFichier.find_last_of(".")) + ".pgm", std::ios::binary);

    // Vérification si l'ouverture du fichier a réussi
    if (!fichier.is_open())
    {
        cerr << "Impossible d'ouvrir le fichier." << endl;
        EXIT_FAILURE; // Erreur
    }

    // Ecriture de l'en-tête PGM
    fichier << "P2" << endl;
    fichier << this->largeur << " " << this->hauteur << endl;
    fichier << this->intensiteMax << endl;

    for (unsigned int j = 0; j < this->hauteur; j++)
    {
        for (unsigned int i = 0; i < this->largeur; i++)
        {
            fichier << this->tblNoeuds[i + j * this->largeur]->getIntensite() << " ";
        }
        fichier << endl;
    }
}

// ------------------- Fonction pour calculer les flots ------------------- //
double GrapheImage::calculerFlot(unsigned int posP, unsigned int posQ, int aSource)
{

    double capPQ, flotPQ, flotQP;
    // aSource = 1 si on calcule le flot entre la source et un noeud
    // aSource = 0 si on calcule le flot entre deux noeuds
    // aSource = -1 si on calcule le flot entre un noeud et le puit
    if (aSource == 1)
    {
        // On récupère la capacité de l'arc P(Source) et Q
        capPQ = this->tblNoeuds[posQ]->capaciteSource;
        // On récupère le flot de l'arc P(Source) et Q
        flotPQ = this->tblNoeuds[posQ]->flotSource;
        // On récupère le flot de l'arc Q et P(Source)
        flotQP = 0;
    }
    else if (aSource == 0)
    {
        // On récupère la capacité de l'arc P et Q
        capPQ = this->tblNoeuds[posP]->getTblArc(posQ)->capacite;
        // On récupère le flot de l'arc P et Q
        flotPQ = this->tblNoeuds[posP]->getTblArc(posQ)->flot;
        // On récupère le flot de l'arc Q et P
        flotQP = this->tblNoeuds[posQ]->getTblArc(posP)->flot;
    }
    else
    {
        // On récupère la capacité de l'arc P et Q(Puit)
        capPQ = this->tblNoeuds[posP]->capacitePuit;
        // On récupère le flot de l'arc P et Q(Puit)
        flotPQ = this->tblNoeuds[posP]->flotPuit;
        // On récupère le flot de l'arc Q(Puit) et P
        flotQP = 0;
    }

    // On calcule le flot
    return capPQ + (flotPQ - flotQP);

}

double GrapheImage::getMinFlot(vector<pair <int, int> > &chemin)
{
    double minFlot = this->calculerFlot(0, chemin[0].first, 1);
    int cheminSize = chemin.size();

    for (int i = 0; i < cheminSize - 2; i++)
    {
        if (this->calculerFlot(chemin[i].first, chemin[i].second, 0) < minFlot)
        {
            minFlot = this->calculerFlot(chemin[i].first, chemin[i].second, 0);
        }
    }
    if (this->calculerFlot(chemin[chemin.size() - 1].first, 0, -1) < minFlot)
    {
        minFlot = this->calculerFlot(chemin[chemin.size() - 1].first, 0, -1);
    }
    return minFlot;
}

void GrapheImage::incrementerFlot(double flot)
{
    int j = 0;
    while (j < int(tblNoeuds.size()))
    {
        tblNoeuds[j]->flotSource += flot;
        tblNoeuds[j]->flotPuit += flot;
        for (int i = 0; i < 4; i++)
        {
            tblNoeuds[i]->getTblArc(i)->flot += flot;
        }

        j++;
    }
}

void GrapheImage::afficherChemin(vector<pair <int, int> > &chemin)
{
    int cheminSize = chemin.size();
    if (cheminSize > 0)
    {
        for (int i = 0; i < cheminSize; i++)
        {
            cout << i << " : " << chemin[i].first << " "
                 << " -> " << chemin[i].second << endl;
        }
    }
}

// ------------------- Fonction pour calculer les capacitées ------------------- //
double GrapheImage::calculerCapacite(int intensiteP, int intensiteQ)
{

    int sigma = 1;
    return exp(-pow(intensiteP - intensiteQ, 2) / (2 * pow(sigma, 2)));
}

double GrapheImage::calculerCapacitePos(unsigned int posP, unsigned int posQ)
{
    return calculerCapacite(this->tblNoeuds[posP]->getIntensite(), this->tblNoeuds[posQ]->getIntensite());
}

double GrapheImage::calculerCapacitePS(unsigned int posP, bool aSource)
{
    double alpha = 2.0; // Alpha est a définir c'est un paramètre du programme d'après le sujet

    // On calcule la capacite entre la source et un pixel
    if (aSource)
    {
        return -(alpha * log((255.0 - this->tblNoeuds[posP]->getIntensite()) / 255.0));
    }
    // On calcule la capacité entre le puit
    else
    {
        return -(alpha * log((this->tblNoeuds[posP]->getIntensite()) / 255.0));
    }
}

void GrapheImage::affichageGrille() const
{
    unsigned int indiceLargeur = 0;
    unsigned int indiceNoeud = 0;
    while (indiceNoeud < this->tblNoeuds.size())
    {
        if (indiceLargeur >= this->largeur)
        {
            // Saute une ligne
            cout << "" << endl;
            // Remise a zero
            indiceLargeur = 0;
        }
        // Affichage intensite avec un espace en plus
        cout << this->tblNoeuds[indiceNoeud]->getIntensite() << " ";
        indiceLargeur++;
        indiceNoeud++;
    }
    // Ajout du endline (c'est plus jolie)
    cout << "" << endl;
}

void GrapheImage::binarisation(const string &nomFichier)
{
    vector<pair <int, int> > chemin = this->trouverChemin();
    double flotOptimal = 0;
    while (chemin.size() > 0 && chemin[chemin.size() - 1].second == int(this->tblNoeuds.size()) + 1)
    {
        double minFlot = 1;
        // double minFlot = getMinFlot(chemin);
        flotOptimal += minFlot;
        this->incrementerFlot(minFlot);
        chemin = this->trouverChemin();
    }

    int j = 0;
    while (j < int(tblNoeuds.size()))
    {
        if (flotOptimal < this->tblNoeuds[j]->capaciteSource)
        {
            this->tblNoeuds[j]->setIntensite(255);
        }
        else
        {
            this->tblNoeuds[j]->setIntensite(0);
        }
        j++;
    }
    this->intensiteMax = 255;
    this->grapheVersImage(nomFichier);
}

// ------------------- Tests ------------------- //

void GrapheImage::testCalculPosNoeud()
{
    hauteur = 6;
    largeur = 3;
    assert(posNoeud(0, 0) == 0);
    assert(posNoeud(1, 0) == 1);
    assert(posNoeud(2, 0) == 2);
    assert(posNoeud(0, 1) == 3);
    assert(posNoeud(1, 1) == 4);
    assert(posNoeud(2, 1) == 5);
    assert(posNoeud(0, 2) == 6);
    assert(posNoeud(1, 2) == 7);
    assert(posNoeud(2, 2) == 8);
    assert(posNoeud(0, 3) == 9);
    assert(posNoeud(1, 3) == 10);
    assert(posNoeud(2, 3) == 11);
    assert(posNoeud(0, 4) == 12);
    assert(posNoeud(1, 4) == 13);
    assert(posNoeud(2, 4) == 14);
    assert(posNoeud(0, 5) == 15);
    assert(posNoeud(1, 5) == 16);
    assert(posNoeud(2, 5) == 17);

    // coin en haut à gauche
    assert(posOuest(0, 0) == ERREUR_POS && posOuest(0) == ERREUR_POS);
    assert(posEst(0, 0) == 1 && posEst(0) == 1);
    assert(posNord(0, 0) == ERREUR_POS && posNord(0) == ERREUR_POS);
    assert(posSud(0, 0) == 3 && posSud(0) == 3);
    // coin en haut à droite
    assert(posOuest(2, 0) == 1 && posOuest(2) == 1);
    assert(posEst(2, 0) == ERREUR_POS && posEst(2) == ERREUR_POS);
    assert(posNord(2, 0) == ERREUR_POS && posNord(2) == ERREUR_POS);
    assert(posSud(2, 0) == 5 && posSud(2) == 5);
    // coin en bas à gauche
    assert(posOuest(0, 5) == ERREUR_POS && posOuest(15) == ERREUR_POS);
    assert(posEst(0, 5) == 16 && posEst(15) == 16);
    assert(posNord(0, 5) == 12 && posNord(15) == 12);
    assert(posSud(0, 5) == ERREUR_POS && posSud(15) == ERREUR_POS);
    // coin en bas à droite
    assert(posOuest(2, 5) == 16 && posOuest(17) == 16);
    assert(posEst(2, 5) == ERREUR_POS && posEst(17) == ERREUR_POS);
    assert(posNord(2, 5) == 14 && posNord(17) == 14);
    assert(posSud(2, 5) == ERREUR_POS && posSud(17) == ERREUR_POS);

    hauteur = 0;
    largeur = 0;

    cout << "[OK] Calcul Positions !" << endl;
}

void GrapheImage::testImageVersGraphe()
{
    this->imageVersGraphe("imgTest/imagePgmTest.pgm");

    // Test de la lecture du fichier (début)
    assert(this->tblNoeuds[0]->getIntensite() == 200);

    // Test de la lecture du fichier (fin)
    assert(this->tblNoeuds[8]->getIntensite() == 60);

    // Test des voisins du coin gauche
    assert(this->tblNoeuds[0]->getTblArc(0)->valeur == ERREUR_POS);
    assert(this->tblNoeuds[0]->getTblArc(1)->valeur == 1);
    assert(this->tblNoeuds[0]->getTblArc(2)->valeur == ERREUR_POS);
    assert(this->tblNoeuds[0]->getTblArc(3)->valeur == 3);

    // Test des voisins du coin droit
    assert(this->tblNoeuds[2]->getTblArc(0)->valeur == 1);
    assert(this->tblNoeuds[2]->getTblArc(1)->valeur == ERREUR_POS);
    assert(this->tblNoeuds[2]->getTblArc(2)->valeur == ERREUR_POS);
    assert(this->tblNoeuds[2]->getTblArc(3)->valeur == 5);

    // Test de la capacité pour 4 arcs
    // AVEC SIGMA = 4
    const double epsilon = 0.00001;

    assert(this->tblNoeuds[0]->getTblArc(0)->capacite == 0);

    // assert(this->tblNoeuds[0]->getTblArc(1)->capacite ==0);
    assert(this->tblNoeuds[0]->getTblArc(2)->capacite == 0);
    assert(compareDouble(calculerCapacitePos(0, 3), 1.38389 * pow(10, -87), epsilon * pow(10, -87)));

    // assert(this->tblNoeuds[1]->getTblArc(0)->capacite == 0);
    // assert(this->tblNoeuds[1]->getTblArc(1)->capacite == 0);
    assert(this->tblNoeuds[1]->getTblArc(2)->capacite == 0);
    assert(compareDouble(calculerCapacitePos(1, 4), 1.38389 * pow(10, -87), epsilon * pow(10, -87)));
    
    //On vide le tableau
    this->tblNoeuds.clear();
    cout << "[OK] Image vers Graphe !" << endl;
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
    // cout << "######################" << endl;
    // // Test sur un image 2 * 2
    // cout << "Debut du test des fonctions pour le calcule des voisins" << endl;

    hauteur = 2;
    largeur = 2;

    Arc *voisinGaucheTest = this->ajouterOuestP(0, 0);
    Arc *voisinDroitTest = this->ajouterEstP(0, 0);
    Arc *voisinNordTest = this->ajouterNordP(0, 0);
    Arc *voisinSudTest = this->ajouterSudP(0, 0);
    assert(voisinGaucheTest->valeur == ERREUR_POS);
    assert(voisinDroitTest->valeur == 1);
    assert(voisinNordTest->valeur == ERREUR_POS);
    assert(voisinSudTest->valeur == 2);

    hauteur = 0;
    largeur = 0;
    cout << "[OK] Calcul voisin !" << endl;
}

void GrapheImage::testBinarisation(){
    //Appelle de la fonction imageVersGraphe pour avoir une image de test
    this->imageVersGraphe("imgTest/imagePgmTest.pgm");

    this->binarisation("imagePgmTest.pgm");

    // Utilisation de remove pour supprimer le fichier
    if (remove("imagePgmTest.pgm") != 0) {
        perror("Erreur lors de la suppression du fichier"); // Affiche l'erreur si la suppression échoue
    } else {
        cout << "Fichier test supprimer !" << endl;
    }

    for(unsigned int i = 0; i < this->tblNoeuds.size(); i++)
    {
        // On test si chaque pixel est soit égale a 0 ou a 255
        assert(this->tblNoeuds[i]->getIntensite() == 255 || this->tblNoeuds[i]->getIntensite() == 0);
    }

    this->tblNoeuds.clear();

    cout << "[Ok] Binarisation !" << endl;
}

void GrapheImage::test()
{
    cout << "##############################" << endl;
    cout << "Tests" << endl;

    testCalculPosNoeud();
    testImageVersGraphe();
    testCalculVoisins();
    testCalculerCapacite();
    testBinarisation();

    cout << "--------------------------" << endl;
    cout << "[OK] All test passed !" << endl;
}

// ------------------- Destructeur ------------------- //
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
// ------------------- Tools ------------------- //

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
         double est = ERREUR_POS;
         double nord = ERREUR_POS;
         double sud = calculerCapacite(intensites[i], intensites[i + int(sqrt(testSize))]);
         cout << "Ouest : " << ouest << endl;
         cout << "Est : " << est << endl;
         cout << "Nord : " << nord << endl;
         cout << "Sud : " << sud << endl;
     }

     // tblNoeuds.push_back(new Noeud(intensites[i]));
 }*/

/*

// Créer une file pour le parcours en largeur
    queue<int> file;
    // ajout du premier noeud à la file
    file.push(0);
    this->tblNoeuds[file.front()]->setMarque(1);

    while (this->tblNoeuds[file.front()]->capaciteSource < this->tblNoeuds[file.front()]->flotSource)
    {
        cout << "file.front() : " << file.front() << endl;
        // cout << "flotSource : " << this->tblNoeuds[file.front()]->flotSource << endl;
        // cout << "capaciteSource : " << this->tblNoeuds[file.front()]->capaciteSource << endl;
        // cout << "capacite < flot : " << (this->tblNoeuds[file.front()]->capaciteSource < this->tblNoeuds[file.front()]->flotSource) << endl;
        if (file.front() >= int(this->tblNoeuds.size() - 1))
        {
            return vector<pair<int, int>>();
        }
        int courant = file.front();
        cout << "courant : " << courant << endl;
        file.pop();
        file.push(courant+1);
    }
    // on marque le noeud parcouru
    vector<pair<int, int>> chemin;*/

/*
ParcoursLargeur(Graphe G, Sommet s):
   f = CreerFile();
   f.enfiler(s);
   marquer(s);
   tant que la file est non vide
            s = f.defiler();
            afficher(s);
            pour tout voisin t de s dans G
                     si t non marqué
                             f.enfiler(t);
                             marquer(t);
*/

/*while (!file.empty())
{
    Noeud *noeudCourant = this->tblNoeuds[file.front()];
    int noeudCourantPos = file.front();
    file.pop();
    noeudCourant->setMarque(2);
    if (noeudCourant->capacitePuit > noeudCourant->flotPuit)
    {
        chemin.push_back(make_pair(noeudCourantPos, tblNoeuds.size() + 1));
        cout << "file.front() : " << noeudCourantPos << endl;
        return chemin;
    }

    int j = 0;
    for (int i = 0; i < 4; i++)
    {
        if ((noeudCourant->getTblArc(i)->capacite > noeudCourant->getTblArc(i)->flot) && (this->tblNoeuds[noeudCourant->getTblArc(i)->valeur]->getMarque() == 0))
        {
            file.push(noeudCourant->getTblArc(i)->valeur);
            this->tblNoeuds[noeudCourant->getTblArc(i)->valeur]->setMarque(1);
        }
        else
        {
            j++;
        }
    }
    chemin.push_back(make_pair(noeudCourantPos, file.front()));
    if (j == 4)
    {
        chemin.pop_back();
        if (chemin.size() == 0)
        {
           file.push(noeudCourantPos + 1);
        }

    }
}

// on verifie si la capacité vers le puit est supérieure au flot
// si oui on retourne le chemin
// si non
// on verifie la capacitée vers le voisin
// si la capacité est supérieure au flot on ajoute le voisin à la file
// si non on passe au voisin suivant

// si le voisin n'est pas le puit on l'ajoute à la file
// si le voisin est le puit on retourne le chemin
return chemin;


*/

// on verifie que la capcaié de la source est bien supérieur au flot
// tant que la capacité de la source est inferieur au flot et que la valeur de la position globale du noeud d'entrée est inferieur à la taille du tableau de noeud
// on incrémente de 1 la valeur de la position globale du noeud d'entrée

// on a notre position globale du noeud d'entrée
// on peut commencer notre recherche de chemin
// on crée un vecteur de pair qui va contenir le chemin
// on crée la file qui va contenir les noeuds à visiter
// les noeuds vue sont marqués à 1
// les noeuds visités sont marqués à 2
// on ajoute le noeud d'entrée à la file

// tant que la file n'est pas vide
// on récupère le noeud en tête de file
// on le marque comme visité
// on verifie si la capacitePuit > flotPuit
// si oui on ajoute le noeud au chemin et on retourne le chemin
// sinon on ajoute les noeud voisins non vue et non visité à la file
// on les marque comme vue
// on ajoute le noeud au chemin
// fin de la boucle

// on retourne un vecteur vide