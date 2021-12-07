all: matrixSum

matrixSum: main.o ParallelMatrix.o
	g++ main.o ParallelMatrix.o -lpthread -o matrixSum

main.o: main.cpp ParallelMatrix.h
	g++ main.cpp -c

ParallelMatrix.o: ParallelMatrix.cpp ParallelMatrix.h
	g++ ParallelMatrix.cpp -c

clean:
	rm *.o matrixSum
