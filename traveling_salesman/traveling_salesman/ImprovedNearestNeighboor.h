#pragma once
#include "Algorithm.h"
#include "AdjacencyMatrixG.h"
#include <vector>
//O(n^3)
class ImprovedNearestNeighboor: public Algorithm
{
private:
  AdjacencyMatrixG<int> matrix;
  std::vector<bool> visitedVert;
  std::vector<int> visitedOrder;
  int bestResult = INT_MAX;
  int inifinity = INT_MAX;

  int FindMinDistanceVert(int vert, const std::vector<bool>& tmpVisitedVert);
public:
  ImprovedNearestNeighboor() {
    algName = "Улучшенный ближайшего соседа";
  }

  void SetMatrix(const AdjacencyMatrixG<int>& matr) override;
  void SetMatrix(const Matrix<int>& m);

  void Run() override;
  int GetMinWeight() override { return bestResult; }
  std::vector<int> GetMinRoute() override { return visitedOrder; }
};

