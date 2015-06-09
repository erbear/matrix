#include <iostream>
#include "Matrix.h"
#include <stdio.h>
#include <vector>

#include <fstream>
#include <algorithm>
#include <ctime>

#include <windows.h>

#define TIMER_INIT \
	LARGE_INTEGER frequency; \
	LARGE_INTEGER t1, t2; \
	double elapsedTime; \
	QueryPerformanceFrequency(&frequency);

#define TIMER_START QueryPerformanceCounter(&t1);

#define TIMER_STOP \
	QueryPerformanceCounter(&t2); \
	elapsedTime = (float)(t2.QuadPart - t1.QuadPart) / (frequency.QuadPart/1000); \
	std::wcout << elapsedTime << "ms" << endl;

using namespace std;

char * Menu()
{
    int n;
    char * st;
    cout<<"Wybierz macierz do formatowania"<<endl;
    cout<<"1. Macierz 1 bcsstk27.mtx"<<endl;
    cout<<"2. Macierz 2 bcsstk28.mtx"<<endl;
    cout<<"3. Macierz 3 bcsstm13.mtx"<<endl;
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
    default:
        st = "bcsstk28.mtx";
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

    int n = 0, k = 0;
    char * st = Menu();
    char * vt;
    char * vt2;
    Matrix m;
    TIMER_INIT;
    m.readFromMtx(st, true);

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
        cout<<"1. Metoda Powlokowa"<<endl;
        cout<<"2. Metoda Diagonalna"<<endl;
        cout<<"3. Metoda Rozrzedzona wierszowa"<<endl;
        cout<<"4. Metoda Wspolrzednych"<<endl;
        cout<<"5. Normalna metoda"<<endl;
        cin>>n;
        switch(n){
            case 1:
            {
                cout << "1. Metoda Powlokowa"<<endl;
                m.coatCompression();
                TIMER_START;
                    m.multiplayCoat();
                TIMER_STOP;
                m.matrixDetails();
                m.coatSize();
                break;
            }
            case 2:
            {
                cout<<"2. Metoda Diagonalna"<<endl;
                m.diagonalCompression();
                TIMER_START;
                    m.multiplayDiagonal();
                TIMER_STOP;
                m.matrixDetails();
                m.diagonalSize();
                break;
            }
            case 3:{
                cout<<"3. Metoda Rozrzedzona wierszowa"<<endl;
                m.modifiedSparseCompression();
                TIMER_START;
                    m.multiplicationModifiedSparseCompression();
                TIMER_STOP;
                m.checkMemory();
                break;

            }
            case 4:{
                cout<<"4. Metoda Wspolrzednych"<<endl;
                m.coordinatesCompression();
                TIMER_START;
                    m.multiplicationCoordinatesCompression();
                TIMER_STOP;
                m.checkMemory();
                break;
            }
            case 5:{
                cout<<"5. Normalna metoda"<<endl;
                TIMER_START;
                    m.multiplyMatrix();
                TIMER_STOP;
                break;
            }
            default:{
                cout<<"3. Metoda Rozrzedzona wierszowa"<<endl;
                m.modifiedSparseCompression();
                TIMER_START;
                    m.multiplicationModifiedSparseCompression();
                TIMER_STOP;
                m.checkMemory();
                break;
            }
        }
}
