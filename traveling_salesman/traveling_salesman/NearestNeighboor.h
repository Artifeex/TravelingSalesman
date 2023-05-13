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
  NearestNeighboor(const AdjacencyMatrixG<int>& matr, int _startVert = 0):
    matrix(matr), startVert(_startVert) {
    visitedVert.resize(matr.GetCountVertices());
    visitedOrder.resize(matr.GetCountVertices(), false);
  }
  NearestNeighboor(const Matrix<int>& m, int _startVert = 0):
    matrix(m), startVert(_startVert) {
    visitedVert.resize(matrix.GetCountVertices());
    visitedOrder.resize(matrix.GetCountVertices(), false);
  }
  void Run() override;
  int GetMinWeight() override { return minPath; }
  std::vector<int> GetMinRoute() override { return visitedOrder; }
  
};

