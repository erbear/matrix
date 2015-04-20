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
    
    plik.open("sherman.txt");
    
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
void Matrix::shermanCompression(){
    vector<int> ad, an, ia, ja, ij, jaSlice;
    int iaCounter = 1;
    
    ia.push_back(iaCounter);//start from diagonal first element
    
    for (int i = 0; i<this->rows; i++)
    {
        for (int i2 = i; i2<this->columns; i2++) {
            int element = this->matrix[i*this->columns+i2];
            if (i2 == i)
                ad.push_back(element);
            else if (element != 0){
                an.push_back(element);
                jaSlice.push_back(i2+1);
                iaCounter++;
            }
        }
        int position = this->checkReccurance(ja, jaSlice);
        
        if (position == -1){
            ij.push_back(static_cast<int>(ja.size())+1);
            ja.insert(ja.end(), jaSlice.begin(), jaSlice.end());
        } else
            ij.push_back(position+1);
        jaSlice.clear();
        ia.push_back(iaCounter);
    }
    
    for (int i=0; i<ad.size(); i++) {
        cout << ad[i] << " ";
    }
    cout << endl;
    for (int i=0; i<an.size(); i++) {
        cout << an[i] << " ";
    }
    cout << endl;
    for (int i=0; i<ia.size(); i++) {
        cout << ia[i] << " ";
    }
    cout << endl;
    for (int i=0; i<ja.size(); i++) {
        cout << ja[i] << " ";
    }
    cout << endl;
    for (int i=0; i<ij.size(); i++) {
        cout << ij[i] << " ";
    }
}
int Matrix::checkReccurance(vector<int>& cake, vector<int>& slice){
    int numberOfPasses = 0,
        position = -1;
    for (int i = 0; i<cake.size(); i++){
        if (cake[i] == slice[numberOfPasses] && numberOfPasses < slice.size())
            numberOfPasses++;
        else {
            numberOfPasses = 0;
            position = i+1;
        }
        if (numberOfPasses == slice.size())
            return position;
    }
    return -1;
}

bool Matrix::isSymmetric()
{
    return true;
}

bool Matrix::isTriangular()
{
    return true;
}
