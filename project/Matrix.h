#include <vector>
#include <iostream>

using namespace std;

class Matrix {
    int columns, rows;
    vector < double > matrix;
    vector < double > checkMatrix;

    vector < double > vec; // wygenerowany wektor
    vector < double > vecResult; // wektor do wyniku mnozenia
    vector < double > vecResult2;
    vector <double> AN; // AN - wartosci, IN - wiersze, JA - kolumny
    vector <int> JA, IN;  // wektory na ³apanie formatow kompresji

    vector < vector < double > > compressed;
	vector < double > compressed2;

public:
    Matrix(){};
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
    void readFromMtx(char * s, bool = true);
    
    void multiplyMatrix();
	void vectorsComparssion();

	double* getMatrix();
	double* getVector();
	double* getResult();

	int * getInd();
	int * getPtr();
	double * getData();

	int getSize();
	int getIndSize();
	int getPtrSize();
	int getDataSize();
	double* getCompressedResult();
	double* getCompressedMatrix();
	
	int getCompressedColumnSize();
};