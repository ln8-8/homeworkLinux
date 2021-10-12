#include "ComplexNumber.h"
#include <iostream>
#include <cmath>
using namespace std;

ComplexNumber::ComplexNumber() : real(0), imag(0) {}

ComplexNumber::ComplexNumber(double r, double i) : real(r), imag(i) {}

void ComplexNumber::setData(double r, double i) {
  real = r;
  imag = i;
}

double ComplexNumber::getReal() {
  return real;
}

double ComplexNumber::getImaginary() {
  return imag;
}
void ComplexNumber::print() const {
  if (imag == 0) {
    cout << real << endl;
  }
  else if (real == 0) {
    cout << imag << 'i' << endl;
  }
  else if (imag < 0) {
    cout << real << imag << 'i' << endl;
  }
  else {
    cout << real << '+' << imag << 'i' << endl;
  }
}

ComplexNumber ComplexNumber::operator +(const ComplexNumber& obj) {
  ComplexNumber ans;
  ans.real = real + obj.real;
  ans.imag = imag + obj.imag;
  return ans;
}

ComplexNumber ComplexNumber::operator -(const ComplexNumber& obj) {
  ComplexNumber ans;
  ans.real = real - obj.real;
  ans.imag = imag - obj.imag;
  return ans;
}
ComplexNumber ComplexNumber::operator *(const double n) {
  ComplexNumber ans;
  ans.real = real * n;
  ans.imag = imag * n;
  return ans;
}


double ComplexNumber::absoluteValue() {
  return sqrt(real * real + imag * imag);
}

ComplexNumber operator * (const double n, const ComplexNumber& obj) {
  ComplexNumber ans;
  ans.real = obj.real * n;
  ans.imag = obj.imag * n;
  return ans;
}

void sortListOfComplex(ComplexNumber arr[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i; j++) {
      if (arr[j].absoluteValue() > arr[j + 1].absoluteValue()) {
        ComplexNumber temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

void printArray(ComplexNumber arr[], int n) {
  for (int i = 0; i < n; i++) {
    arr[i].print();
  }
}
