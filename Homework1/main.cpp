#include <iostream>
#include "ComplexNumber.h"

using namespace std;

int main() {

  ComplexNumber arr[3]; //the array of complex numbers
  arr[0].setData(18, 19); //the real part of the first element of array is 18, and the imaginary part is 19
  arr[1].setData(1, 1);
  arr[2].setData(3, 4);
  printArray(arr, 3); //prints the whole array before sorting
  sortListOfComplex(arr, 3); //sorts the array by their absolute value
  cout << "The array after sorting" << endl;
  printArray(arr, 3); //prints the whole array after sorting
}
