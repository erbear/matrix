//
//  Vector.cpp
//  project
//
//  Created by Bartek on 20.05.2015.
//  Copyright (c) 2015 Bartek. All rights reserved.
//

#include "Vector.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

Vector::Vector(int size){
    this->size = size;
}

string Vector::get_size(){
    return to_string(this->size);
}

int Vector::read_size(ifstream &plik){
    int size;
    plik >> size;
    return size;
}

void Vector::generate(){
    this->vector.clear();
    
    double n = 0;
    
    srand( time( NULL ) );
    
    for (int i = 0; i < this->size; i++){
        n =( rand() /( static_cast < double >( RAND_MAX ) + 1 ) ) *(10.5 - 5.25 ) - 1.25;
        this->vector.push_back(n);
    }
}

void Vector::save(char *name){
    fstream plik;
    
    plik.open(name, ios::out);
    if( plik.good() == true ){
        plik << get_size()<<" "<<endl;
        for (int i = 0; i < this->vector.size(); i++){
            plik << this->vector[i]<<" "<<endl;
        }
        plik.close();
    }
}


void Vector::read(char *name){
    ifstream plik;
    this->vector.clear();
    double number = 0.0;
    int size = 0;
    
    plik.open(name, ios::in);
    if( plik.good() == true ){
        size = read_size(plik);
        for (int i = 0; i < size; i++){
            plik >> number;
            this->vector.push_back(number);
            number = 0;
        }
        plik.close();
    }
}
