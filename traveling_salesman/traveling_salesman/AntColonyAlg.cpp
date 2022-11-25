#include "AntColonyAlg.h"

double AntColonyAlg::ProbabilityTransition(int i, int j, double probabilitySum) // P_i_j
{
  const double desireTransition = DesireTransition(i, j);
  const double sumProbabilityTransition = probabilitySum;

  return desireTransition / sumProbabilityTransition;
}

double AntColonyAlg::SumProbabilityTransition(int start) //знаметатель для формулы P
{
  double result = 0;
  for (const auto& vertex : GetCurFreeVert())
	result += DesireTransition(start, vertex);

  return result;
}

double AntColonyAlg::DesireTransition(int i, int j) // числитель для формулы P
{
  const double amountPheromore = matrix[i][j].GetPheromone();
  const double closeness = matrix[i][j].GetCloseness();

  return pow(amountPheromore, alfa) * pow(closeness, beta);
}

void AntColonyAlg::UpdateProbabilityTransition(int start)
{
  double sumProb = SumProbabilityTransition(start);
  std::vector<int> freeVert = GetCurFreeVert();
  if (freeVert.size() == 1)
  {
	matrix[start][freeVert[0]].ChangeProbabilityTransition(1.0);
	return;
  }
  for (const auto& vert : freeVert)
  {
	matrix[start][vert].ChangeProbabilityTransition(
	  ProbabilityTransition(start, vert, sumProb));
  }
}

int AntColonyAlg::SelectVert(int start)
{
  double lenta = 0.0;
  srand(time(0));
  double r = (double)(rand()) / RAND_MAX; // сгенерировали число, с помощью которого будет выбирать вершину
  for (const auto& freeVert : GetCurFreeVert())
  {
	lenta += matrix[start][freeVert].GetProbability();
	if (r > lenta)
	  continue;
	else
	{
	  return freeVert;
	}
  }
  return -1;
}

void AntColonyAlg::UpdatePheromones()
{
  for (size_t i = 0; i < matrix.GetCountVertices(); i++)
  {
	for (size_t j = 0; j < matrix.GetCountVertices(); j++)
	{
	  //1. Испарение феромона
	  matrix[i][j].ChangePheromone(matrix[i][j].GetPheromone() * pheromoneResidue);
	}
  }
  double supplementPheromone = 0.0; // Добавка, полученная от всех муравьев
  double lastPheromone = 0.0; //старое значение феромона
  int vert1 = 0;
  int vert2 = 0;

  for (size_t numberAnt = 0; numberAnt < countAnts; numberAnt++)
  {
	for (size_t i = 0; i < countVertecies; i++)
	{
	  vert1 = antRoute[numberAnt][i];
	  vert2 = antRoute[numberAnt][i + 1];

	  lastPheromone = matrix[vert1][vert2].GetPheromone();
	  supplementPheromone = pheromoneConst / antRoute[numberAnt][countVertecies + 1];

	  matrix[vert1][vert2].ChangePheromone(lastPheromone + supplementPheromone);
	}
  }
}

void AntColonyAlg::ClearVisitedVert()
{
  for (size_t i = 0; i < visitedVertecies.size(); i++)
	visitedVertecies[i] = 0;
}

std::vector<int> AntColonyAlg::GetCurFreeVert()
{
  std::vector<int> freeVert;
  for (size_t i = 0; i < visitedVertecies.size(); i++)
  {
	if (visitedVertecies[i] == 0)
	  freeVert.push_back(i);
  }
  return freeVert;
}

void AntColonyAlg::Run()
{
  int startVer = 0;
  int nextVert = 0;
  for (size_t numberAnt = 0; numberAnt < countAnts; numberAnt++)
  {
	startVer = numberAnt % countVertecies;
	visitedVertecies[startVer] = 1;
	antRoute[numberAnt][0] = startVer;

	for (size_t i = 1; i < countVertecies; i++)
	{

	  UpdateProbabilityTransition(startVer); 
	  nextVert = SelectVert(startVer); 

	  visitedVertecies[nextVert] = 1;
	  antRoute[numberAnt][i] = nextVert;
	  antRoute[numberAnt][weightIndex] += matrix[startVer][nextVert].GetWeight();
	  startVer = nextVert;
	}
	antRoute[numberAnt][countVertecies] = numberAnt % countVertecies;
	antRoute[numberAnt][weightIndex] += matrix[startVer][numberAnt % countVertecies].GetWeight();
	
	ClearVisitedVert();
  }
  UpdatePheromones();

}


AntColonyAlg::AntColonyAlg(const AdjacencyMatrixG<int>& adjacencyMatr, double _alfa, double _beta,
  double _startPheromone, double _Q, int _countAnts,
  double _pheromoneResidue, double _pheromoneConst) :matrix(adjacencyMatr.GetCountVertices())
{
  alfa = _alfa;
  beta = _beta;
  _startPheromone = _startPheromone;
  Q = _Q;
  countAnts = _countAnts;
  pheromoneResidue = _pheromoneResidue;
  pheromoneConst = _pheromoneConst;
  algName = "AntAlg";
  countVertecies = adjacencyMatr.GetCountVertices();
  visitedVertecies.resize(countVertecies);
  antRoute.resize(countAnts);
  minRoad = INT_MAX;
  weightIndex = countVertecies + 1;
  for (size_t i = 0; i < countAnts; i++) 
	antRoute[i].resize(weightIndex + 1); // + 1 из-за доп вершины в замыкании

  for (size_t i = 0; i < adjacencyMatr.GetCountVertices(); i++)
  {
	for (size_t j = 0; j < adjacencyMatr.GetCountVertices(); j++)
	{
	  if (i == j)
		matrix[i][j] = AntColonyCell(DBL_MAX, 0.0, INT_MAX);
	  else
	  {
		matrix[i][j] = AntColonyCell(Q / adjacencyMatr[i][j], _startPheromone, adjacencyMatr[i][j]);
		matrix[j][i] = AntColonyCell(Q / adjacencyMatr[j][i], _startPheromone, adjacencyMatr[j][i]);
	  }
		
	}
  }
}

int AntColonyAlg::GetMinRoad() noexcept
{
  for (size_t i = 0; i < countAnts; i++)
  {
	if (antRoute[i][weightIndex] < minRoad)
	  minRoad = antRoute[i][weightIndex];
  }
  return minRoad;
}

std::vector<int> AntColonyAlg::GetMinPath()
{
  int index = -1;
  for (size_t i = 0; i < countAnts; i++)
  {
	if (antRoute[i][weightIndex] == minRoad)
	{
	  minRoad = antRoute[i][weightIndex];
	  index = i;
	}
  }
  return std::vector<int>(antRoute[index].begin(), antRoute[index].begin() + weightIndex);
}
