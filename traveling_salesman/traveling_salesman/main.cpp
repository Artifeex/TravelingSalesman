#include "Matrix.h"
#include <iostream>
#include "AntColonyAlg.h"

int main(int argc, char* argv[])
{
  AdjacencyMatrixG<int> ma(3);
  ma[0] = { 0, 10, 7 };
  ma[1] = { 10, 0, 5 };
  ma[2] = { 20, 5, 0 };
  AntColonyAlg alg(ma);
  std::cout << ma;
  alg.Run();
  int minRoad = alg.GetMinRoad();
  std::cout <<"Min road: " << minRoad;
}