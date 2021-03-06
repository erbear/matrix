//
//  DiagonalMatrix.cpp
//  project
//
//  Created by Bartek on 21.05.2015.
//  Copyright (c) 2015 Bartek. All rights reserved.
//

#include "DiagonalMatrix.h"
#include "Vector.h"
#include <vector>
DiagonalMatrix::DiagonalMatrix(Matrix m)
:Matrix(0,0)
{
    this->compress(m);
}

void DiagonalMatrix::compress(Matrix &matrix){
    int size = 0;
    std::vector<int> rowsSize;
    for (int i = 0; i<matrix.rows; i++)
    {
        int beta = 0;
        bool saveTrigger = false;
        for (int i2 = 0; i2<i+1; i2++) {
            int currentNumber = matrix.vector[i*matrix.columns+i2];
            if (currentNumber > 0 && !saveTrigger)
            {
                saveTrigger = true;
                beta = i - i2;
                rowsSize.push_back(beta);
                if (beta > size)
                    size = beta;
            }
            if (saveTrigger)
                this->vector.push_back(currentNumber);
        }
    }
    int iteration = 0;
    for (int i=rowsSize.size()-1; i>=0; i--){
        while (rowsSize[i] < size) {
            this->vector.insert(this->vector.end()-((size+1)*iteration+(rowsSize[i]+1)),0);
            rowsSize[i]++;
        }
        iteration++;
    }
    this->columns = size + 1;
    this->rows = rowsSize.size();
}

Vector DiagonalMatrix::multiplyBy(Vector &v){
    Vector result(this->rows);
    
    for (int row = 0; row<this->rows; row++) {
        int positionInMatrix = row,
        numberOfColumns = this->columns - 1;
        
        for (int column = numberOfColumns; column>=0; column--) {
            if (positionInMatrix>=0){
                if (column<numberOfColumns){
                    result.vector[row] += v.vector[positionInMatrix] * this->vector[row*this->columns + column];
                    result.vector[positionInMatrix] += v.vector[row] * this->vector[row*this->columns + column];
                }
                else {
                    result.vector[row] += v.vector[positionInMatrix] * this->vector[row*this->columns + column];
                }
                positionInMatrix--;
            }
        }
    }

    return result;
}