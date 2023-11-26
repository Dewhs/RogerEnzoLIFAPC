struct Arc
{
    Arc() : valeur(0), flot(0), capacite(0) {} // Initialisation des membres dans le constructeur
    unsigned int valeur;
    double flot, capacite;
};

#ifndef NOEUD_H
#define NOEUD_H

class Noeud
{
private:
    unsigned int intensite;
    Arc* tblArc[4]; 

public:
    Noeud(); // Constructeur par défaut
    Noeud(unsigned int intensite);

    unsigned int getIntensite() const; // Getter sur l'intensité
    Arc*& getTblArc(); // Getter sur le tableau
    void setTblArc(const Arc* nouveauTbl[4]); // Setter sur le tableau

    ~Noeud(); // Destructeur
};

#endif // NOEUD_H
