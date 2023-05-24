#include "LittleAlg.h"

void LittleAlg::SetMatrix(const AdjacencyMatrixG<int>& m)
{
  matrix = m;
  curRecord = INT_MAX - 1;
  solution = INT_MAX - 1;
  bestOrder.clear();
  bestTreePath.clear();
}

void LittleAlg::Run() {
  std::list<pair<int, int>> curPath;
  HandleMatrix(matrix, curPath, 0, true);
  ConvertResult();
}

void LittleAlg::HandleMatrix(const AdjacencyMatrixG<int>& m,
  const std::list<pair<int, int> >& currentPath, int bottomLimit, bool hasAdje)
{
  if (m.GetCountRows() == 2) {
    //����������� ����� ����

    //�������� ������� �� 0 ������, ������� �� ����� �������������
    int columnIndex = m[0][0] >= infinity ? 1 : 0;
    std::list<pair<int, int> > resultPath(currentPath);
    resultPath.emplace_back(m.RowIndex(0), m.ColumnIndex(columnIndex));
    resultPath.emplace_back(m.RowIndex(1), m.ColumnIndex(1 - columnIndex));

    CandidateSolution(resultPath);
    return;
  }
  //1. ���������� �������� ������� � ������� ������ �������
   auto matrix(m);
  if (bottomLimit == 0) {
    bottomLimit += ReduceMatrix(matrix);
  }
  else if (hasAdje) {
    bottomLimit += ReduceMatrix(matrix);
  }
  else {
    //����� �� �� ��������� bottom_limit, ��� ��� �� ������� ������� 
    //bottomLimit � ���������� ��������
    //��� ��� ��� �� ��������� ����� bottomLimit += maxZeroCoeff(����. ����� �� �� ����� ��������)
    ReduceMatrix(matrix);
  }


  //2. ���������� ������� ������ ������� � record. ����� ����� ����� �������� ������ �����
  if (bottomLimit > curRecord) {
    return;
  }

  //������ ������ � ������� �������� � ������������ �������
  int maxZeroCoefRow = -1;
  int maxZeroCoefColumn = -1;
  
  //3. ���� ����� � �������� ������������ ����� �� ��� ���������������
  GetBestZero(matrix, maxZeroCoefRow, maxZeroCoefColumn);
  

  ///////////////////// ��������� �����, ������� �������� ��� ����� ////////////////////
  
  //0. ��������� ��� ����� � ���� 
  std::list<pair<int, int> > newPath(currentPath);
  newPath.emplace_back(matrix.RowIndex(maxZeroCoefRow), matrix.ColumnIndex(maxZeroCoefColumn));
  //1. ������� �������, ���������� �� ��������� �����, ���������� �����
  auto hasEdgeMatrix(matrix);

  //hasEdgeMatrix[maxZeroCoefColumn][maxZeroCoefRow] = infinity;
  
  //2. ������� ������ � ������� �������, ��������������� ����� �����
  hasEdgeMatrix.RemoveRowColumn(maxZeroCoefRow, maxZeroCoefColumn);

  //3. ��������� ������������� ���������������� �����, ����� �������� �����
  AddInfinity(hasEdgeMatrix);

  
  //4.��������� ��������� ��� ����� �����, ���������� �����
  HandleMatrix(hasEdgeMatrix, newPath, bottomLimit, true);

  ///////////////////// ��������� �����, ������� �� �������� ��� ����� ////////////////////

  //1. ������� �������
  auto noEdgeMatrix(matrix);

  //2. ������� ����� �� ��������������� �����
  int fine = CalculateCoeff(noEdgeMatrix, maxZeroCoefRow, maxZeroCoefColumn);

  if (fine == infinity)
    return;
  //3. ������ ������������� ��� ���� �����, ������� �� �� ����� �����
  noEdgeMatrix[maxZeroCoefRow][maxZeroCoefColumn] = infinity + 1;

  //4. �������� ��������� ��� �����, ������� �� �������� ����� 
  HandleMatrix(noEdgeMatrix, currentPath, bottomLimit + fine, false);
}

