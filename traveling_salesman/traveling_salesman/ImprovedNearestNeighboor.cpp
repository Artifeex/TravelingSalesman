#include "ImprovedNearestNeighboor.h"

int ImprovedNearestNeighboor::FindMinDistanceVert(int vert, const std::vector<bool>& tmpVisitedVert)
{
  int minRoute = INT_MAX;
  int minVert = -1;
  std::vector<int> availableVert;
  for (size_t i = 0; i < tmpVisitedVert.size(); i++)
  {
    if (tmpVisitedVert[i] == false)
      availableVert.push_back(i);
  }
  for (size_t i = 0; i < availableVert.size(); i++)
  {
    if (minRoute > matrix[vert][availableVert[i]])
    {
      minRoute = matrix[vert][availableVert[i]];
      minVert = availableVert[i];
    }
  }
  return minVert;
}

void ImprovedNearestNeighboor::SetMatrix(const AdjacencyMatrixG<int>& matr)
{
  matrix = matr;
  visitedOrder.clear();
  visitedVert.clear();
  visitedVert.resize(matr.GetCountVertices(), false);
  visitedOrder.resize(matr.GetCountVertices());
  bestResult = INT_MAX;
}

void ImprovedNearestNeighboor::SetMatrix(const Matrix<int>& m)
{
  matrix = m;
  visitedVert.resize(matrix.GetCountVertices());
  visitedOrder.resize(matrix.GetCountVertices(), false);
}

void ImprovedNearestNeighboor::Run()
{
  for (size_t i = 0; i < matrix.GetCountVertices(); i++)
  {
    //Обнуляем значение стоимости всего маршрута
    int minPath = 0;
    //Выбираем в качестве стартовой очередную вершину
    int startVert = i;
    //Задаем текущую вершину
    int currentVert = startVert;
    //Задаем число вершин
    int countVert = matrix.GetCountVertices();
    //Массив, хранящий весь путь для данной стартовой вершины
    std::vector<int> tmpVisitedOrder(countVert);
    //Массив, хранящий информацию о посещенных вершинах
    std::vector<bool> tmpVisitedVert(countVert, false);
    //Добавляем стартовую вершину в путь
    tmpVisitedOrder[0] = startVert;
    //Отмечаем стартовую вершину как посещенную 
    tmpVisitedVert[i] = true;
    for (size_t i = 1; i < countVert; i++)
    {
      //Выбираем ближайшую вершину для перехода
      int nextVert = FindMinDistanceVert(currentVert, tmpVisitedVert);
      //Отмеча ближайшую вершину как посещенную
      tmpVisitedVert[nextVert] = true;
      //Добавляем вершину в путь
      tmpVisitedOrder[i] = nextVert;
      //Добавляем стоимость перехода в общую стоимость маршрута
      minPath += matrix[currentVert][nextVert];
      currentVert = nextVert;
    }
    //Возвращаемся в стартовую вершину
    minPath += matrix[currentVert][startVert];
    tmpVisitedOrder.push_back(startVert);
    //Сравниваем стоимость маршрута, полученного для данной стартовой вершины
    if (bestResult > minPath) {
      //Запоминаем лучший результат и маршрут
      bestResult = minPath;
      visitedOrder = tmpVisitedOrder;
    }
  }
}
