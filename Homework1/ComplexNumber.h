#pragma once
#include <list>
class ComplexNumber
{
  double real;
  double imag;
public:
  ComplexNumber(); //default constructor
  ComplexNumber(double r, double i); //constructor which give data for real and imaginary parts
  void setData(double r, double i); //sets data for real and imaginary parts
  double getReal(); //returns the real part
  double getImaginary(); //returns the imaginary part
  void print() const; //prints the complex number
  ComplexNumber operator +(const ComplexNumber& obj);
  ComplexNumber operator -(const ComplexNumber& obj);
  ComplexNumber operator *(const double n);//multiply by constant when the constant is the second argument
  double absoluteValue(); //returns absolute value of complex number
  friend ComplexNumber operator * (const double n, const ComplexNumber& obj);//multiply by constant when the constant is the first argument
};

void sortListOfComplex(ComplexNumber arr[], int n); // sorts the array of complex numbers using bubble sort
void printArray(ComplexNumber arr[], int n); //prints the array of complex numbers
