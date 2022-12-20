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
  AdjacencyMatrixG<int> ma(1000);
  ma.GenerateByRandom(RandomFunc);
  AntColonyAlg alg1(ma,2,0.5 ,0.2,1,5, 0.3, 1, 10);
  std::cout << "Time = " << ts::TestSpeed::TestAlg(&alg1) << std::endl;
  std::cout << "Result = " << alg1.GetMinWeight();
  BruteForceAlg bAlg(ma);
  //std::cout << "Матрица смежности имеет вид:" << std::endl;
  //std::cout << ma;
  std::cout << std::endl;
  //ts::TestSpeed::CompareAlgs(&alg1, &bAlg);
}