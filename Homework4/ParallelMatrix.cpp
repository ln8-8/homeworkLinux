#include "ParallelMatrix.h"
#include <cstdlib>
#include <pthread.h>
#include <cerrno>
#include <iostream>

// arguments of matrix
struct sumElements
{
        int* myMatrix;
        int start;
        int count;
};

// sum element of the part of the matrix
void* sumThreads(void* matArg)
{
        sumElements* argsToSum = (sumElements*) matArg;
        int sumForThread = 0;
        for(int i = argsToSum->start; i < argsToSum->start + argsToSum->count; ++i) {
                sumForThread += argsToSum->myMatrix[i];
        }
        return (void*) (new int(sumForThread));
}

// constructor which create matrix 
ParallelMatrix::ParallelMatrix(int _row, int _col) : Row(_row), Col(_col) {
	matrix = new int [Row*Col];
}

// fill the matrix with random numbers
void ParallelMatrix::fillRandom() {
	for(int i = 0; i < Row; ++i) {
		for(int j = 0; j < Col; ++j) {
			matrix[Col*i + j] = rand() % 100;
		}
	}
}

// return element with given index
int ParallelMatrix::Element(int _row, int _col) {
	return matrix[Col*_row + _col]; 
}

// return the number of Rows
int ParallelMatrix::numberOfRows() {
	return Row;
}

// return the number of Columns
int ParallelMatrix::numberOfColumns() {
	return Col;
}

// sum all elements of the matrix without threand
int ParallelMatrix::Sum() {
	int sum = 0;
	for(int i = 0; i < Row*Col; ++i){
		sum += matrix[i];
	}
	return sum;
}

// sum all elements of the matrix with given number of Threads
int ParallelMatrix::SumParrallel(int numOfThreads) {
	int sum = 0;
	int matrixSize = Row*Col;

	// create array for threads
	pthread_t* threads = new pthread_t[numOfThreads];

	// create array for arguments
	sumElements* matArg = new sumElements[numOfThreads];

	// divide process into threads
	for(int i = 0; i < numOfThreads; ++i) {
		matArg[i].myMatrix = matrix;
		matArg[i].start = i*(matrixSize/numOfThreads);
		matArg[i].count = matrixSize/numOfThreads;
		
		// create threade
		int out = pthread_create(&threads[i], NULL, sumThreads, &matArg[i]);

		// check error 
		if(out != 0) {
			std::cerr << "Couldn't create new thread" << std::endl;
			exit(out);
		}
	}	

        void* sumForThread;

        for(int i = 0; i < numOfThreads; ++i) {	
		// join the thread
                int joined = pthread_join(threads[i], &sumForThread);
		
		// check error while joining
                if (joined != 0) {
			std::cerr << "Couldn't join" << std::endl;
                        exit(joined);
                }

		// count the whole sum 
                int* sumForThreadToInt = (int*) sumForThread;
                sum += *sumForThreadToInt;
                delete sumForThreadToInt;
        }
	
	// delete all dynamic arrays
	delete[] threads;
	delete[] matArg;

	// retrun sum
	return sum;
}

// destructor to delete out matrix
ParallelMatrix::~ParallelMatrix() {
	delete[] matrix;
}
