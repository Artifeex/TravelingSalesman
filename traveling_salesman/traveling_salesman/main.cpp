#include "Matrix.h"
#include <iostream>
#include "AntColonyAlg.h"
#include "BruteForceAlg.h"
#include "TestSpeed.h"

int RandomFunc(int i, int j)
{
  if (i == j)
	return INT_MAX;
  return rand() % 100 + 1;
}


int main(int argc, char* argv[])
{
  srand(3);
  setlocale(LC_ALL, "Russian");
  AdjacencyMatrixG<int> ma(3);
  ma.GenerateByRandom(RandomFunc);
  AntColonyAlg alg(ma);
  BruteForceAlg bAlg(ma);
  std::cout << "Матрица смежности имеет вид:" << std::endl;
  std::cout << ma;
  std::cout << std::endl;
  ts::TestSpeed::CompareAlgs(&alg, &bAlg);
}