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
    
    plik >> columns >> rows;
    
    this->columns = columns;
    this->rows = rows;
    
    while (true){
        numberInRow++;
        plik >> number;
        
        if (plik.good()){
            cout << number;
            this->matrix.push_back(number);
        }
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

void Matrix::compress()
{
    
}
void Matrix::coatCompression()
{
    vector<int> an, ia;
    
    for (int i = 0; i<this->rows; i++)
    {
        bool startReading = false;
        
        
        for (int i2=0; i2<i+1; i2++){
            if (this->matrix[i*this->columns+i2] != 0 || startReading == true){
                startReading = true;
                an.push_back(this->matrix[i*this->columns+i2]);
            }
        }
        ia.push_back(static_cast<int>(an.size()));
    }
    
    this->compressed.push_back(an);
    this->compressed.push_back(ia);
    
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
void Matrix::diagonalCompression()
{
    int size = 0;
    vector<int> row;
    for (int i = 0; i<this->rows; i++)
    {
        int beta = 0;
        bool trigger = false;
        for (int i2 = 0; i2<i+1; i2++) {
            int currentNumber = this->matrix[i*this->columns+i2];
            if (currentNumber > 0)
            {
                trigger = true;
                beta = i - i2;
                if (beta > size)
                    size = beta;
            }
            if (trigger)
                row.push_back(currentNumber);
        }
        this->compressed.push_back(row);
        row.clear();
    }

    for (int i=0; i<this->compressed.size(); i++) {
        while (this->compressed[i].size()<size+1)
            this->compressed[i].insert(this->compressed[i].begin(), 0);
    }
    
//    check
//    for (int i=0; i<this->compressed.size(); i++) {
//        for (int i2=0; i2<this->compressed[i].size(); i2++) {
//            cout << this->compressed[i][i2] << " ";
//        }
//        cout << endl;
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
