//
//  main.cpp
//  project
//
//  Created by Bartek on 19.04.2015.
//  Copyright (c) 2015 Bartek. All rights reserved.
//

#include <iostream>
#include "Matrix.h"

using namespace std;
int main(int argc, const char * argv[]) {
    
    Matrix m;
    vector<int> one, two;
    
    m.loadMatrix();
    m.diagonalCompression();
    m.diagonalUnzip();
    
}
