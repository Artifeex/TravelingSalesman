#include "NearestNeighboor.h"

int NearestNeighboor::FindMinDistanceVert(int vert)
{
  int minRoute = INT_MAX;
  int minVert = -1;
  std::vector<int> availableVert;
  for (size_t i = 0; i < visitedVert.size(); i++)
  {
    if (visitedVert[i] == false)
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

void NearestNeighboor::SetMatrix(const AdjacencyMatrixG<int>& matr)
{
  matrix = matr;
  minPath = 0;
  visitedOrder.clear();
  visitedVert.clear();
  visitedVert.resize(matr.GetCountVertices(), false);
  visitedOrder.resize(matr.GetCountVertices());
}

void NearestNeighboor::SetMatrix(const Matrix<int>& m)
{
  matrix = m;
  minPath = 0;
  visitedOrder.clear();
  visitedVert.clear();
  visitedVert.resize(matrix.GetCountVertices());
  visitedOrder.resize(matrix.GetCountVertices(), false);
}

void NearestNeighboor::Run()
{
  int currentVert = startVert;
  int countVert = matrix.GetCountVertices();
  visitedOrder[0] = startVert;
  visitedVert[0] = true;
  for (size_t i = 1; i < countVert; i++)
  {
    int nextVert = FindMinDistanceVert(currentVert);
    visitedVert[nextVert] = true;
    visitedOrder[i] = nextVert;
    minPath += matrix[currentVert][nextVert];
    currentVert = nextVert;
  }
  minPath += matrix[currentVert][startVert];
  visitedOrder.push_back(startVert);
}
