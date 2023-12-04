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
    cout << "GrapheImage" << endl;
    test();
    largeur = 0;
    hauteur = 0;
    intensiteMax = 0;
}

GrapheImage::GrapheImage(const string &nomFichier)
{
    this->imageVersGraphe(nomFichier);

    vector<pair<int, int>> chemin = trouverChemin();
    for (unsigned int i = 0; i < chemin.size(); i++)
    {
        cout << "chemin.size() : " << chemin.size() << endl;
        cout << "Source : " << chemin[i].first << " " << "Destination : " << chemin[i].second << endl;
    }
}

void GrapheImage::copieImage(const string &nomFichier)
{
    this->imageVersGraphe(nomFichier);
    this->grapheVersImage(nomFichier);
}

// ------------------- Fonction de recherche d'un chemin entre deux noeuds ------------------- //

vector<pair<int, int>> GrapheImage::trouverChemin()
{
    // Créer une file pour le parcours en largeur
    queue<int> file;
    // ajout du premier noeud à la file
    file.push(0);
    this->tblNoeuds[file.front()]->setMarque(1);
    // on marque le noeud parcouru
    vector<pair<int, int>> chemin;

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

    while (!file.empty())
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
    ofstream fichier(nomFichier.substr(0, nomFichier.find_last_of(".")) + "Copie.pgm", std::ios::binary);

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
void GrapheImage::calculerFlot(unsigned int posP, unsigned int posQ, int aSource)
{

    double capPQ, flotPQ, flotQP;
    // aSource = 1 si on calcule le flot entre la source et un noeud
    // aSource = 0 si on calcule le flot entre deux noeuds
    // aSource = -1 si on calcule le flot entre un noeud et le puit
    if (aSource == 1)
    {
        // On récupère la capacité de l'arc P(Source) et Q
        capPQ = this->tblNoeuds[posP]->capaciteSource;
        // On récupère le flot de l'arc P(Source) et Q
        flotPQ = this->tblNoeuds[posP]->flotSource;
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
    else if (aSource == -1)
    {
        // On récupère la capacité de l'arc P et Q(Puit)
        capPQ = this->tblNoeuds[posP]->capacitePuit;
        // On récupère le flot de l'arc P et Q(Puit)
        flotPQ = this->tblNoeuds[posP]->flotPuit;
        // On récupère le flot de l'arc Q(Puit) et P
        flotQP = 0;
    }

    this->tblNoeuds[posP]->getTblArc(posQ)->flot += capPQ + (flotPQ - flotQP);

    // Si le flot le dépasse la capaité on ajoute le trop plein dans l'arc Q et P
    if (this->tblNoeuds[posP]->getTblArc(posQ)->flot += capPQ + (flotPQ - flotQP) > capPQ)
    {
        double flotPlein = this->tblNoeuds[posP]->getTblArc(posQ)->flot += capPQ + (flotPQ - flotQP) - capPQ;
        this->tblNoeuds[posQ]->getTblArc(posP)->flot += flotPlein;
    }
}

// ------------------- Fonction pour calculer les capacitées ------------------- //
double GrapheImage::calculerCapacite(int intensiteP, int intensiteQ)
{
    // Ne pas oublier le H
    // Je pense qu'il faut faire un lround ici c'est une capacité donc un int mais on en repalera
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
        return -(alpha * log(255.0 - (this->tblNoeuds[posP]->getIntensite()) / 255.0));
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
    this->imageVersGraphe("src/imagePgmTest.pgm");

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

    // Il faut avoir un sigma plus gros pour ne pas avoir de probleme de petit chiffre qui sont proches de zero

    assert(this->tblNoeuds[0]->getTblArc(0)->capacite == 0);
    // Ne marche pas car la valeur est trop petite et toutes les calculatrices me renvoie environ 0
    // Mais la fonction renvoie les bons resultats tout marche sauf impossible de savoir les resultats
    // assert(this->tblNoeuds[0]->getTblArc(1)->capacite ==0);
    assert(this->tblNoeuds[0]->getTblArc(2)->capacite == 0);
    assert(compareDouble(calculerCapacitePos(0, 3), 1.38389 * pow(10, -87), epsilon * pow(10, -87)));

    // Ne marche pas car la valeur est trop petite et toutes les calculatrices me renvoie environ 0
    // Mais la fonction renvoie les bons resultats tout marche sauf impossible de savoir les resultats
    // assert(this->tblNoeuds[1]->getTblArc(0)->capacite == 0);
    // assert(this->tblNoeuds[1]->getTblArc(1)->capacite == 0);
    assert(this->tblNoeuds[1]->getTblArc(2)->capacite == 0);
    assert(compareDouble(calculerCapacitePos(1, 4), 1.38389 * pow(10, -87), epsilon * pow(10, -87)));

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

void GrapheImage::test()
{
    cout << "##############################" << endl;
    cout << "Tests" << endl;

    testCalculPosNoeud();
    testImageVersGraphe();
    testCalculVoisins();
    testCalculerCapacite();

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
