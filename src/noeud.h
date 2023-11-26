

struct Arc
{
    Arc(){valeur = 0; flot = 0; capacite = 0;};
    unsigned int valeur;
    double flot, capacite;
};

#ifndef NOEUD_H
#define NOEUD_H

class Noeud
{
private:
    // intensité lumineuse
    unsigned int intensite;

    // valuation des 4 arcs (Ouest ,Est ,Nord ,Sud)
    Arc tblArc[4];
    Arc s, p;

public:
    Noeud();
    Noeud(unsigned int intensite);

    unsigned int getIntensite();
    Arc* getTblArc();

    ~Noeud();
};

#endif // NOEUD_H
