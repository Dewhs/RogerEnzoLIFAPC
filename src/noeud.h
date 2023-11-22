

struct Arc
{
    unsigned int flot, capacite, valeur;
};

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
