#include <vector>
#include <iostream>

using namespace std;

class Matrix {
    int columns, rows;
    vector < double > matrix;
    vector < double > checkMatrix;
<<<<<<< HEAD
    vector < double > vec; // wygenerowany wektor
    vector < double > vecResult; // wektor do wyniku mnozenia
    vector <double> AN; // AN - wartosci, IN - wiersze, JA - kolumny
    vector <int> JA, IN;  // wektory na łapanie formatow kompresji
=======
    vector < double > vec; // wektor do wektora :)
    vector < double > vecResult; // wynik mnozenia 
    vector <double> AN, IN, JA;  // wektory na łapanie formatow kompresji
>>>>>>> origin/test
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

    void readFromMtx();
    void loadMatrix(char *s);
    void checkTwoMatrices() const;
    void makeEmptyCheckMatrix();

    void generateNewVector();
    void saveVector(char * s, vector <double> &v) const;
    void readVector(char *s);

    void multiplicationCoordinatesCompression();
    void multiplicationModifiedSparseCompression();
    void checkMemory();
};
