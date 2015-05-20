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

using namespace std;

class Vector {
    vector<double> vector;
    
public:
    void generate(int);
    void save(char*);
    void read(char *s);
    void get();
};