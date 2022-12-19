#pragma once
#include "Algorithm.h"
#include <algorithm>
#include "AdjacencyMatrixG.h"
class BruteForceAlg: public Algorithm
{
private:
  AdjacencyMatrixG<int> matrix;
  std::vector<int> shortestPath;
  int shortestValuePath = INT_MAX;
public:
  void Run() override;
  BruteForceAlg(const AdjacencyMatrixG<int>& m);
  BruteForceAlg(const Matrix<int>& m);
  int GetMinWeight() override;
  std::vector<int> GetMinRoute() override;
  void SetNameAlg(std::string _nameAlg);
};

