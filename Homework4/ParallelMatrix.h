#pragma once

class ParallelMatrix{
private:
	int Col;
	int Row;
	int* matrix;
public:
	ParallelMatrix(int _row, int _col);
	void fillRandom();
	int Element(int _row, int _col);
	int numberOfRows();
	int numberOfColumns();
	int Sum();
	int SumParrallel(int numOfThreads);
	~ParallelMatrix();

};
