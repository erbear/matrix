#include <vector>
#include <iostream>

using namespace std;

class Matrix {
    int columns, rows;
    vector < double > matrix;
    vector < double > checkMatrix;

    vector < double > vec; // wygenerowany wektor
    vector < double > vecResult; // wektor do wyniku mnozenia
    vector <double> AN; // AN - wartosci, IN - wiersze, JA - kolumny
    vector <int> JA, IN;  // wektory na łapanie formatow kompresji

    vector < vector < int > > compressed;

public:
    Matrix(){};

    void coatCompression();
    void coatUnzip();
    void diagonalUnzip();
    void diagonalCompression();

    void coordinatesCompression();
    void modifiedSparseCompression();
    void coordinatesCompressionUnzip();

    void loadMatrix(char *s);
    void checkTwoMatrices() const;
    void makeEmptyCheckMatrix();

    void generateNewVector();
    void saveVector(char * s, vector <double> &v) const;
    void readVector(char *s);

    void multiplicationCoordinatesCompression();
    void multiplicationModifiedSparseCompression();
    void checkMemory();

    void multiplayDiagonal();
    void multiplayCoat();
    void readFromMtx();
};
