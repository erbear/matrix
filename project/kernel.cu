#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include "Matrix.h"
#include <windows.h>
#include <vector>

using namespace std;

__global__
void multiplyCRS(int *ptr, int *ind, double *data, double *vec, double *res, int N) {
	int row = blockDim.x * blockIdx.x + threadIdx.x;

	if ( row < N ){
		double suma = 0;
		for (int jj = ptr[row]; jj < ptr[row + 1]; jj++){
			int j = ind[jj];
			suma += data[jj] * vec[j];
		}
		res[row] += suma;
	}
}




int main()
{
	Matrix m;
	m.readFromMtx("bcsstm13.mtx");
	m.generateNewVector();
	m.multiplyMatrix();
	m.modifiedSparseCompression();

	int block_size = 256;
	int N = m.getSize();
	int I = m.getIndSize();
	int P = m.getPtrSize();
	int D = m.getDataSize();
	int grid_number = ceil(N / (float)block_size);
	int thread_number = grid_number * block_size;

	double summary = 0.0;
	double *vectord;
	double *resultd;
	int *ptrd; 
	int *indd; 
	double *datad;
	vector <double> check;
	double *vector = m.getVector();
	double *result = new double[N];
	int *ptr = m.getPtr();
	int *ind = m.getInd();
	double *data = m.getData();

	fill(result, result + N, 0.);

	// rozmiar
	const int vecor_size = N*sizeof(double);
	const int result_size = N*sizeof(double);
	const int data_size = D*sizeof(double);
	const int ptr_size = P*sizeof(int);
	const int ind_size = I*sizeof(int);

	// zalokowanie
	
	cudaMalloc((void**)&ptrd, ptr_size);
	cudaMalloc((void**)&indd, ind_size);
	cudaMalloc((void**)&datad, data_size);
	cudaMalloc((void**)&vectord, vecor_size);
	cudaMalloc((void**)&resultd, result_size);

	//przeslanie do CUDY

	cudaMemcpy(ptrd, ptr, ptr_size, cudaMemcpyHostToDevice);
	cudaMemcpy(indd, ind, ind_size, cudaMemcpyHostToDevice);
	cudaMemcpy(datad, data, data_size, cudaMemcpyHostToDevice);
	cudaMemcpy(vectord, vector, vecor_size, cudaMemcpyHostToDevice);
	cudaMemcpy(resultd, result, result_size, cudaMemcpyHostToDevice);

	dim3 dimBlock(block_size, 1);
	dim3 dimGrid(grid_number);

	// mnozenie
	
	cudaEvent_t start, stop;
	float time;

	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	cudaEventRecord(start, 0);
	 
         multiplyCRS <<< dimGrid, dimBlock >>> (ptrd, indd, datad, vectord, resultd, N);
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);

	cudaEventElapsedTime(&time, start, stop);

	printf("Time difference: %f ms \n", time);
               
	// odsylanie
	cudaMemcpy(result, resultd, result_size, cudaMemcpyDeviceToHost);

	// uwolnienie
	
	cudaFree(ptrd);
	cudaFree(indd);
	cudaFree(datad);
	
	/*
	double* result2 = m.getResult();
	for (int i = 0; i < N; i++){
		if (result2[i] != 0){
			printf(" %f ---- %d ---- %f  \n", result[i]/100, i, result2[i]);
		}
	}

	*/
	printf("ilosc wierszy: %d  \n", N);
	printf("grid_number: %d  \n", grid_number);
	printf("threads_number: %d  \n", thread_number);
}