#include <iostream>
#include "Matrix2.h"
#include <chrono>
#include "Vector.h"
#include "Matrix.h"
#include "DiagonalMatrix.h"

using namespace std;

char * Menu()
{
    int n;
    char * st;
    cout<<"Wybierz macierz do formatowania"<<endl;
    cout<<"1. Macierz 1"<<endl;
    cout<<"2. Macierz 2"<<endl;
    cout<<"3. Macierz 3"<<endl;
    cout<<"4. Macierz 4"<<endl;
    cout<<"5. Macierz 5"<<endl;
    cin>>n;

    switch(n)
    {
    case 1:
        st = "bcsstk27.mtx";
        break;
    case 2:
        st = "bcsstk28.mtx";
        break;
    case 3:
        st = "bcsstm13.mtx";
        break;
    case 4:
        st = "dwt___59.mtx";
        break;
    case 5:
        st = "matrix5.txt";
        break;
    default:
        st = "matrix.txt";
        break;
    }
    return st;
}

char * menuVector()
{
    int n;
    char * vt;
    cout<<"Wybierz wektor do mnozenia"<<endl;
    cout<<"1. Wektor new_vector"<<endl;
    cout<<"2. Wektor 2"<<endl;
    cin>>n;

    switch(n) {
    case 1:
        vt = "new_vector.txt";
        break;
    case 2:
        vt = "vector.txt";
        break;
    default:
        vt = "vector.txt";
        break;
    }
    return vt;
}


int main(int argc, const char * argv[]) {
    Vector v(7);
    v.generate();
    v.read("vec.txt");
    Matrix m(0, 0);
    m.read("matrix.txt");
    Vector result = m.multiplyBy(v);
    result.save("result.txt");
    DiagonalMatrix d(m);
    Vector result2 = d.multiplyBy(v);
    result2.save("result2.txt");
    
//    Matrix2 m;
//    m.readFromMtx("bcsstk27.mtx", true);
////    m.loadMatrix("matrix2.txt");
//    m.generateNewVector();
//    m.multiplyMatrix();
//
//    m.diagonalCompression();
//    m.multiplayDiagonal();
//    m.vectorsComparssion();
    
    /*

    int n = 0, k = 0;
    char * st = Menu();
    char * vt;
    char * vt2;
    Matrix2 m;

    m.readFromMtx(st);

    cout<<"Wybierz wektor do mnozenia"<<endl;
        cout<<"1. Wygeneruj nowy wektor"<<endl;
        cout<<"2. Wczytaj utworzony wektor"<<endl; // Nie ruszac na razie
    cin>>k;

    switch(k){
        case 1:
            m.generateNewVector();
        break;
        case 2:
            vt = menuVector();
            m.readVector(vt);
        break;
        default:
            m.generateNewVector();
        break;
    }
        cout<<"\nWybierz metode do formatowania"<<endl;
        cout<<"1. Metoda Diagonalna"<<endl;
        cout<<"2. Metoda Powlokowa"<<endl;
        cout<<"3. Metoda Rozrzedzona wierszowa"<<endl;
        cout<<"4. Metoda Współrzędnych"<<endl;
        cout<<"5. Wyjscie"<<endl;
        cin>>n;
        switch(n){
            case 1:
            {
                cout << "Metoda Powlokowa"<<endl;
                m.coatCompression();
                std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
                m.multiplayCoat();
                std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
                int time = chrono::duration_cast<chrono::nanoseconds> (end - begin).count();
                
                m.matrixDetails();
                
                std::cout << "Time difference = " << time <<std::endl;
                m.coatSize();
                break;
            }
            case 2:
            {
                cout<<"2. Metoda diagonalna"<<endl;
                m.diagonalCompression();
                std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
                m.multiplayDiagonal();
                std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
                int time = chrono::duration_cast<chrono::nanoseconds> (end - begin).count();
                
                m.matrixDetails();

                std::cout << "Time difference = " << time <<std::endl;
                m.diagonalSize();
                break;
            }
            case 3:{
                cout<<"3. Metoda Rozrzedzona wierszowa"<<endl;
                m.modifiedSparseCompression();
                std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
                m.multiplicationModifiedSparseCompression();
                std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
                int time = chrono::duration_cast<chrono::nanoseconds> (end - begin).count();
                std::cout << "Time difference = " << time <<std::endl;
                m.checkMemory();
                break;
                
            }
            case 4:{
                cout<<"4. Metoda Współrzędnych"<<endl;
                m.coordinatesCompression();
                std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
                m.multiplicationCoordinatesCompression();
                std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
                int time = chrono::duration_cast<chrono::nanoseconds> (end - begin).count();
                std::cout << "Time difference = " << time <<std::endl;
                m.checkMemory();
                break;
            }
            case 5:
                break;
        }
     */
}
