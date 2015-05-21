//
//  Matrix.h
//  project
//
//  Created by Bartek on 20.05.2015.
//  Copyright (c) 2015 Bartek. All rights reserved.
//

#include <stdio.h>
#include <string>
#include "Vector.h"

using namespace std;

#ifndef __project__Matrix__
#define __project__Matrix__

class Matrix
    : public Vector
{
public:
    int rows, columns;
public:
    Matrix(int r, int c);
    string get_size();
    int read_size(ifstream&);
    
};
#endif /* defined(__project__Matrix__) */
