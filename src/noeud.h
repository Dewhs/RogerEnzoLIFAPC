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
    //si marque = 0, le noeud n'est pas visité
    //si marque = 1, le noeud est vue
    //si marque = 2, le noeud est visité
    int marque;

public:

    Noeud();                       // Constructeur par défaut
    Noeud(unsigned int intensite); // Construteur avec l'intensité en paramètre
    Noeud(unsigned int intensite, Arc* tabArc[4]); // Constructeur avec l'intensité et le tableau des voisin en parameter

    double capacitePuit, capaciteSource; // Capacité du puit et de la source
    double flotPuit, flotSource;         // Flot du puit et de la source

    unsigned int getIntensite() const; // Getter sur l'intensité
    void setIntensite(unsigned int intensite); // Setter sur l'intensité

    Arc *getTblArc(const unsigned int i); // Getter sur 1 élément du tableau

    void setTblArc(Arc *nouveauTbl[4]); // Setter sur le tableau

    void setMarque(int marque); // Setter sur la marque
    int getMarque() const; // Getter sur la marque

    ~Noeud(); // Destructeur
};

#endif // NOEUD_H
