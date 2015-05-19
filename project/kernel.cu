
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