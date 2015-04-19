//
//  Matrix.cpp
//  project
//
//  Created by Bartek on 19.04.2015.
//  Copyright (c) 2015 Bartek. All rights reserved.
//

#include "Matrix.h"
#include <fstream>
#include <iostream>

using namespace std;

Matrix::Matrix()
{
    return;
}

void Matrix::generateMatrix()
{
    
}

void Matrix::loadMatrix()
{
    //opening file
    ifstream plik;
    
    plik.open("matrix.txt");
    
    if (!plik.good())
        return;
    
    
    //Reading from file
    int columns, rows, liczba;
    int numberInRow;
    
    plik >> columns >> rows;
    
    while (true){
        numberInRow++;
        plik >> liczba;
        
        if (plik.good())
            cout << liczba;
        else
            break;
        
        if (numberInRow == columns){
            numberInRow = 0;
            cout << endl;
        }
        else
            cout << " ";
        
    }
    
}

bool Matrix::isSymmetric()
{
    return true;
}

bool Matrix::isTriangular()
{
    return true;
}