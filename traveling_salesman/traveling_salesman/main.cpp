#include "Matrix.h"
#include <iostream>
#include "AntColonyAlg.h"
#include "BruteForceAlg.h"
#include "TestSpeed.h"
#include "NearestNeighboor.h"
#include "ImprovedNearestNeighboor.h"
#include "LittleAlg.h"
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
  AdjacencyMatrixG<int> ma(5);
  ma.GenerateByRandom(RandomFunc);
  std::vector<std::vector<int>> matrix = {
	{INT_MAX, 20, 18, 12, 8},
	{5, INT_MAX, 14, 7, 11},
	{12, 18, INT_MAX, 6, 11},
	{11, 17, 11, INT_MAX, 12},
	{5, 5, 5, 5, INT_MAX}
  };
  AdjacencyMatrixG<int> adjMatrix(matrix);
  //AntColonyAlg alg1(ma,2,0.5 ,0.2,1,5, 0.3, 1, 10);
  //std::cout << "Time = " << ts::TestSpeed::TestAlg(&alg1) << std::endl;
  //std::cout << "Result = " << alg1.GetMinWeight();
  //BruteForceAlg bAlg(ma);
  std::cout << "Матрица смежности имеет вид:" << std::endl;
  std::cout << adjMatrix;
  std::cout << std::endl;
  LittleAlg little(adjMatrix, INT_MAX);
  little.Run();
  std::cout << "Длина маршрута: " << little.GetMinWeight() << std::endl;
  std::cout << "Маршрут: " << std::endl;
  auto res = little.GetMinRoute();
  for (auto val : res) {
	std::cout << val << " ";
  }
  std::cout << std::endl;
}