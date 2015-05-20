#include "Matrix2.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;


void Matrix2::loadMatrix(char * s) {
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

void Matrix2::coatCompression()
{
    AN.clear();
    JA.clear();

    for (int i = 0; i<this->rows; i++)
    {
        bool startReading = false;


        for (int i2=0; i2<i+1; i2++){
            if (this->matrix[i*this->columns+i2] != 0 || startReading == true){
                startReading = true;
                AN.push_back(this->matrix[i*this->columns+i2]);
            }
        }
        JA.push_back(static_cast<int>(AN.size()));
    }

//    check
//
//    for (int i=0; i<AN.size(); i++) {
//        cout << AN[i] << " ";
//    }
//    cout << endl;
//    for (int i=0; i<JA.size(); i++) {
//        cout << JA[i] << " ";
//    }
}

void Matrix2::diagonalCompression()
{
    int size = 0;
    vector<double> row;
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

void Matrix2::diagonalUnzip(){
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
        }
        //zeros on back
        for (int i2=i; i2<this->columns-1; i2++) {
            this->checkMatrix.push_back(0);
        }
        
    }

//    check
//    for (int i = 1; i<=this->checkMatrix.size(); i++) {
//        cout << this->checkMatrix[i-1];
//        cout << " ";
//        if (i%this->rows == 0 )
//            cout << endl;
//    }
}


void Matrix2::coatUnzip(){
    this->checkMatrix.clear();
    this->rows = static_cast<int>(JA.size());
    int nextStepSize = 0,
        position = 0;
    for (int i=0; i<this->rows; i++){
        nextStepSize = JA[i] - nextStepSize;

        for (int i2 = 0; i2<i-nextStepSize+1; i2++) {
            this->checkMatrix.push_back(0);
        }
        for (int i2 = position; i2<position + nextStepSize; i2++){
            this->checkMatrix.push_back(this->AN[i2]);
            int column = static_cast<int>(this->checkMatrix.size() - i * this->columns -1);
            this->checkMatrix[this->rows*column+i] = AN[i2];
        }
        for (int i2=0; i2<this->columns-i-1; i2++) {
            this->checkMatrix.push_back(0);
        }
        position = position + nextStepSize;
        nextStepSize = JA[i];
    }

//    for (int i = 1; i<=this->matrix.size(); i++) {
//        cout << this->matrix[i-1];
//        cout << " ";
//        if (i%this->rows == 0 )
//            cout << endl;
//    }
    checkTwoMatrices();
}


