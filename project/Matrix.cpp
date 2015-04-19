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
    int columns, rows, number;
    int numberInRow;
    vector<int> row;
    
    plik >> columns >> rows;
    
    this->columns = columns;
    this->rows = rows;
    
    while (true){
        numberInRow++;
        plik >> number;
        
        if (plik.good()){
            cout << number;
            row.push_back(number);
        }
        else
            break;
        
        if (numberInRow == columns){
            numberInRow = 0;
            this->matrix.push_back(row);
            row.clear();
            cout << endl;
        }
        else
            cout << " ";
        
    }
    
}

void Matrix::compress()
{
    
}
void Matrix::compressToCoat()
{
    vector<int> an, ia;
    
    for (int i = 0; i<this->rows; i++)
    {
        bool startReading = false;
        
        
        for (int i2=0; i2<i+1; i2++){
            if (this->matrix[i][i2] != 0 || startReading == true){
                startReading = true;
                an.push_back(this->matrix[i][i2]);
            }
        }
        ia.push_back(static_cast<int>(an.size()));
    }
    
//    check
//    
//    for (int i=0; i<an.size(); i++) {
//        cout << an[i] << " ";
//    }
//    cout << endl;
//    for (int i=0; i<ia.size(); i++) {
//        cout << ia[i] << " ";
//    }
    
}


bool Matrix::isSymmetric()
{
    return true;
}

bool Matrix::isTriangular()
{
    return true;
}
