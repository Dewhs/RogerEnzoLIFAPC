struct Arc {
    // Constructeur prenant des valeurs initiales en paramètres
    Arc(double valeur = 0, double flot = 0.0, double capacite = 0.0)
        : valeur(valeur), flot(flot), capacite(capacite) {}

    // Surcharge de l'opérateur '='
    Arc& operator=(const Arc& autre);

    //Destructeur
    ~Arc();

    //Données-membres
    double valeur, flot, capacite;
};

#ifndef NOEUD_H
#define NOEUD_H

class Noeud
{

private:
    //Données-membres
    unsigned int intensite;
    Arc* tblArc[4]; 

public:

    Noeud(); // Constructeur par défaut
    Noeud(unsigned int intensite); // Construteur avec l'intensité en paramètre

    unsigned int getIntensite() const; // Getter sur l'intensité

    Arc*& getTblArc(); // Getter sur le tableau

    void setTblArc(Arc* nouveauTbl[4]); // Setter sur le tableau

    ~Noeud(); // Destructeur
};

#endif // NOEUD_H
