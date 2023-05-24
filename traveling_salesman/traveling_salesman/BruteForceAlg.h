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

  void SetMatrix(const AdjacencyMatrixG<int>& m) override;
  void SetMatrix(const Matrix<int>& m);
  BruteForceAlg();
  int GetMinWeight() override;
  std::vector<int> GetMinRoute() override;
  void SetNameAlg(std::string _nameAlg);
};

