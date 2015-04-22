#include <iostream>
#include "Matrix.h"

using namespace std;

char * Menu(){
    int n;
    char * st;
        cout<<"Wybierz macierz do formatowania"<<endl;
        cout<<"1. Macierz 1"<<endl;
        cout<<"2. Macierz 2"<<endl;
        cout<<"3. Macierz 3"<<endl;
        cout<<"4. Macierz 4"<<endl;
        cout<<"5. Macierz 5"<<endl;
    cin>>n;

    switch(n){
        case 1: st = "matrix.txt";
        break;
        case 2: st = "matrix2.txt";
        break;
        case 3: st = "matrix.txt";
        break;
        case 4: st = "matrix.txt";
        break;
        case 5: st = "matrix.txt";
        break;
        default: st = "matrix.txt";
        break;
    }
    return st;
}

int main(int argc, const char * argv[]) {

    int n = 0;
    char * st = Menu();
    Matrix m;

    m.loadMatrix(st);

    cout<<"Wybierz metode do formatowania"<<endl;
        cout<<"1. Metoda Wspolrzednych"<<endl;
        cout<<"2. Metoda Diagonalna"<<endl;
        cout<<"3. Metoda Rozrzedzona wierszowa"<<endl;
        cout<<"4. Metoda Powlokowa"<<endl;
    cin>>n;

    switch(n){
        case 1: m.coordinatesCompression();
        break;
        case 2: m.diagonalCompression();
        break;
        case 3: m.modifiedSparseCompression();
        break;
        case 4: m.coatCompression();
        break;
        default: m.coordinatesCompression();
        break;
    }
}
