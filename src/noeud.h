

struct Arc
{
    unsigned int flot, capacite, valeur;
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
    ~Noeud();
};

#endif // NOEUD_H
