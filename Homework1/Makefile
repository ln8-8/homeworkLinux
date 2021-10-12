all: output

output: main.o ComplexNumber.o
	g++ main.o ComplexNumber.o -o output

main.o: main.cpp
	g++ -c main.cpp

ComplexNumber.o: ComplexNumber.cpp ComplexNumber.h
	g++ -c ComplexNumber.cpp

clean:
	rm *.o output
