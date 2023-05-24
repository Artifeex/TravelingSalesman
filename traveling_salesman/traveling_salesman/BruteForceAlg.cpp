#include "BruteForceAlg.h"

void BruteForceAlg::Run()
{
  std::vector<int> curRoad;
  std::vector<int> bestCurRoad;
  int n = matrix[0].size();
  size_t sourceVert = 0;
	// создаем самую маленькую перестановку в лексикографическом порядке
	for (size_t i = 0; i < n; i++)
	  if (i != sourceVert)
		curRoad.push_back(i);
	// генеририуем все перестановки отличных от начальной вершины
	do
	{
	  int pathWeight = 0;
	  int curVert = sourceVert;

	  for (size_t i = 0; i < curRoad.size(); i++)
	  {
		pathWeight += matrix[curVert][curRoad[i]];
		curVert = curRoad[i];
	  }
	  //замыкание
	  pathWeight += matrix[curVert][sourceVert];

	  if (shortestValuePath > pathWeight)
	  {
		shortestValuePath = pathWeight;
		shortestPath.clear();
		shortestPath.push_back(sourceVert);
		shortestPath.insert(shortestPath.begin() + 1, curRoad.begin(), curRoad.end());
		shortestPath.push_back(sourceVert);
	  }
	}while (std::next_permutation(curRoad.begin(), curRoad.end()));
}

void BruteForceAlg::SetMatrix(const AdjacencyMatrixG<int>& m)
{
  matrix = m;
  shortestValuePath = INT_MAX;
  shortestPath.clear();
}

void BruteForceAlg::SetMatrix(const Matrix<int>& m)
{
  matrix = m;
  shortestValuePath = INT_MAX;
  shortestPath.clear();
}

BruteForceAlg::BruteForceAlg()
{
  shortestValuePath = INT_MAX;
  algName = "Полный перебор";
}


int BruteForceAlg::GetMinWeight()
{
  return shortestValuePath;
}

std::vector<int> BruteForceAlg::GetMinRoute()
{
  return shortestPath;
}

void BruteForceAlg::SetNameAlg(std::string _nameAlg)
{
  algName = _nameAlg;
}
