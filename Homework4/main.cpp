#include <iostream>
#include <chrono>
#include "ParallelMatrix.h"

int main() {

	// create Matrix with 1000 rows and 7000 columns
	ParallelMatrix mat(1000, 7000);

	// fil with random numbers
	mat.fillRandom();
	
	// count sum of matrix without threads
	auto start = std::chrono::high_resolution_clock::now();
	std::cout << "Sum without threads = " << mat.Sum() << std::endl;
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Time without threads: " << elapsed.count() << std::endl;
	std::cout << std::endl;

	// count sum of matrix with 4 threads
        start = std::chrono::high_resolution_clock::now();
        std::cout << "Sum with 4 threads = " << mat.SumParrallel(4) << std::endl;
        finish = std::chrono::high_resolution_clock::now();
        elapsed = finish - start;
        std::cout << "Time with 4 threads: " << elapsed.count() << std::endl;
	std::cout << std::endl;

	// count sum of matrix with 8 threads
	start = std::chrono::high_resolution_clock::now();
        std::cout << "Sum with 8 threads = " << mat.SumParrallel(8) << std::endl;
        finish = std::chrono::high_resolution_clock::now();
        elapsed = finish - start;
        std::cout << "Time with 8 threads: " << elapsed.count() << std::endl;
	std::cout << std::endl;

	// count sum of matrix with 16 threads
	start = std::chrono::high_resolution_clock::now();
        std::cout << "Sum with 16 threads = " << mat.SumParrallel(16) << std::endl;
        finish = std::chrono::high_resolution_clock::now();
        elapsed = finish - start;
        std::cout << "Time with 16 threads: " << elapsed.count() << std::endl;
	std::cout << std::endl;

	// count sum of matrix with 100 threads
	start = std::chrono::high_resolution_clock::now();
	std::cout << "Sum with 100 threads = " << mat.SumParrallel(100) << std::endl;
        finish = std::chrono::high_resolution_clock::now();
       	elapsed = finish - start;
        std::cout << "Time with 100 threads: " << elapsed.count() << std::endl;

}
