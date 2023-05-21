#pragma once
#include "Algorithm.h"
#include "AdjacencyMatrixG.h"
#include <vector>

class ImprovedNearestNeighboor: public Algorithm
{
private:
  AdjacencyMatrixG<int> matrix;
  std::vector<bool> visitedVert;
  std::vector<int> visitedOrder;
  int bestResult = INT_MAX;

  int FindMinDistanceVert(int vert, const std::vector<bool> tmpVisitedOrder);
public:
  ImprovedNearestNeighboor(const AdjacencyMatrixG<int>& matr): matrix(matr) {
    visitedVert.resize(matr.GetCountVertices());
    visitedOrder.resize(matr.GetCountVertices(), false);
    algName = "Улучшенный ближайшего соседа";
  }
  ImprovedNearestNeighboor(const Matrix<int>& m): matrix(m) {
    visitedVert.resize(matrix.GetCountVertices());
    visitedOrder.resize(matrix.GetCountVertices(), false);
    algName = "Улучшенный ближайшего соседа";
  }
  void Run() override;
  int GetMinWeight() override { return bestResult; }
  std::vector<int> GetMinRoute() override { return visitedOrder; }
};