int LittleAlg::ReduceMatrix(AdjacencyMatrixG<int>& curMatrix) {
  //���������� �����
  int rowMinSum = 0;
  int columnMinSum = 0;

  for (size_t row = 0; row < curMatrix.GetCountRows(); row++)
  {
    int minRowElem = curMatrix[row][0];
    for (size_t column = 0; column < curMatrix.GetCountColumns(); column++)
    {
      if (minRowElem > curMatrix[row][column]) {
        minRowElem = curMatrix[row][column];
      }
    }

    for (size_t column = 0; column < curMatrix.GetCountColumns(); column++)
    {
      if (curMatrix[row][column] < infinity) {
        curMatrix[row][column] -= minRowElem;
      }
    }
    rowMinSum += minRowElem;
  }

  //���������� ��������
  for (size_t column = 0; column < curMatrix.GetCountColumns(); column++)
  {
    int minColumnElem = curMatrix[0][column];
    for (size_t row = 0; row < curMatrix.GetCountRows(); row++)
    {
      if (minColumnElem > curMatrix[row][column]) {
        minColumnElem = curMatrix[row][column];
      }
    }

    for (size_t row = 0; row < curMatrix.GetCountRows(); row++)
    {
      if (curMatrix[row][column] < infinity) {
        curMatrix[row][column] -= minColumnElem;
      }
    }
    columnMinSum += minColumnElem;
  }
  return rowMinSum + columnMinSum;
}

int LittleAlg::CalculateCoeff(AdjacencyMatrixG<int>& curMatrix, int row, int column)
{
  int minRowElem = INT_MAX;
  int minColumnElem = INT_MAX;
  //������� ����������� � ������������ ������� �� ������ � ������� �� ����������� [row][column]
  for (size_t i = 0; i < curMatrix.GetCountColumns(); i++)
  {
    if (i != row)
      minColumnElem = std::min(minColumnElem, curMatrix[i][column]);
    if (i != column)
      minRowElem = std::min(minRowElem, curMatrix[row][i]);
  }
  return minColumnElem + minRowElem;
}

void LittleAlg::GetBestZero(AdjacencyMatrixG<int>& matrix, int& row, int& column)
{
  int maxZeroCoeff = -1;
  int bestRow = 0;
  int bestColumn = 0;
  for (size_t rows = 0; rows < matrix.GetCountRows(); rows++)
  {
    for (size_t columns = 0; columns < matrix.GetCountColumns(); columns++)
    {
      //����� ������� ������� � ������� ��� ���� �����������
      if (matrix[rows][columns] == 0) {
        int coeff = CalculateCoeff(matrix, rows, columns);
        //std::cout << "row, column: " << rows << columns << "Coef = " << coeff<<  std::endl;
        if (maxZeroCoeff < coeff) {
          maxZeroCoeff = coeff;
          bestRow = rows;
          bestColumn = columns;
        }
      }
    }
  }
  row = bestRow;
  column = bestColumn;
}

int LittleAlg::CalculatePrice(const std::list<pair<int, int>>& path)
{
  int result = 0;
  for (const auto& step : path) {
    result += matrix[step.first][step.second];
  }
  return result;
}

void LittleAlg::CandidateSolution(const std::list<pair<int, int> >& curSolution) {
  int curPrice = CalculatePrice(curSolution);
  if (curPrice < curRecord) {
    curRecord = curPrice;
    bestTreePath = curSolution;
  }
}

void LittleAlg::ConvertResult() {
  bestOrder.push_back(0);
  solution = curRecord;

  while (!bestTreePath.empty()) {
    auto iter = bestTreePath.begin();
    while (iter != bestTreePath.end()) {
      if (iter->first == bestOrder.back()) {
        bestOrder.push_back(iter->second);
        iter = bestTreePath.erase(iter);
      }
      else {
        ++iter;
      }
    }
  }

  /*
  while (bestOrder.size() != matrix.GetCountVertices() + 1) {
    for (const auto& edge : bestTreePath) {
      if (edge.first == bestOrder.back())
      {
        bestOrder.push_back(edge.second);
      }
    }
  }
  */
}

void LittleAlg::AddInfinity(AdjacencyMatrixG<int>& m)
{
  // ������� � ����������� � ���, � ����� �������� � ������� ���������� �������������
  std::vector<bool> infRow(m.GetCountRows(), false), infColumn(m.GetCountRows(), false);
  // ����� ���� �������
  for (size_t i = 0; i < m.GetCountRows(); i++)
    for (size_t j = 0; j < m.GetCountRows(); j++)
      if (m[i][j] == infinity) {
        infRow[i] = true;
        infColumn[j] = true;
      }
  // ����� ������, �� ���������� �������������
  size_t notInf;
  for (size_t i = 0; i < infRow.size(); i++)
    if (!infRow[i]) {
      notInf = i;
      break;
    }

  // ����� �������, �� ����������� ������������� � ���������� �������������
  for (size_t j = 0; j < infColumn.size(); j++)
    if (!infColumn[j]) {
      m[notInf][j] = infinity;
      break;
    }
}
