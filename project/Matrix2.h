#include <vector>
#include <iostream>

using namespace std;

class Matrix2 {
    int columns, rows;
    vector < double > matrix;
    vector < double > checkMatrix;

    vector < double > vec; // wygenerowany wektor
    vector < double > vecResult; // wektor do wyniku mnozenia
    vector < double > vecResult2;
    vector <double> AN; // AN - wartosci, IN - wiersze, JA - kolumny
    vector <int> JA, IN;  // wektory na łapanie formatow kompresji

    vector < vector < double > > compressed;

public:
    Matrix2(){};
    void matrixDetails();
    
    void coatCompression();
    void coatUnzip();
    void coatSize();
    
    void diagonalUnzip();
    void diagonalCompression();
    void diagonalSize();

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
    void readFromMtx(char * s, bool = false);
    
    void multiplyMatrix();
	void vectorsComparssion();

	double* getMatrix();
	double* getVector();
	double* getResult();
	int getSize();
};
