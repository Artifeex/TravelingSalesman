#pragma once
#include "Algorithm.h"
#include "AdjacencyMatrixG.h"
#include <algorithm>
#include <vector>
class NearestNeighboor: public Algorithm
{
private:
  AdjacencyMatrixG<int> matrix;
  std::vector<bool> visitedVert;
  std::vector<int> visitedOrder;
  int minPath = 0;
  int startVert;

  int FindMinDistanceVert(int vert);
public:
  NearestNeighboor(int _startVert = 0):
    startVert(_startVert) {
    algName = "Ближайшего соседа";
  }

  void SetMatrix(const AdjacencyMatrixG<int>& matr) override;
  void SetMatrix(const Matrix<int>& m);

  void Run() override;
  int GetMinWeight() override { return minPath; }
  std::vector<int> GetMinRoute() override { return visitedOrder; }
  
};

