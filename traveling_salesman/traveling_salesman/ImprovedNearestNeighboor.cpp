#include "ImprovedNearestNeighboor.h"

int ImprovedNearestNeighboor::FindMinDistanceVert(int vert, const std::vector<bool> tmpVisitedVert)
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
    for (size_t j = 1; j < countVert; j++)
    {
      int nextVert = FindMinDistanceVert(currentVert, tmpVisitedVert);
      tmpVisitedOrder[j] = nextVert;
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
