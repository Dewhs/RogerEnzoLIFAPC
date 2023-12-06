#include <iostream>
#include "graphe.h"

using namespace std;



int main(int argc, char const *argv[])
{


    cout << "Test du service en cours" << endl;
    GrapheImage g;
    // g.~GrapheImage();
    cout << "Test du service terminer" << endl << endl;

    string nomFichierImageNonBinariser; 
    cout << "Entrez le nom de votre image : ";
    cin >> nomFichierImageNonBinariser;
    cout << "Vous avez decider de binariser cette image : " << nomFichierImageNonBinariser << endl;

    cout << "Processus en cours" << endl;
    GrapheImage grapheBin(nomFichierImageNonBinariser);
    cout << "Processus terminer !" << endl;
    // grapheBin.~GrapheImage();

    return 0;
}