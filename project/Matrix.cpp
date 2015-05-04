#include "Matrix.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;


void Matrix::loadMatrix(char * s) {
    //opening file
    ifstream plik;

    plik.open(s);

    if (!plik.good())
        return;


    //Reading from file
    int columns, rows, number;
    int numberInRow;

    plik >> columns >> rows;

    this->columns = columns;
    this->rows = rows;

    while (true){
        numberInRow++;
        plik >> number;

        if (plik.good()){
            this->matrix.push_back(number);
        }
        else
            break;

        if (numberInRow == columns){
            numberInRow = 0;
        }

    }
}

void Matrix::coatCompression()
{
    vector<int> an, ia;

    for (int i = 0; i<this->rows; i++)
    {
        bool startReading = false;


        for (int i2=0; i2<i+1; i2++){
            if (this->matrix[i*this->columns+i2] != 0 || startReading == true){
                startReading = true;
                an.push_back(this->matrix[i*this->columns+i2]);
            }
        }
        ia.push_back(static_cast<int>(an.size()));
    }

    this->compressed.push_back(an);
    this->compressed.push_back(ia);

//    check
//
//    for (int i=0; i<an.size(); i++) {
//        cout << an[i] << " ";
//    }
//    cout << endl;
//    for (int i=0; i<ia.size(); i++) {
//        cout << ia[i] << " ";
//    }
}

void Matrix::diagonalCompression()
{
    int size = 0;
    vector<int> row;
    for (int i = 0; i<this->rows; i++)
    {
        int beta = 0;
        bool trigger = false;
        for (int i2 = 0; i2<i+1; i2++) {
            int currentNumber = this->matrix[i*this->columns+i2];
            if (currentNumber > 0)
            {
                trigger = true;
                beta = i - i2;
                if (beta > size)
                    size = beta;
            }
            if (trigger)
                row.push_back(currentNumber);
        }
        this->compressed.push_back(row);
        row.clear();
    }

    for (int i=0; i<this->compressed.size(); i++) {
        while (this->compressed[i].size()<size+1)
            this->compressed[i].insert(this->compressed[i].begin(), 0);
    }

//    check
//    for (int i=0; i<this->compressed.size(); i++) {
//        for (int i2=0; i2<this->compressed[i].size(); i2++) {
//            cout << this->compressed[i][i2] << " ";
//        }
//        cout << endl;
//    }
}

void Matrix::diagonalUnzip(){
    this->checkMatrix.clear();
    this->rows = static_cast<int>(this->compressed.size());
    this->columns = this->rows;
    for (int i=0; i<this->compressed.size(); i++) {
        size_t rowSize = this->compressed[i].size() - 1;
        int n = static_cast<int>(i-rowSize);
        //zeros on front
        for (int i2=0; i2<n; i2++) {
            this->checkMatrix.push_back(0);
        }
        for (int i2=0; i2<rowSize+1; i2++) {
            int column = static_cast<int>(this->checkMatrix.size() - i * this->columns);
            if (rowSize>i && i2<=i){
                this->checkMatrix.push_back(this->compressed[i][rowSize-i+i2]);
                this->checkMatrix[this->rows*column+i] = this->compressed[i][rowSize-i+i2];

            }else if (i2<=i){
                this->checkMatrix.push_back(this->compressed[i][i2]);
                this->checkMatrix[this->rows*column+i] = this->compressed[i][i2];

        }
        //zeros on back
        for (int i2=i; i2<this->columns-1; i2++) {
            this->checkMatrix.push_back(0);
        }
    }

//    check
//    for (int i = 1; i<=this->matrix.size(); i++) {
//        cout << this->matrix[i-1];
//        cout << " ";
//        if (i%this->rows == 0 )
//            cout << endl;
//    }
}
}


