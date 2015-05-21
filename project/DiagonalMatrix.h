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
#include "Vector.h"

class DiagonalMatrix
: public Matrix
{
public:
    DiagonalMatrix(Matrix);
    
    void compress(Matrix&);
    Vector multiplyBy(Vector&);
    
};

#endif /* defined(__project__DiagonalMatrix__) */
