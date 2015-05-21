//
//  Matrix.cpp
//  project
//
//  Created by Bartek on 20.05.2015.
//  Copyright (c) 2015 Bartek. All rights reserved.
//

#include "Matrix.h"
#include <vector>
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
    return size;
}

void Matrix::read_mtx(char *name){
    // Open the file:
    ifstream plik;
    plik.open(name);
    
    // Declare variables:
    int M, N, L;
    std::vector<double> matrix;
    
    // Ignore headers and comments:
    while (plik.peek() == '%') plik.ignore(2048, '\n');
    
    // Read defining parameters:
    plik >> M >> N >> L;
    
    //    cout << M << " " << N << " " << L << " ";
    
    // Create your matrix:
    for(int i = 0; i < M*N; i++){
        matrix.push_back(0);
    }
    
    // Read the data
    for (int l = 0; l < L; l++)
    {
        int m, n;
        double data;
        plik >> m >> n >> data;
        matrix[(m-1) + (n-1)*M] = data;
    }
    
    plik.close();
    
    this->columns = M;
    this->rows = N;
    this->vector = matrix;
    


}

int Matrix::read_size(ifstream &plik){
    int rws, cols;
    plik >> rws >> cols;
    return rws * cols;
}
