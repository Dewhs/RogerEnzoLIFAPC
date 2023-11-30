struct Arc
{
    // Constructeur prenant des valeurs initiales en paramètres
    Arc(unsigned int valeur = 0, double flot = 0.0, double capacite = 0.0)
        : valeur(valeur), flot(flot), capacite(capacite) {}

    // Surcharge de l'opérateur '='
    Arc &operator=(const Arc &autre);

    // Destructeur
    ~Arc();

    // Données-membres
    unsigned int valeur;
    double flot, capacite;
};

#ifndef NOEUD_H
#define NOEUD_H

class Noeud
{

private:
    // Données-membres
    Arc *tblArc[4];
    unsigned int intensite;

public:

    Noeud();                       // Constructeur par défaut
    Noeud(unsigned int intensite); // Construteur avec l'intensité en paramètre
    Noeud(unsigned int intensite, Arc* tabArc[4]); // Constructeur avec l'intensité et le tableau des voisin en parameter

    unsigned int getIntensite() const; // Getter sur l'intensité

    Arc *getTblArc(const unsigned int i); // Getter sur 1 élément du tableau

    void setTblArc(Arc *nouveauTbl[4]); // Setter sur le tableau

    ~Noeud(); // Destructeur
};

#endif // NOEUD_H
