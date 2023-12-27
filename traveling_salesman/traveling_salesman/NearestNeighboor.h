#pragma once
#include "Algorithm.h"
#include "AdjacencyMatrixG.h"
#include <algorithm>
#include <vector>
//O(n^2)
class NearestNeighboor: public Algorithm
{
private:
  //������� ���������
  AdjacencyMatrixG<int> matrix; 
  //������ ������������ ����� ������� ��������(false - �� ��������)
  std::vector<bool> visitedVert; 
  //������, �������� � ���� ���������� ����
  std::vector<int> visitedOrder;
  int minPath = 0;
  int startVert;

  int FindMinDistanceVert(int vert);
public:
  NearestNeighboor(int _startVert = 0):
    startVert(_startVert) {
    algName = "���������� ������";
  }

  void SetMatrix(const AdjacencyMatrixG<int>& matr) override;
  void SetMatrix(const Matrix<int>& m);

  void Run() override;
  int GetMinWeight() override { return minPath; }
  std::vector<int> GetMinRoute() override { return visitedOrder; }

};
