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
        case 3: st = "matrix3.txt";
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

char * menuVector() {
    int n;
    char * vt;
    cout<<"Wybierz wektor do mnozenia"<<endl;
        cout<<"1. Wektor 1"<<endl;
        cout<<"2. Wektor 2"<<endl;
    cin>>n;

    switch(n){
        case 1: vt = "vecto.txt";
        break;
        case 2: vt = "vector.txt";
        break;
        default: vt = "vector.txt";
        break;
    }
    return vt;
}
/*
char * menuVector2(){
    char * s;

    cout<<"\n Podaj nazwe wektora do zapisu: "<<endl;
    cin>>s;

    return s;

}
*/

int main(int argc, const char * argv[]) {

    int n = 0, k = 0;
    //char * st = Menu();
    char * vt;
    char * vt2;
    Matrix m;

    //m.loadMatrix(st);
    m.loadMatrix("matrix2.txt");

    m.generateNewVector();

    m.modifiedSparseCompression();

    m.multiplicationModifiedSparseCompression();



    //m.coordinatesCompression();

    //m.multiplicationCoordinatesCompression();

    /*cout<<"Wybierz wektor do mnozenia"<<endl;
        cout<<"1. Wygeneruj nowy wektor"<<endl;
        cout<<"2. Wczytaj utworzony wektor"<<endl;
    cin>>k;

    switch(k){
        case 1:
            //vt2 = menuVector2();
            m.generateNewVector();
        break;
        case 2:
            vt = menuVector();
            m.readVector(vt);
        break;
        default:
            vt = menuVector();
            m.readVector(vt);
        break;
    }
/*
    cout<<"\nWybierz metode do formatowania"<<endl;
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

    */
}
