#include "AntColonyAlg.h"

double AntColonyAlg::CalculateProbabilityTransition(int i, int j, double probabilitySum) // P_i_j
{
  double desireTransition = CalculateDesireTransition(i, j);
  double sumProbabilityTransition = probabilitySum;

  return desireTransition / sumProbabilityTransition;
}

double AntColonyAlg::CalculateSumProbabilityTransition(int start) //����������� ��� ������� P
{
  double result = 0;
  std::vector<int> curFreeVert = GetCurFreeVert();
  if (curFreeVert.size() == 0)
	return 1.0;
  for (const auto& vertex : curFreeVert)
  {
	result += CalculateDesireTransition(start, vertex);
  }
  return result;
}

double AntColonyAlg::CalculateDesireTransition(int i, int j) // ��������� ��� ������� P
{
  double amountPheromore = matrix[i][j].GetPheromone();
  double closeness = matrix[i][j].GetCloseness();

  return pow(amountPheromore, alfa) * pow(closeness, beta);
}

void AntColonyAlg::UpdateProbabilityTransition(int start)
{
  double sumProb = CalculateSumProbabilityTransition(start);
  for (const auto& vert : GetCurFreeVert())
  {
	matrix[start][vert].ChangeProbabilityTransition(
	  CalculateProbabilityTransition(start, vert, sumProb));
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
	for (size_t j = i; j < matrix.GetCountVertices(); j++)
	{
	  //1. ��������� ��������
	  matrix[i][j].ChangePheromone(matrix[i][j].GetPheromone() * pheromoneResidue);
	}
  }
  //2. ���������� �������� �� �������� ��������
  // road[k].size() - 1 - ����� �������� ��������� �������, � ������� �������� ����� ��������
  for (size_t k = 0; k < countAnts; k++)
  {
	for (size_t i = 0; i < road[k].size(); i++)
	{
	  matrix[road[k][i]][road[k][i + 1]].ChangePheromone(matrix[road[k][i]][road[k][i + 1]].GetPheromone()
		+ pheromoneConst / road[k][road[k].size() - 1]);
	}
  }
}

std::vector<int> AntColonyAlg::GetCurFreeVert()
{
  std::vector<int> freeVert;
  for (size_t i = 0; i < vertVisitStat.size(); i++)
  {
	if (vertVisitStat[i] == 0)
	  freeVert.push_back(i);
  }
  return freeVert;
}

void AntColonyAlg::Run()
{
  //��� ������ �������
  int startVer = 0;
  
  // �������� ���-�� �������� ��� ������ ��������� ��� �������� �������
  for (size_t numberAnt = 0; numberAnt < countAnts; numberAnt++)
  {
	//����� ���� �������� ���� ������, ��� ������ ��� �������
	startVer = numberAnt % matrix.GetCountVertices();
	vertVisitStat[startVer] = 1; // ������� �� ����������
	// � ���� ����� ������ ������ �������
	for (size_t i = 0; i < matrix.GetCountVertices(); i++)
	{
	  road[numberAnt][i] = startVer; // �������� � �������

	  // �������� ��� ������� ������� � ������� � ������� �� ��������� ���-�� �������� � ������ �������
	  UpdateProbabilityTransition(startVer); 
	  // �� ������ ����� ���-��� ������� ����� �������
	  int nextVert = SelectVert(startVer); // ������� ������� ��� ��������
	  // ���������� ������� � ����� ������� � �������, ��� ��� ����� ���������
	  // ����� ������ ���-�� ��������� � ���, ��� ��������� ���� �������, ����� �������� ��������
	  road[numberAnt][road[numberAnt].size() - 1] += matrix[startVer][nextVert].GetWeight(); // ��������� � ����� �����
	  startVer = nextVert;
	  vertVisitStat[startVer] = 1; //�������� ����������
	}
	road[numberAnt][matrix.GetCountVertices()] = numberAnt; // ����� ��������
	road[numberAnt][road[numberAnt].size() - 1] += matrix[startVer][numberAnt].GetWeight();
	if (minRoad > road[numberAnt][road[numberAnt].size() - 1])
	  minRoad = road[numberAnt][road[numberAnt].size() - 1];
	// ������� ����� �� ���������� ��������
	for (size_t i = 0; i < vertVisitStat.size(); i++)
	{
	  vertVisitStat[i] = 0;
	}
  }
  UpdatePheromones();
  
}


AntColonyAlg::AntColonyAlg(const AdjacencyMatrixG<int>& _matrix, double _alfa, double _beta,
  double _startPheromone, double _Q, int _countAnts,
  double _pheromoneResidue, double _pheromoneConst) :matrix(_matrix.GetCountVertices())
{
  alfa = _alfa;
  beta = _beta;
  _startPheromone = _startPheromone;
  Q = _Q;
  countAnts = _countAnts;
  pheromoneResidue = _pheromoneResidue;
  minRoad = INT_MAX;
  pheromoneConst = _pheromoneConst;
  road.resize(countAnts);
  vertVisitStat.resize(matrix.GetCountVertices());
  for (size_t i = 0; i < countAnts; i++) 
  {
	road[i].resize(matrix.GetCountVertices() + 2); // ��� ����� ��� �������� ����
	// +2 - ���� ��� ��������� ��������, � ������ ��� �������� ����� ��������
  }
  for (size_t i = 0; i < _matrix.GetCountVertices(); i++)
  {
	for (size_t j = i; j < _matrix.GetCountVertices(); j++)
	{
	  if (i == j)
		this->matrix[i][j] = AntColonyCell(infinity, 0.0, infinity);
	  else
	  {
		this->matrix[i][j] = AntColonyCell(Q / _matrix[i][j], _startPheromone, _matrix[i][j]);
		// ��� ��� ������������
		//this->matrix[j][i] = AntColonyCell(Q / _matrix[i][j], _startPheromone);
	  }
	}
  }
}

int AntColonyAlg::GetMinRoad()
{
  return minRoad;
}
