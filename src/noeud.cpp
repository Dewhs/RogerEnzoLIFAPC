#include "noeud.h"

Noeud::Noeud()
{
}

Noeud::Noeud(unsigned int intensite)
{
    this->intensite = intensite;
}


unsigned int Noeud::getIntensite()
{
    return intensite;
}

Noeud::~Noeud()
{
}