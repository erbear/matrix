#include <vector>
#include <iostream>

using namespace std;


class Matrix {
    int columns, rows;
    vector < double > matrix;
    vector < double > checkMatrix;
    vector < double > vec;
    vector < double > vecResult;
    vector <double> AN, IN, JA;  // wektory na łapanie formatow kompresji
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

    void generateNewVector();
    void saveVector();
    void readVector(char *s);

    void multiplicationCoordinatesCompression();
    void multiplicationModifiedSparseCompression();
};
