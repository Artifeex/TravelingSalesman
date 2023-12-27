#include "TwoOpt.h"

int TwoOpt::calculateCost(const std::vector<int>& curPath)
{
  int cost = 0;
  for (size_t i = 0; i < curPath.size() - 1; i++)
  {
    cost += matrix[curPath[i]][curPath[i + 1]];
  }
  return cost;
}

void TwoOpt::TwoOptSwap(std::vector<int>& tmpPath, int i, int j)
{
  //������������ �������
  auto first = tmpPath.begin();
  std::reverse(first + i, first + j);
}

void TwoOpt::TwoOptUndoSwap(std::vector<int>& tmpPath, int i, int j)
{
  //������������ �������
  auto first = tmpPath.begin();
  std::reverse(first + i, first + j);
}



void TwoOpt::SetMatrix(const AdjacencyMatrixG<int>& matr)
{
  matrix = matr;
  minPathValue = 0;
  path.clear();
}

void TwoOpt::SetMatrix(const Matrix<int>& m)
{

}


void TwoOpt::Run()
{
  //��� ��������� ������ ��� ����� �����-������ ������, ������� �� ����� ��������
  //� �������� ���������, ������� ����� ��� �������� ��������� ������� ���������� 
  //�������� ���������� ������
  auto alg = NearestNeighboor();
  //������������� ��� ��������� ���������� ������ ������� ��������� � ��������� ���
  alg.SetMatrix(matrix);
  alg.Run();
  //�������� ���������� ������ ��������� ���������� ������ � ��� �������
  auto firstPath = alg.GetMinRoute();
  auto curLength = alg.GetMinWeight();
  //������ ������������� �������
  int n = firstPath.size();
  //����, ���������� �� ��, ���������� �� ���-���� �������� �� ������� ��������
  bool isOptimal = false;
  //�������� ���� ��������� 2-opt. ��������� �� ��� ���, ���� ������ �������� �������
  //����� ���������
  while (!isOptimal) {
    isOptimal = true;
    //���� �� ���� ��������� ��������
    for (int i = 1; i < n - 1; i++) {
      for (int j = i + 1; j < n - 1; j++) {
        //������ ������� ��� ������� � �������� ����� �����
        TwoOptSwap(firstPath, i, j + 1);
        //������� ����� ��������� ��� ���������� ������������
        int newCost = calculateCost(firstPath);
        //��������� � ���������� ������ ��������� � ������, ���� ������������ ���� ���������
        if (newCost < curLength) {
          isOptimal = false;
          curLength = newCost;
        }
        //���� ������������ �� ���� ��������� ���������� ������� �������
        else {
          TwoOptUndoSwap(firstPath, i, j + 1);
        }

        //��� �������� ������ � ������ ��������� ������� ���������
        /*
        * int lengthDelta = -matrix[firstPath[i]][firstPath[(i + 1) % n]] - matrix[firstPath[j]][firstPath[(j + 1) % n]]
          + matrix[firstPath[i]][firstPath[j]] + matrix[(i + 1) % n][firstPath[(j + 1) % n]];

        if (lengthDelta < 0) {
          TwoOptSwap(firstPath, i, j);
          curLength += lengthDelta;
        }
      }
        */
      }
    }
  }
  //���������� ������ ���������
  minPathValue = curLength;
  path = firstPath;
}
