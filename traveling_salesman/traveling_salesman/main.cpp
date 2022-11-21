#include "Matrix.h"
#include <iostream>
#include "AntColonyAlg.h"

int main(int argc, char* argv[])
{
  Matrix<int> m(3, 5);
  std::vector<int> values = { 3, 5, 7, 9, 8 };
  m.AddRow(values);
  std::cout << m;
  AdjacencyMatrixG<int> ma(4);
  ma[0] = { 0, 10, 20, 7 };
  ma[1] = { 10, 0, 5, 5 };
  ma[2] = { 20, 5, 0, 20 };
  ma[3] = { 7, 5, 20, 0 };
  AntColonyAlg alg(ma);
  alg.Run();
  int minRoad = alg.GetMinRoad();
  std::cout << minRoad;
}