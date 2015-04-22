//
//  Martix.h
//  AK2
//
//  Created by Bartek on 19.04.2015.
//  Copyright (c) 2015 Bartek. All rights reserved.
//

#include <vector>

using namespace std;

//Potrzebuje:

//wczytanie/wygenerowanie macierzy

//sprawdzenie czy macierz jest symetryczna

//sprawdzanie czy jest trojkatna

//vektor ktory trzyma macierz

//tablice ktore beda przechowywaly dane

//rozmar column, row



class Matrix
{
    int columns, rows;
    vector < int > matrix;
    vector < vector < int >> compressed;
    
public:
    Matrix();
    
    void generateMatrix();
    void loadMatrix();
    bool isSymmetric();
    bool isTriangular();
    void compress();
    void coatCompression();//Schemat powłokowy
    void diagonalUnzip();
    void diagonalCompression();//Kompresja Shermana
    
};