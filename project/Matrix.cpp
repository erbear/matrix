#include "Matrix.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void Matrix::loadMatrix(char * s) {
    //opening file
    ifstream plik;

    plik.open(s);

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
            this->matrix.push_back(number);
        }
        else
            break;

        if (numberInRow == columns){
            numberInRow = 0;
        }

    }
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

void Matrix::modifiedSparseCompression(){
    vector <int> AN, IN, JA, IN2;

    for (int i = 0; i<this->rows; i++){
        for (int i2=0; i2<this->columns; i2++){
            int currentNumber = this->matrix[i*this->columns+i2];
            if (currentNumber != 0) {
                AN.push_back(currentNumber);
                IN.push_back(i);
                JA.push_back(i2);
            }
        }
    }

    sort( IN.begin(), IN.end() );
    IN.erase(unique(IN.begin(), IN.end()), IN.end());

    makeEmptyCheckMatrix();
    int inIndex = 0, jaIndex = 0, anIndex = 0;

    for (int i = 0; i<this->rows; i++){
        for (int i2=0; i2<this->columns; i2++){
            if((i == IN[inIndex]) && (i2 == JA[jaIndex])){
                checkMatrix[i*this->columns+i2]=AN[anIndex];
                jaIndex++;
                anIndex++;
            }
            if (i2 == this->columns - 1 && i == IN[inIndex])
                inIndex++;
        }
    }
    checkTwoMatrices();
}

void Matrix::coordinatesCompression(){
    vector <int> AN, IN, JA;

    for (int i = 0; i<this->rows; i++){
        for (int i2=0; i2<this->columns; i2++){
            int currentNumber = this->matrix[i*this->columns+i2];
            if (currentNumber != 0) {
                AN.push_back(currentNumber);
                IN.push_back(i);
                JA.push_back(i2);
            }
        }
    }

    makeEmptyCheckMatrix();
    int inIndex = 0, jaIndex = 0, anIndex = 0;

    for (int i = 0; i<this->rows; i++){
        for (int i2=0; i2<this->columns; i2++){
            if((i == IN[inIndex]) && (i2 == JA[jaIndex])){
                checkMatrix[i*this->columns+i2]=AN[anIndex];
                inIndex++;
                jaIndex++;
                anIndex++;
            }
        }
    }
    checkTwoMatrices();
}

void Matrix::makeEmptyCheckMatrix(){
    checkMatrix.clear();

    for (int i = 0; i<this->rows * this->columns; i++){
        checkMatrix.push_back(0);
    }
}

void Matrix::checkTwoMatrices() const {
    int count = 0;

    for (int i = 0; i<matrix.size(); i++){
        if(matrix[i]!=checkMatrix[i]){
            count++;
        }
    }

    cout<<endl;
    if (count==0) {
        cout<<"Macierze nie roznia sie!";
    }
    else {
        cout<<"Macierze roznia sie w "<<count<<" miejscach!";
    }
}