void Matrix::coatUnzip(){
    this->checkMatrix.clear();
    this->rows = static_cast<int>(this->compressed[1].size());
    int nextStepSize = 0,
        position = 0;
    for (int i=0; i<this->rows; i++){
        nextStepSize = this->compressed[1][i] - nextStepSize;

        for (int i2 = 0; i2<i-nextStepSize+1; i2++) {
            this->checkMatrix.push_back(0);
        }
        for (int i2 = position; i2<position + nextStepSize; i2++){
            this->checkMatrix.push_back(this->compressed[0][i2]);
            int column = static_cast<int>(this->checkMatrix.size() - i * this->columns -1);
            this->checkMatrix[this->rows*column+i] = this->compressed[0][i2];
        }
        for (int i2=0; i2<this->columns-i-1; i2++) {
            this->checkMatrix.push_back(0);
        }
        position = position + nextStepSize;
        nextStepSize = this->compressed[1][i];
    }

//    for (int i = 1; i<=this->matrix.size(); i++) {
//        cout << this->matrix[i-1];
//        cout << " ";
//        if (i%this->rows == 0 )
//            cout << endl;
//    }
    checkTwoMatrices();
}


void Matrix::coordinatesCompression(){

    for (int i = 0; i<this->rows; i++){
        for (int i2=0; i2<this->columns; i2++){
            int currentNumber = this->matrix[i*this->columns+i2];
            if (currentNumber != 0) {
                AN.push_back(currentNumber);
                IN.push_back(i);
                JA.push_back(i2);
            }
        }
    }
}

void Matrix::makeEmptyCheckMatrix(){
    checkMatrix.clear();

    for (int i = 0; i<this->rows * this->columns; i++){
        checkMatrix.push_back(0);
    }
}

void Matrix::checkTwoMatrices() const {
    int count = 0;

    for (int i = 0; i<matrix.size(); i++){
        if(matrix[i]!=checkMatrix[i]){
            count++;
        }
    }

    cout<<endl;
    if (count==0) {
        cout<<"Macierze nie roznia sie!";
    }
    else {
        cout<<"Macierze roznia sie w "<<count<<" miejscach!";
    }
}


void Matrix::generateNewVector(){
    vec.clear();
    double n = 0;
    srand( time( NULL ) );

    for (int i = 0; i < this->columns; i++){
        //n = 1;
        n =( rand() /( static_cast < double >( RAND_MAX ) + 1 ) ) *(10.5 - 5.25 ) - 1.25;
        vec.push_back(n);
    }
    this->saveVector("new_vector.txt", vec);
}

void Matrix::readVector(char * s){ // na probe tekstowy wektor
    fstream plik;
    vec.clear();
    double number = 0.0;

    plik.open( "new_vector.txt", std::ios::in);
    if( plik.good() == true ){
        for (int i = 0; i < this->columns; i++){
            plik >> number;
            vec.push_back(number);
            number = 0;
        }
        plik.close();
    }
}

void Matrix::saveVector(char * s, vector <double> &v) const{
    fstream plik;

    plik.open( s, std::ios::out);
    if( plik.good() == true ){
        for (int i = 0; i < this->columns; i++){
            plik << v[i]<<" "<<endl;
        }
        plik.close();
    }
}

void Matrix::multiplicationCoordinatesCompression(){
    for (int i = 0; i < this->rows; i++ ) {
        vecResult.push_back(0.0);
    }

    for (int i = 0; i < AN.size(); i++){
        vecResult[IN[i]] += (AN[i] * vec[JA[i]])/100;
    }

    this->saveVector("result_vector_coo.txt", vecResult);
}

void Matrix::modifiedSparseCompression(){

    int theBiggestProblemWithCRS = 0;

    for (int i = 0; i<this->rows; i++){
        for (int i2=0; i2<this->columns; i2++){
            int currentNumber = this->matrix[i*this->columns+i2];
            if (currentNumber != 0) {
                AN.push_back(currentNumber);
                JA.push_back(i2);
                theBiggestProblemWithCRS++;
                if(theBiggestProblemWithCRS == 1)
                    IN.push_back(i);
            }
        }
        if (theBiggestProblemWithCRS>0)
            IN.push_back(theBiggestProblemWithCRS);
    }
    IN[IN.size()-1]=AN.size();
}

void Matrix::multiplicationModifiedSparseCompression(){
    for (int i = 0; i<this->rows; i++ ){
        vecResult.push_back(0.0);
        for (int jj = IN[i]; jj < IN[i+1]; jj++ ) {
            int j = JA[jj];
            vecResult[i] += (AN[jj] * vec[j])/100;
        }
    }
    this->saveVector("result_vector_crs.txt", vecResult);
}

