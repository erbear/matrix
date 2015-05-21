//
//  Matrix.cpp
//  project
//
//  Created by Bartek on 20.05.2015.
//  Copyright (c) 2015 Bartek. All rights reserved.
//

#include "Matrix.h"
#include <iostream>
#include <fstream>

Matrix::Matrix(int r, int c)
:Vector(r*c)
{
    this->rows = r;
    this->columns = c;
}

string Matrix::get_size(){
    string size;
    size = to_string(this->rows) + " " + to_string(this->columns);
    std::cout << size;
    return size;
}

int Matrix::read_size(ifstream &plik){
    int rws, cols;
    plik >> rws >> cols;
    return rws * cols;
}