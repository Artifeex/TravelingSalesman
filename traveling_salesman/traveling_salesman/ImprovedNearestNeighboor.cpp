#include "ImprovedNearestNeighboor.h"

int ImprovedNearestNeighboor::FindMinDistanceVert(int vert, const std::vector<bool>& tmpVisitedVert)
{
  int minRoute = INT_MAX;
  int minVert = -1;
  std::vector<int> availableVert;
  for (size_t i = 0; i < tmpVisitedVert.size(); i++)
  {
    if (tmpVisitedVert[i] == false)
      availableVert.push_back(i);
  }
  for (size_t i = 0; i < availableVert.size(); i++)
  {
    if (minRoute > matrix[vert][availableVert[i]])
    {
      minRoute = matrix[vert][availableVert[i]];
      minVert = availableVert[i];
    }
  }
  return minVert;
}

void ImprovedNearestNeighboor::SetMatrix(const AdjacencyMatrixG<int>& matr)
{
  matrix = matr;
  visitedOrder.clear();
  visitedVert.clear();
  visitedVert.resize(matr.GetCountVertices(), false);
  visitedOrder.resize(matr.GetCountVertices());
  bestResult = INT_MAX;
}

void ImprovedNearestNeighboor::SetMatrix(const Matrix<int>& m)
{
  matrix = m;
  visitedVert.resize(matrix.GetCountVertices());
  visitedOrder.resize(matrix.GetCountVertices(), false);
}

void ImprovedNearestNeighboor::Run()
{
  for (size_t i = 0; i < matrix.GetCountVertices(); i++)
  {
    int minPath = 0;
    int startVert = i;
    int currentVert = startVert;
    int countVert = matrix.GetCountVertices();
    std::vector<int> tmpVisitedOrder(countVert);
    std::vector<bool> tmpVisitedVert(countVert, false);
    tmpVisitedOrder[0] = startVert;
    tmpVisitedVert[i] = true;
    for (size_t i = 1; i < countVert; i++)
    {
      int nextVert = FindMinDistanceVert(currentVert, tmpVisitedVert);
      tmpVisitedVert[nextVert] = true;
      tmpVisitedOrder[i] = nextVert;
      minPath += matrix[currentVert][nextVert];
      currentVert = nextVert;
    }
    minPath += matrix[currentVert][startVert];
    tmpVisitedOrder.push_back(startVert);
    if (bestResult > minPath) {
      bestResult = minPath;
      visitedOrder = tmpVisitedOrder;
    }
  }
}
