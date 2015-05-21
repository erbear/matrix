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
#include <string>

#ifndef __project__Vector__
#define __project__Vector__

using namespace std;

class Vector {
public:
    vector<double> vector;
    int size;
    
public:
    Vector(int);
    void generate();
    void save(char*);
    void read(char *s);
    virtual string get_size();
    virtual int read_size(ifstream& plik);
    void get();
};


#endif /* defined(__project__Vector__) */