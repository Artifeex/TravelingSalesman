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
  int infinity = INT_MAX;
  int curRecord;
  std::vector<int> bestOrder;
  std::list<pair<int, int>> bestTreePath;
  int solution = INT_MAX;

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
  LittleAlg(const AdjacencyMatrixG<int>& m, int _record) : matrix(m),
    curRecord(_record) {}

  
  void Run() override;
  int GetMinWeight() override { return solution; }
  std::vector<int> GetMinRoute() override { return bestOrder; }

};

