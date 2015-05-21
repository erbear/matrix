//
//  DiagonalMatrix.h
//  project
//
//  Created by Bartek on 21.05.2015.
//  Copyright (c) 2015 Bartek. All rights reserved.
//

#ifndef __project__DiagonalMatrix__
#define __project__DiagonalMatrix__

#include <stdio.h>
#include "Matrix.h"

class DiagonalMatrix
: public Matrix
{
public:
    DiagonalMatrix(Matrix m)
    :Matrix(0,0)
    {
        this->compress(m);
    }
    
    void compress(Matrix);
    
};

#endif /* defined(__project__DiagonalMatrix__) */
