#pragma once
#include "Algorithm.h"
#include "NearestNeighboor.h"

//O(N^2)
class TwoOpt: public Algorithm
{
private:
  AdjacencyMatrixG<int> matrix;
  int minPathValue;
  int currentPathValue;
  std::vector<int> path;
  int calculateCost(const std::vector<int>& curPath);
  void TwoOptSwap(std::vector<int>& tmpPath, int i, int j);
  void TwoOptUndoSwap(std::vector<int>& tmpPath, int i, int j);

public:
  void SetMatrix(const AdjacencyMatrixG<int>& matr) override;
  void SetMatrix(const Matrix<int>& m);

  TwoOpt() {
    algName = "2-opt";
  }

  void Run() override;
  int GetMinWeight() override { return minPathValue; }
  std::vector<int> GetMinRoute() override { return path; }
};