void Matrix::coordinatesCompressionUnzip(){
    makeEmptyCheckMatrix();

    int inIndex = 0, jaIndex = 0, anIndex = 0;

    for (int i = 0; i<this->rows; i++){
        for (int i2=0; i2<this->columns; i2++){
            if((i == IN[inIndex]) && (i2 == JA[jaIndex])){
                checkMatrix[i*this->columns+i2]=AN[anIndex];
                inIndex++;
                jaIndex++;
                anIndex++;
            }
        }
    }
    checkTwoMatrices();
}

void Matrix::checkMemory(){
    cout<<"Ilosc elementow macierzy: "<<matrix.size()<<endl;
    cout<<"Macierz przed formatem zajmuje: "<<sizeof(double) * this->matrix.size()<<" bajtow"<<endl;
    cout<<"--------------------------------------"<<endl;
    cout<<"Ilosc elementow niezerowych (double): "<<AN.size()<<endl;
    cout<<"Ilosc wierszy (int): "<<IN.size()<<endl;
    cout<<"Ilosc kolumn (int): "<<JA.size()<<endl;
    cout<<"Macierz po formacie zajmuje: "<<(sizeof(double) * this->AN.size())+ (sizeof(int)*this->IN.size()) + (sizeof(int)* this->JA.size())<<" bajtow"<<endl;
    cout<<"--------------------------------------"<<endl;
    cout<<endl;
}

/*
void Matrix::readFromMtx(){
    // Open the file:
    ifstream plik;
    plik.open("matrix.mtx");
    // Declare variables:
    int M, N, L;

    // Ignore headers and comments:
    while (plik.peek() == '%') plik.ignore(2048, '\n');

    // Read defining parameters:
    plik >> M >> N >> L;

//    cout << M << " " << N << " " << L << " ";

    // Create your matrix:
    vector<int> matrix(M*N);
    for(int i = 0; i < M*N; i++){
        matrix.push_back(0);
    }

    // Read the data
    for (int l = 0; l < L; l++)
    {
        int m, n;
        int data;
        plik >> m >> n >> data;
        matrix[(m-1) + (n-1)*M] = data;
    }

    plik.close();

//    check
//    for (int i = 1; i<M*N+1; i++) {
//        cout << matrix[i-1]<< " ";
//        if (i%M == 0)
//            cout << endl;
//    }

    this->columns = M;
    this->rows = N;
    this->matrix = matrix;


}

void Matrix::multiplayDiagonal(){
    vector<int> vector = {4, 5, 1, 2, 4, 6, 0},
                result(vector.size());

//    fill(std::begin(result), std::end(result), 0);

    for (int row = 0; row<this->rows; row++) {
        int positionInMatrix = row,
            numberOfColumns = this->compressed[0].size() - 1;

        for (int column = numberOfColumns; column>=0; column--) {
            if (positionInMatrix>=0){
                if (column<numberOfColumns){
                    result[row] += vector[positionInMatrix] * this->compressed[row][column];
                    result[positionInMatrix] += vector[row] * this->compressed[row][column];
                }
                else {
                    result[row] += result[row] + vector[positionInMatrix] * this->compressed[row][column];
                }
                positionInMatrix--;
            }
        }
    }

//    check
//    for (int i = 0; i<result.size(); i++) {
//        cout << result[i] << endl;
//    }
}
void Matrix::multiplayCoat(){
    vector<int> vector = {4, 5, 1, 2, 4, 6, 0},
    result(vector.size());

    int position = 0,
        previousRow = 0;

    for (int row = 0; row<this->compressed[1].size(); row++) {
        int elementsToRead = this->compressed[1][row] - previousRow;
        int col = row + 1 - elementsToRead;

        while (position<this->compressed[1][row]) {

            if (position+1==this->compressed[1][row]){
                result[row] += vector[col] * this->compressed[0][position];
            }
            else {
                result[row] += vector[col] * this->compressed[0][position];
                result[col] += vector[row] * this->compressed[0][position];
            }
            col++;
            position++;
        }
        previousRow = this->compressed[1][row];
    }

//    check
//    for (int i = 0; i<result.size(); i++) {
//        cout << result[i] << endl;
//    }
//

}
*/
