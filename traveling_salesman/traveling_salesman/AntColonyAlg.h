#pragma once
#include "Algorithm.h"
#include "AdjacencyMatrixG.h"
#include "AntColonyCell.h"

class AntColonyAlg : public Algorithm
{
private:
  double alfa; // ������� ���������� ��������� �� ����� �������
  double beta; //������� �������� ������� �� ����� �������
  AdjacencyMatrixG<AntColonyCell> matrix;
public:
  void Run() override;
  AntColonyAlg(AdjacencyMatrixG<int> matrix);
};

