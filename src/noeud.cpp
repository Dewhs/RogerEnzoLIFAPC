#include "noeud.h"
#include <iostream>
using namespace std;

Arc &Arc::operator=(const Arc &autre)
{
    // Vérification pour éviter l'auto-affectation
    if (this != &autre)
    {
        valeur = autre.valeur;
        flot = autre.flot;
        capacite = autre.capacite;
    }
    return *this;
}

Arc::~Arc()
{
    this->capacite = 0;
    this->flot = 0;
    this->valeur = 0;
    // cout << "Destructeur Arc" << endl;
}

Noeud::Noeud()
{
    this->intensite = 0;
    // Allocation dynamique d'un tableau d'Arc avec 4 éléments
    for (int i = 0; i < 4; ++i)
    {
        tblArc[i] = new Arc();
    }
}

Noeud::Noeud(unsigned int intensite)
{
    this->intensite = intensite;
    // Allocation dynamique d'un tableau d'Arc avec 4 éléments
    for (int i = 0; i < 4; ++i)
    {
        this->tblArc[i] = new Arc();
    }
}

Noeud::Noeud(unsigned int intensite, Arc* tabArc[4])
{
    this->intensite = intensite;
    for(unsigned int i = 0; i < 4; i++){
        this->tblArc[i] = tabArc[i];
    }
}

Noeud::~Noeud()
{
    this->intensite = 0;
    // Libération de la mémoire allouée pour chaque élément du tableau tblArc
    for (int i = 0; i < 4; ++i)
    {
        delete tblArc[i];
        tblArc[i] = nullptr;
    }
    // cout << "Destructeur Noeud" << endl;
}

unsigned int Noeud::getIntensite() const
{
    return intensite;
}

void Noeud::setIntensite(unsigned int intensite)
{
    this->intensite = intensite;
}

Arc *Noeud::getTblArc(const unsigned int i)
{
    return tblArc[i];
}

void Noeud::setTblArc(Arc *nouveauTbl[4])
{
    for (int i = 0; i < 4; ++i)
    {
        this->tblArc[i]->valeur = nouveauTbl[i]->valeur;
    }
}


void Noeud::setMarque(int marque)
{
    this->marque = marque;
}

int Noeud::getMarque() const
{
    return marque;
}


