#pragma once
#include "Algorithm.h"
#include "AdjacencyMatrixG.h"
#include "AntColonyCell.h"
#include <cmath>
#include <float.h>

class AntColonyAlg : public Algorithm
{
  
private:
  double alfa; // ������� ���������� ��������� �� ����� �������
  double beta; //������� �������� ������� �� ����� �������
  double pheromoneResidue; // ������� �������� �������� ����� ����� ��������
  int countAnts;
  std::vector<int> vertVisitStat; // ��� ����������� ��������� ������ ��� ������ �������
  std::vector<std::vector<int>> road;// ��� ������������ �����, �� ������� ������ ������� ��� ���-� ���-��
  AdjacencyMatrixG<AntColonyCell> matrix;

  int minRoad;
  double Q; // ��� ��������
  double pheromoneConst; // ������� �������� ������� ������� �������� �� ���� ����
  const double infinity = DBL_MAX;
  //������
  std::vector<int> GetCurFreeVert();
  // ������ � ������������
  double CalculateProbabilityTransition(int i, int j, double probabilitySum); 
  double CalculateSumProbabilityTransition(int start); 
  double CalculateDesireTransition(int i, int j); // ��� �������� �� q 
  void UpdateProbabilityTransition(int start);

  int SelectVert(int start);
  //������ � ���������
  void UpdatePheromones();
  
public:
  void Run() override;
  AntColonyAlg(const AdjacencyMatrixG<int>& matrix, double _alfa=1.0, double _beta = 1.0,
	double _startPheromone = 0.2, double _Q = 200, int _countAnts = 5, 
	double _pheromoneResidue = 0.6, double _pheromoneConst = 4);
  int GetMinRoad();
};

