#include "Matrix.h"
#include <iostream>
#include "AntColonyAlg.h"
#include "BruteForceAlg.h"
#include "TestSpeed.h"

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
  std::vector<int> res = alg.GetMinPath();
  std::cout <<"Min road: " << minRoad << std::endl;
  std::cout << "Path: " << std::endl;
  for (size_t i = 0; i < res.size(); i++)
  {
	std::cout << res[i] << " ";
  }
  std::cout << std::endl << std::endl;
  BruteForceAlg bAlg(ma);
  bAlg.Run();
  std::cout << "Min road: " << bAlg.GetShortestValuePath() << std::endl;
  std::cout << "Path: " << std::endl;
  res = bAlg.GetShortestPath();
  for (size_t i = 0; i < res.size(); i++)
  {
	std::cout << res[i] << " ";
  }
  std::cout << std::endl << std::endl;
  ts::TestSpeed::CompareAlgs(&alg, &bAlg);
}