void Matrix2::coordinatesCompression(){

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

void Matrix2::makeEmptyCheckMatrix(){
    checkMatrix.clear();

    for (int i = 0; i<this->rows * this->columns; i++){
        checkMatrix.push_back(0);
    }
}

void Matrix2::checkTwoMatrices() const {
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


void Matrix2::generateNewVector(){
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

void Matrix2::readVector(char * s){ // na probe tekstowy wektor
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

void Matrix2::saveVector(char * s, vector <double> &v) const{
    fstream plik;

    plik.open( s, std::ios::out);
    if( plik.good() == true ){
        for (int i = 0; i < this->columns; i++){
            plik << v[i]<<" "<<endl;
        }
        plik.close();
    }
}

void Matrix2::multiplicationCoordinatesCompression(){
    this->vecResult.clear();
    for (int i = 0; i < this->rows; i++ ) {
        vecResult.push_back(0.0);
    }

    for (int i = 0; i < AN.size(); i++){
        vecResult[IN[i]] += (AN[i] * vec[JA[i]]);
    }

    this->saveVector("result_vector_coo.txt", vecResult);
}

void Matrix2::modifiedSparseCompression(){

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

void Matrix2::multiplicationModifiedSparseCompression(){
    for (int i = 0; i<this->rows; i++ ){
        vecResult.push_back(0.0);
        for (int jj = IN[i]; jj < IN[i+1]; jj++ ) {
            int j = JA[jj];
            vecResult[i] += (AN[jj] * vec[j]);
        }
    }
    this->saveVector("result_vector_crs.txt", vecResult);
}

void Matrix2::coordinatesCompressionUnzip(){
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

void Matrix2::checkMemory(){
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


void Matrix2::readFromMtx(char * s, bool isSymetric){
    // Open the file:
    ifstream plik;
    plik.open(s);
    // Declare variables:
    int M, N, L;

    // Ignore headers and comments:
    while (plik.peek() == '%') plik.ignore(2048, '\n');

    // Read defining parameters:
    plik >> M >> N >> L;

//    cout << M << " " << N << " " << L << " ";

    // Create your matrix:
    vector<double> matrix(M*N);
    for(int i = 0; i < M*N; i++){
        matrix.push_back(0);
    }

    // Read the data
    for (int l = 0; l < L; l++)
    {
        int m, n;
        double data;
        plik >> m >> n >> data;
        matrix[(m-1) + (n-1)*M] = data;
        if (isSymetric){
            matrix[(n-1) + (m-1)*N] = data;
        }
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

void Matrix2::multiplayDiagonal(){
    vector<double> result(this->vec.size());
    this->vecResult = result;

//    fill(std::begin(result), std::end(result), 0);

    for (int row = 0; row<this->rows; row++) {
        int positionInMatrix = row,
            numberOfColumns = this->compressed[0].size() - 1;

        for (int column = numberOfColumns; column>=0; column--) {
            if (positionInMatrix>=0){
                if (column<numberOfColumns){
                    this->vecResult[row] += this->vec[positionInMatrix] * this->compressed[row][column];
                    this->vecResult[positionInMatrix] += this->vec[row] * this->compressed[row][column];
                }
                else {
                    this->vecResult[row] += this->vec[positionInMatrix] * this->compressed[row][column];
                }
                positionInMatrix--;
            }
        }
    }

//    check
//    for (int i = 0; i<this->vecResult.size(); i++) {
//        cout << this->vecResult[i] << endl;
//    }
}
void Matrix2::multiplayCoat(){
    vector<double> result(this->vec.size());
    this->vecResult = result;

    int position = 0,
        previousRow = 0;

    for (int row = 0; row<JA.size(); row++) {
        int elementsToRead = JA[row] - previousRow;
        int col = row + 1 - elementsToRead;

        while (position<JA[row]) {

            if (position+1==JA[row]){
                this->vecResult[row] += (this->vec[col] * AN[position]);
            }
            else {
                this->vecResult[row] += (this->vec[col] * AN[position]);
                this->vecResult[col] += (this->vec[row] * AN[position]);
            }
            col++;
            position++;
        }
        previousRow = JA[row];
    }

//    check
//    for (int i = 0; i<this->vecResult.size(); i++) {
//        cout << this->vecResult[i] << endl;
//    }
//

}

void Matrix2::coatSize(){
    cout << "Macierz skompresowana metoda powłokową waży: ";
    cout << (sizeof(double) * this->AN.size())+ (sizeof(int)*this->JA.size()) << "Bajtów" <<endl;
}

void Matrix2::diagonalSize(){
    cout << "Macierz skompresowana metoda diagonalna waży: ";
    cout << (sizeof(double) * this->compressed[0].size() * this->compressed.size()) << "Bajtów" <<endl;
}

void Matrix2::matrixDetails(){
    cout<<"Ilosc elementow macierzy: "<<matrix.size()<<endl;
    cout<<"Macierz przed formatem zajmuje: "<<sizeof(double) * this->matrix.size()<<" bajtow"<<endl;
}

void Matrix2::multiplyMatrix(){
    this->vecResult2.clear();
    vector<double> result(this->rows);
    
    this->vecResult2 = result;
    
    bool isSymetric = true;
    for (int row=0; row<this->rows; row++) {
        for (int column=0; column<this->columns; column++) {
            if (this->matrix[row*this->columns+column] != this->matrix[column*this->rows+row]) {
                isSymetric = false;
            }
            this->vecResult2[row] += this->matrix[row*this->columns+column] * this->vec[column];
        }
    }
    cout << "czy jest symetryczna: " << isSymetric << endl;
    this->saveVector("matrixXvector.txt", result);
}
void Matrix2::vectorsComparssion() {
    bool isSame = true;
    if (this->vecResult.size() != this->vecResult2.size()){
        cout << "Rozne rozmiary wektorow";
    }
    
    for (int i = 0; i<this->vecResult.size(); i++) {
        cout <<this->vecResult[i] << " " <<this->vecResult2[i] << endl;
        if (!(this->vecResult[i] == this->vecResult2[i])){
            isSame = false;
        }
    }
    if (isSame) {
        cout<< "wektory sa takie same";
    } else {
        cout << "wektory sa rozne";
    }
}

double* Matrix2::getMatrix(){
	return &this->matrix[0];
}
double*  Matrix2::getVector(){
	return &this->vec[0];
}
double*  Matrix2::getResult(){
	return &this->vecResult2[0];
}
int Matrix2::getSize(){
	return this->rows;
}