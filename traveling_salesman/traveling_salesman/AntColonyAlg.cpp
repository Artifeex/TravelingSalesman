#include "AntColonyAlg.h"

double AntColonyAlg::CalculateProbabilityTransition(int i, int j)
{
  double desireTransition = CalculateDesireTransition(i, j);
  double sumProbabilityTransition = CalculateSumProbabilityTransition(i);

  return desireTransition / sumProbabilityTransition;
}

double AntColonyAlg::CalculateSumProbabilityTransition(int start)
{
  double result;
	for (const auto& vertex : currentFreeVertecies)
	  result += CalculateDesireTransition(start, vertex);
  return result;
}

double AntColonyAlg::CalculateDesireTransition(int i, int j)
{
  double amountPheromore = matrix[i][j].GetPheromone();
  double closeness = matrix[i][j].GetCloseness();

  return pow(amountPheromore, alfa) * pow(closeness, beta);
}

void AntColonyAlg::Run()
{
  //Для одного муравья
  int startVer = 0;
  // Расчитал вер-ть перехода для каждой возможной для перехода вершины
  for (const auto& freeVert : currentFreeVertecies)
  {
	matrix[startVer][freeVert].ChangeProbabilityTransition(
	  CalculateProbabilityTransition(startVer, freeVert));
  }

}

AntColonyAlg::AntColonyAlg(const AdjacencyMatrixG<int>& _matrix, double _alfa = 1.0, double _beta = 1.0,
  double _startPheromone = 0.2, double _Q = 200, int _countAnts = 5,
  double _pheromoneResidue = 0.6)
{
  alfa = _alfa;
  beta = _beta;
  _startPheromone = _startPheromone;
  Q = _Q;
  countAnts = _countAnts;
  pheromoneResidue = _pheromoneResidue;

  for (size_t i = 0; i < _matrix.GetCountVertices(); i++)
  {
	currentFreeVertecies.push_back(i);
  }
  for (size_t i = 0; i < _matrix.GetCountVertices(); i++)
  {
	for (size_t j = i; j < _matrix.GetCountVertices() - i; j++)
	{
	  if (i == j)
		this->matrix[i][j] = AntColonyCell(infinity, 0.0);
	  else
	  {
		this->matrix[i][j] = AntColonyCell(Q / _matrix[i][j], _startPheromone);
		// Так как симметричная
		this->matrix[j][i] = AntColonyCell(Q / _matrix[i][j], _startPheromone);
	  }
	}
  }
}
