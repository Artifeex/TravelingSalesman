#pragma once
#include "Algorithm.h"
#include <algorithm>
#include "AdjacencyMatrixG.h"
class BruteForceAlg:public Algorithm
{
private:
  AdjacencyMatrixG<int> matrix;
  std::vector<int> shortestPath;
  int shortestValuePath;
public:
  void Run() override;
  BruteForceAlg(const AdjacencyMatrixG<int>& m);
  BruteForceAlg(const Matrix<int>& m);
  int GetShortestValuePath();
  std::vector<int> GetShortestPath();
};

