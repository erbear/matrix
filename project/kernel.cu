
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

using namespace std;


__global__
void multiply(double *mtx, double *vec, double *res, int N)
{
	for (int i = 0; i < N; i++){
		int idx = blockIdx.x * blockDim.x + threadIdx.x;
		if (idx < N){
			res[idx] += mtx[idx * N + i] * vec[i];
		}
	}
}


__global__
void multiplyCompressed(double *mtx, double *vec, double *res, int rows, int columns)
{
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	int positionInMatrix = idx;

	if (idx < rows){
		for (int column = columns - 1; column >= 0; column--){
			if (positionInMatrix >= 0){
				if (column < columns - 1){
					res[idx] += vec[positionInMatrix] * mtx[idx*columns + column];
					res[positionInMatrix] += vec[idx] * mtx[idx*columns + column];
				}
				else{
					res[idx] += vec[positionInMatrix] * mtx[idx*columns + column];
				}
				positionInMatrix--;
			}
		}
	}
}

int main()
{
	Matrix m;
	m.readFromMtx("bcsstk27.mtx");
	//m.loadMatrix("matrix.txt");
	m.generateNewVector();
	m.multiplyMatrix();

	int block_size = 256;
	int N = m.getSize();
	int grid_number = ceil(N / (float)block_size);
	int thread_number = grid_number * block_size;
	double *matrixd;
	double *vectord;
	double *resultd;
	double *matrix = m.getMatrix();
	double *vector = m.getVector();
	double *result = new double[N];
	//for (int i = 0; i < N*N; i++){
	//	if (matrix[i] != 0){
	//		printf("%d: %f \n", i, matrix[i]);
	//	}
	//}
	fill(result, result + N, 0.);

	const int martix_size = N*N*sizeof(double);
	const int vecor_size = N*sizeof(double);
	const int result_size = N*sizeof(double);


	cudaMalloc((void**)&matrixd, martix_size);
	cudaMalloc((void**)&vectord, vecor_size);
	cudaMalloc((void**)&resultd, result_size);

	cudaMemcpy(matrixd, matrix, martix_size, cudaMemcpyHostToDevice);
	cudaMemcpy(vectord, vector, vecor_size, cudaMemcpyHostToDevice);
	cudaMemcpy(resultd, result, result_size, cudaMemcpyHostToDevice);

	dim3 dimBlock(block_size, 1);
	dim3 dimGrid(grid_number);
	multiply << <dimGrid, dimBlock >> >(matrixd, vectord, resultd, N);
	cudaMemcpy(result, resultd, result_size, cudaMemcpyDeviceToHost);
	cudaFree(matrixd);
	cudaFree(vectord);
	cudaFree(resultd);
	double* result2 = m.getResult();
	for (int i = 0; i < N; i++){
		if (result2[i] != 0){
			printf(" %f ---- %d ---- %f  \n", result[i], i, result2[i]);
		}
	}
	printf("ilosc wierszy: %d  \n", N);
	printf("grid_number: %d  \n", grid_number);
	printf("threads_number: %d  \n", thread_number);
}

int main()
{
	Matrix m;
	m.readFromMtx("bcsstk28.mtx");
	//m.loadMatrix("matrix.txt");
	m.generateNewVector();
	m.diagonalCompression();
	m.multiplayDiagonal();


	int block_size = 256;
	int rows = m.getSize();
	int columns = m.getCompressedColumnSize();
	printf("rows: %d ", rows);
	printf("columns: %d ", columns);

	int grid_number = ceil(rows / (float)block_size);
	int thread_number = grid_number * block_size;

	double *matrixd;
	double *vectord;
	double *resultd;
	double *matrix = m.getCompressedMatrix();
	double *vector = m.getVector();
	double *result = new double[rows];

	//for (int i = 0; i < rows*columns; i++){
	//	printf(" %f ", matrix[i]);
	//	if ((i+1)%columns == 0){
	//		printf("\n");
	//	}
	//}

	fill(result, result + rows, 0.);
	const int martix_size = rows*columns*sizeof(double);
	const int vecor_size = rows*sizeof(double);
	const int result_size = rows*sizeof(double);


	cudaMalloc((void**)&matrixd, martix_size);
	cudaMalloc((void**)&vectord, vecor_size);
	cudaMalloc((void**)&resultd, result_size);

	cudaMemcpy(matrixd, matrix, martix_size, cudaMemcpyHostToDevice);
	cudaMemcpy(vectord, vector, vecor_size, cudaMemcpyHostToDevice);
	cudaMemcpy(resultd, result, result_size, cudaMemcpyHostToDevice);

	dim3 dimBlock(block_size, 1);
	dim3 dimGrid(grid_number);
	multiplyCompressed << <dimGrid, dimBlock >> >(matrixd, vectord, resultd, rows, columns);
	cudaMemcpy(result, resultd, result_size, cudaMemcpyDeviceToHost);
	cudaFree(matrixd);
	cudaFree(vectord);
	cudaFree(resultd);

	double* result2 = m.getCompressedResult();
	for (int i = 0; i < rows; i++){
		if (result2[i] != 0){
			printf(" %f ---- %d ---- %f  \n", result[i], i, result2[i]);
		}
	}
	printf("ilosc wierszy: %d  \n", rows);
	printf("grid_number: %d  \n", grid_number);
	printf("threads_number: %d  \n", thread_number);
}