#include <vector>
#include <iostream>

using namespace std;


class Matrix {
    int columns, rows;
    vector < int > matrix;
    vector < int > checkMatrix;
    vector < vector < int > > compressed;

public:
    Matrix(){};
    
    void generateMatrix();
    void loadMatrix();
    bool isSymmetric();
    bool isTriangular();
    void compress();
    void coatCompression();//Schemat powłokowy
    void coatUnzip();
    void diagonalUnzip();
    void loadMatrix(char *s);
    void diagonalCompression();//Kompresja Shermana
    void coordinatesCompression();
    void modifiedSparseCompression();
    void checkTwoMatrices() const;
    void makeEmptyCheckMatrix();
    void readFromMtx();
    void multiplayDiagonal();
    void multiplayCoat();
};
