#include "Matrix.h"
#include <iostream>

int main()
{
  Matrix<int> m(3, 5);
  std::vector<int> values = { 3, 5, 7, 9, 8 };
  m.AddRow(values);
  std::cout << m;
}