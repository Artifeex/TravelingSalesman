#pragma once
#include "Algorithm.h"
#include "AdjacencyMatrixG.h"
#include <algorithm>
#include <vector>
//O(n^2)
class NearestNeighboor: public Algorithm
{
private:
  //матрица смежности
  AdjacencyMatrixG<int> matrix; 
  //массив отображающий какие вершины посещены(false - не посещена)
  std::vector<bool> visitedVert; 
  //массив, хранящий в себе пройденный путь
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
