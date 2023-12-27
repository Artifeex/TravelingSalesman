#include "AntColonyAlg.h"

double AntColonyAlg::ProbabilityTransition(int i, int j, double probabilitySum) // P_i_j
{
  const double desireTransition = DesireTransition(i, j);
  const double sumProbabilityTransition = probabilitySum;

  return desireTransition / sumProbabilityTransition;
}

double AntColonyAlg::SumProbabilityTransition(int start) //����������� ��� ������� P
{
  double result = 0;
  for (const auto& vertex : GetCurFreeVert())
    result += DesireTransition(start, vertex);

  return result;
}

double AntColonyAlg::DesireTransition(int i, int j) // ��������� ��� ������� P
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
  double r = (double)(rand()) / RAND_MAX; // ������������� �����, � ������� �������� ����� �������� �������
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
      //1. ��������� ��������
      matrix[i][j].ChangePheromone(matrix[i][j].GetPheromone() * pheromoneResidue);
    }
  }
  double supplementPheromone = 0.0; // �������, ���������� �� ���� ��������
  double lastPheromone = 0.0; //������ �������� ��������
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

void AntColonyAlg::ClearAntRoute()
{
  for (size_t i = 0; i < antRoute.size(); i++)
  {
    for (size_t j = 0; j < antRoute[i].size(); j++)
    {
      antRoute[i][j] = 0;
    }
  }
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

void AntColonyAlg::SetNameAlg(std::string _nameAlg)
{
  algName = _nameAlg;
}

void AntColonyAlg::Run()
{
  //����, ������� ����������� �������� ����� ��������
  for (size_t i = 0; i < countIterations; i++)
  {
    //��������� �������
    int startVer = 0;
    //��������� ������� ��� ��������
    int nextVert = 0;
    //����, ������� ��������� ������ ������� �������
    for (size_t numberAnt = 0; numberAnt < countAnts; numberAnt++)
    {
      //����� ��������� �������. � ������ ������ �� ������� ������� ��������� �� ����� �������
      //�� ���� �������� ������, ��� ����� ������, �� �� ���� ������� �� ������ ��������� �������
      //����� �������� ���� ������ �� ���������� ������
      startVer = numberAnt % countVertecies;
      //�������� ������� �������, � ������� ��������� ������� ��� ����������
      visitedVertecies[startVer] = 1;
      //��������� ������� ������� � �������
      antRoute[numberAnt][0] = startVer;
      //���� ������ � ���������
      for (size_t i = 1; i < countVertecies; i++)
      {
        //������� ����������� ��������� �� ������� ������� � ��� �� ����������
        UpdateProbabilityTransition(startVer);
        //�������� ��������� ��� �������� ������� �� ������ ����������� ����� �����������
        nextVert = SelectVert(startVer);
        //�������� ��������� ������� ��� ����������
        visitedVertecies[nextVert] = 1;
        //��������� ��������� ������� � �������
        antRoute[numberAnt][i] = nextVert;
        //����������� ��� ���� �������� �������
        antRoute[numberAnt][weightIndex] += matrix[startVer][nextVert].GetWeight();
        startVer = nextVert;
      }
      //��������� ��������� ������� ��� ��������� ��������
      antRoute[numberAnt][countVertecies] = numberAnt % countVertecies;
      //��������� ��� ���������� �������� ��� ��������� ��������
      antRoute[numberAnt][weightIndex] += matrix[startVer][numberAnt % countVertecies].GetWeight();
      //�������� ������� ���������� ������
      ClearVisitedVert();
    }
    //��������� �������� ��� ��������� ��������
    UpdatePheromones();
    //�������� ����������� ������ � � ������ ���������, ���������� ������� ����������
    UpdateResults();
    //�������� ��������, ���������� ���� ������� ��������
    ClearAntRoute();
  }
}

void AntColonyAlg::SetMatrix(const AdjacencyMatrixG<int>& adjacencyMatr)
{
  matrix = AdjacencyMatrixG<AntColonyCell>(adjacencyMatr.GetCountVertices());
  countVertecies = adjacencyMatr.GetCountVertices();
  visitedVertecies.resize(countVertecies);
  weightIndex = countVertecies + 1;
  for (size_t i = 0; i < countAnts; i++)
    antRoute[i].resize(weightIndex + 1); // + 1 ��-�� ��� ������� � ���������

  for (size_t i = 0; i < adjacencyMatr.GetCountVertices(); i++)
  {
    for (size_t j = 0; j < adjacencyMatr.GetCountVertices(); j++)
    {
      if (i == j)
        matrix[i][j] = AntColonyCell(DBL_MAX, 0.0, INT_MAX);
      else
      {
        matrix[i][j] = AntColonyCell(closConst / adjacencyMatr[i][j], startPheromone, adjacencyMatr[i][j]);
        matrix[j][i] = AntColonyCell(closConst / adjacencyMatr[j][i], startPheromone, adjacencyMatr[j][i]);
      }

    }
  }
}

AntColonyAlg::AntColonyAlg(double _alfa, double _beta,
  double _startPheromone, double _Q, int _countAnts,
  double _pheromoneResidue, double _pheromoneConst, int _countIterations)
{
  alfa = _alfa;
  beta = _beta;
  startPheromone = _startPheromone;
  closConst = _Q;
  countIterations = _countIterations;
  countAnts = _countAnts;
  pheromoneResidue = _pheromoneResidue;
  pheromoneConst = _pheromoneConst;
  algName = "���������� ��������";

  antRoute.resize(countAnts);
  minWeightRoute = INT_MAX;
}

void AntColonyAlg::UpdateBestRoute()
{
  if (minWeightRoute > CalculateMinWeight())
    bestRoute = CalculateMinRoute();
}

void AntColonyAlg::UpdateBestRouteWeight()
{
  if (minWeightRoute > CalculateMinWeight())
    minWeightRoute = CalculateMinWeight();
}

int AntColonyAlg::GetMinWeight()
{
  return minWeightRoute;
}

std::vector<int> AntColonyAlg::GetMinRoute()
{
  return bestRoute;
}

int AntColonyAlg::CalculateMinWeight() noexcept
{
  int localMinRoad = INT_MAX;
  for (size_t i = 0; i < countAnts; i++)
  {
    if (antRoute[i][weightIndex] < localMinRoad)
      localMinRoad = antRoute[i][weightIndex];
  }
  return localMinRoad;
}

std::vector<int> AntColonyAlg::CalculateMinRoute()
{
  int index = -1;
  for (size_t i = 0; i < countAnts; i++)
  {
    if (antRoute[i][weightIndex] == minWeightRoute)
    {
      index = i;
    }
  }
  return std::vector<int>(antRoute[index].begin(), antRoute[index].begin() + weightIndex);
}

void AntColonyAlg::UpdateResults()
{
  if (minWeightRoute > CalculateMinWeight()) {
    minWeightRoute = CalculateMinWeight();
    bestRoute = CalculateMinRoute();
  }
}
