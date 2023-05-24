#pragma once
#include "Algorithm.h"
#include "AdjacencyMatrixG.h"
#include <vector>
#include <list>

using std::pair;

class LittleAlg: public Algorithm
{
private:
  AdjacencyMatrixG<int> matrix;
  int infinity = INT_MAX - 1;
  int curRecord;
  std::vector<int> bestOrder;
  std::list<pair<int, int>> bestTreePath;
  int solution = INT_MAX - 1;

  void HandleMatrix(const AdjacencyMatrixG<int>& m,
    const std::list<pair<int, int> >& currentPath, int bottomLimit, bool hasAdje);

  //�������� ����������� �������� �� ������� � ��������. ���������� ����� ���� ��� ���������
  int ReduceMatrix(AdjacencyMatrixG<int>& curMatrix);
  
  //���������� ������������ ��� �������� ��������
  int CalculateCoeff(AdjacencyMatrixG<int>& curMatrix, int row, int column);

  //������� ������ �������� � ���������� ������� ��� ������� ��������� �������
  void GetBestZero(AdjacencyMatrixG<int>& matrix, int& row, int& column);

  //��������� ���������� �������
  void CandidateSolution(const std::list<pair<int, int>>& curSolution);

  //������� ����� ��������� ����
  int CalculatePrice(const std::list<pair<int, int>>& path);

  void ConvertResult();

  void AddInfinity(AdjacencyMatrixG<int>& m);
public:
  LittleAlg(int _record): curRecord(_record) {
    algName = "������ � ������";
  }

  void SetMatrix(const AdjacencyMatrixG<int>& m) override;
  void Run() override;
  int GetMinWeight() override { return solution; }
  std::vector<int> GetMinRoute() override { return bestOrder; }

};

