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

    void loadMatrix(char *s);
    void coatCompression();//Schemat pow³okowy
    void diagonalCompression();//Kompresja Shermana
    void coordinatesCompression();
    void modifiedSparseCompression();
    void checkTwoMatrices() const;
    void makeEmptyCheckMatrix();
};
