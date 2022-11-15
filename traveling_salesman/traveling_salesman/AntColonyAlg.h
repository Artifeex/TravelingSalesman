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

  AdjacencyMatrixG<AntColonyCell> matrix;
  std::vector<int> currentFreeVertecies; // ������ ������� ��� �� ���������� ������ ��� �������� �������

  double Q;
  const double infinity = DBL_MAX;
  //������
  
  // ������ � ������������
  double CalculateProbabilityTransition(int i, int j); 
  double CalculateSumProbabilityTransition(int start); 
  double CalculateDesireTransition(int i, int j); 

  //������ � ���������
  
public:
  void Run() override;
  AntColonyAlg(const AdjacencyMatrixG<int>& matrix,double _alfa=1.0, double _beta = 1.0,
	double _startPheromone = 0.2, double _Q = 200, int _countAnts = 5, 
	double _pheromoneResidue = 0.6);
};

