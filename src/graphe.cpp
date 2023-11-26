#include "graphe.h"
#include <iostream>
#include <cassert>
#include <cmath>

bool GrapheImage::compareDouble(double a, double b, double epsilon)
{
    return fabs(a - b) < epsilon;
}

GrapheImage::GrapheImage()
{
    cout << "GrapheImage" << endl;
    test();
}

void GrapheImage::test()
{
    const unsigned int testSize = 9;
    const double epsilon = 0.00001;

    int intensites[testSize] = {248, 234, 0, 221, 248, 77, 234, 51, 51};
    tblNoeuds.resize(testSize);
    for (unsigned int i = 0; i < testSize; i++)
    {
        tblNoeuds[i] = new Noeud(intensites[i]);
    }

    assert(compareDouble(calculerCapacite(0, 1), 2.74879 * pow(10, -43), epsilon));
    cout << "[OK] [0,0] [1,0]" << endl;
    assert(compareDouble(calculerCapacite(0, 3), 5.00797 * pow(10, -159), epsilon));
    cout << "[OK] [0,0] [0,1]" << endl;
    assert(compareDouble(calculerCapacite(1, 2), 0, epsilon));
    cout << "[OK] [1,0] [2,0]" << endl;
    assert(compareDouble(calculerCapacite(1, 4), 2.74879 * pow(10, -43), epsilon));
    cout << "[OK] [1,0] [1,1]" << endl;
    assert(compareDouble(calculerCapacite(2, 5), 0, epsilon));
    cout << "[OK] [2,0] [2,1]" << endl;
    assert(compareDouble(calculerCapacite(3, 4), 5.00797 * pow(10, -159), epsilon));
    cout << "[OK] [0,1] [1,1]" << endl;
    assert(compareDouble(calculerCapacite(3, 6), 2.00501 * pow(10, -37), epsilon));
    cout << "[OK] [0,1] [0,2]" << endl;
    assert(compareDouble(calculerCapacite(4, 5), 0, epsilon));
    cout << "[OK] [1,1] [2,1]" << endl;
    assert(compareDouble(calculerCapacite(4, 7), 0, epsilon));
    cout << "[OK] [1,1] [1,2]" << endl;
    assert(compareDouble(calculerCapacite(5, 8), 1.61609 * pow(10, -147), epsilon));
    cout << "[OK] [2,1] [2,2]" << endl;
    assert(compareDouble(calculerCapacite(6, 7), 0, epsilon));
    cout << "[OK] [0,2] [1,2]" << endl;
    assert(compareDouble(calculerCapacite(7, 8), 1, epsilon));
    cout << "[OK] [1,2] [2,2]" << endl;

    tblNoeuds.clear();

    cout << "##############################" << endl;
    cout << "[OK] All test passed !" << endl;
}

double GrapheImage::calculerCapacite(int posP, int posQ)
{
    int sigma = 1;
    int intensiteP = tblNoeuds[posP]->getIntensite();
    int intensiteQ = tblNoeuds[posQ]->getIntensite();

    double capacite = exp(-pow(intensiteP - intensiteQ, 2) / (2 * pow(sigma, 2)));

    // cout << "capacite : " << capacite << endl;
    return capacite;
}

GrapheImage::~GrapheImage()
{
    cout << "~GrapheImage" << endl;
}