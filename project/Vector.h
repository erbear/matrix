//
//  Vector.h
//  project
//
//  Created by Bartek on 20.05.2015.
//  Copyright (c) 2015 Bartek. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <iostream>

#ifndef __project__Vector__
#define __project__Vector

using namespace std;

class Vector {
public:
    vector<double> vector;
    
public:
    void generate(int);
    void save(char*);
    void read(char *s);
    void get();
};


#endif /* defined(__project__Vector__) */