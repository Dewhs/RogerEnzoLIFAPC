#include "noeud.h"
#include <iostream>
using namespace std;

Arc::~Arc(){
    cout << "Arc detruit" << endl;
}

Noeud::Noeud() {
    this->intensite = 0;
    // Allocation dynamique d'un tableau d'Arc avec 4 éléments
    for (int i = 0; i < 4; ++i) {
        tblArc[i] = new Arc();
    }
}

Noeud::Noeud(unsigned int intensite){
    this->intensite = intensite;
    // Allocation dynamique d'un tableau d'Arc avec 4 éléments
    for (int i = 0; i < 4; ++i) {
        tblArc[i] = new Arc();
    }
}

Noeud::~Noeud() {
    this->intensite = 0;
    // Libération de la mémoire allouée pour chaque élément du tableau tblArc
    for (int i = 0; i < 4; ++i) {
        delete tblArc[i];
        tblArc[i] = nullptr;
    }
}

unsigned int Noeud::getIntensite() const
{
    return intensite;
}

Arc*& Noeud::getTblArc()
{
    return *tblArc;
}

void Noeud::setTblArc(Arc* nouveauTbl[4]) {
    for (int i = 0; i < 4; ++i) {
        // Vérification que chaque élément du nouveau tableau n'est pas nul avant de le copier
        if (nouveauTbl[i] != nullptr) {
            // Si un nouvel arc est valide, copie de ses valeurs dans le tableau tblArc
            if (tblArc[i] == nullptr) {
                tblArc[i] = new Arc(); // Allouer de la mémoire si l'arc actuel est nul
            }
            // Copie des valeurs de l'arc dans tblArc
            tblArc[i]->valeur = nouveauTbl[i]->valeur;
            tblArc[i]->flot = nouveauTbl[i]->flot;
            tblArc[i]->capacite = nouveauTbl[i]->capacite;
        }
    }
    // Suppression du tableau nouveauTbl après le traitement
    for (int i = 0; i < 4; ++i) {
        delete nouveauTbl[i];
    }
}
