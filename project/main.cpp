#include <iostream>
#include "Matrix.h"
#include <windows.h>

#define TIMER_INIT \
    LARGE_INTEGER frequency; \
    LARGE_INTEGER t1,t2; \
    double elapsedTime; \
    QueryPerformanceFrequency(&frequency);

#define TIMER_START QueryPerformanceCounter(&t1);

#define TIMER_STOP \
    QueryPerformanceCounter(&t2); \
    elapsedTime=(float)(t2.QuadPart-t1.QuadPart)/frequency.QuadPart; \
    std::wcout<<elapsedTime/100<<L" sekund"<<endl;

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
        st = "matrix.txt";
        break;
    case 2:
        st = "matrix2.txt";
        break;
    case 3:
        st = "matrix3.txt";
        break;
    case 4:
        st = "matrix4.txt";
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

    TIMER_INIT;
    int n = 0, k = 0;
    char * st = Menu();
    char * vt;
    char * vt2;
    Matrix m;

    m.loadMatrix(st);

    //m.readFromMtx();

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
        cout<<"1. Metoda Wspolrzednych"<<endl;
        cout<<"2. Metoda Diagonalna"<<endl;
        cout<<"3. Metoda Rozrzedzona wierszowa"<<endl;
        cout<<"4. Metoda Powlokowa"<<endl;
    cin>>n;

    switch(n){
        case 1:
            m.coordinatesCompression();
            cout<<"COO: ";
            TIMER_START
            for(int i = 0; i < 100; i++)
                m.multiplicationCoordinatesCompression();
            TIMER_STOP

            m.checkMemory();
        break;

        case 2: m.diagonalCompression();
        break;
        case 3: m.modifiedSparseCompression();
            m.modifiedSparseCompression();
            cout<<"CRS: ";
            TIMER_START
            for(int i = 0; i < 100; i++)
                m.multiplicationModifiedSparseCompression();
            TIMER_STOP

            m.checkMemory();
        break;
        case 4: m.coatCompression();
        break;
        default:
            m.coordinatesCompression();
            cout<<"COO: ";
            TIMER_START
            for(int i = 0; i < 100; i++)
                m.multiplicationCoordinatesCompression();
            TIMER_STOP

            m.checkMemory();
        break;
    }
}
