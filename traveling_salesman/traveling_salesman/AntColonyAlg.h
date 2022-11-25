#pragma once
#include "Algorithm.h"
#include "AdjacencyMatrixG.h"
#include "AntColonyCell.h"
#include <cmath>
#include <float.h>
#include <valarray>

class AntColonyAlg : public Algorithm
{
private:
  double alfa; // ������� ���������� ��������� �� ����� �������
  double beta; //������� �������� ������� �� ����� �������
  double pheromoneResidue; // ������� �������� �������� ����� ����� ��������
  int countAnts;
  int countVertecies;
  std::vector<int> visitedVertecies; // ��� ����������� ��������� ������ ��� ������ �������
  std::vector<std::vector<int>> antRoute;// ��� ������������ �����, �� ������� ������ ������� ��� ���-� ���-��
  AdjacencyMatrixG<AntColonyCell> matrix;
  int weightIndex; // ��������� �� ��������� ���� ����� �������� �������
  int minRoad;
  double Q; // ��� ��������
  double pheromoneConst; // ������� �������� ������� ������� �������� �� ���� ����

  //������
  std::vector<int> GetCurFreeVert();
  // ������ � ������������
  double ProbabilityTransition(int i, int j, double probabilitySum); 
  double SumProbabilityTransition(int start); 
  double DesireTransition(int i, int j); // ��� �������� �� q 
  void UpdateProbabilityTransition(int start);
  int SelectVert(int start);
  void UpdatePheromones();
  void ClearVisitedVert();
public:
  void Run() override;
  AntColonyAlg(const AdjacencyMatrixG<int>& matrix, double _alfa=1.0, double _beta = 1.0,
	double _startPheromone = 0.2, double _Q = 200, int _countAnts = 3, 
	double _pheromoneResidue = 0.6, double _pheromoneConst = 4);
  int GetMinRoad() noexcept;
  std::vector<int> GetMinPath();
};

