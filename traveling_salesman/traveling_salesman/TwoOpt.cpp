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
  //перезаписать вершины
  auto first = tmpPath.begin();
  std::reverse(first + i, first + j);
}

void TwoOpt::TwoOptUndoSwap(std::vector<int>& tmpPath, int i, int j)
{
  //перезаписать вершины
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
  //для начальной работы нам нужен какой-нибудь машрут, который мы будем улучшать
  //в качестве алгоритма, который будет нам выдавать начальный маршрут используем 
  //алгоритм ближайшего соседа
  auto alg = NearestNeighboor();
  //устанавливаем для алгоритма ближайшего соседа матрицу смежности и запускаем его
  alg.SetMatrix(matrix);
  alg.Run();
  //получаем результаты работы алгоритма ближайшего соседа и сам маршрут
  auto firstPath = alg.GetMinRoute();
  auto curLength = alg.GetMinWeight();
  //размер получившегося машрута
  int n = firstPath.size();
  //флаг, отвечающий за то, получилось ли что-либо улучшить на текущей итерации
  bool isOptimal = false;
  //основной цикл алгоритма 2-opt. Выполняем до тех пор, пока внутри итерации удалось
  //найти улучшение
  while (!isOptimal) {
    isOptimal = true;
    //цикл по всем возможным вершинам
    for (int i = 1; i < n - 1; i++) {
      for (int j = i + 1; j < n - 1; j++) {
        //меняем местами две вершины в маршруте между собой
        TwoOptSwap(firstPath, i, j + 1);
        //считаем новую стоимость для полученной перестановки
        int newCost = calculateCost(firstPath);
        //обновляем и запоминаем лучший результат в случае, если перестановка дала улучшение
        if (newCost < curLength) {
          isOptimal = false;
          curLength = newCost;
        }
        //если перестановка не дала улучшений возвращаем вершины обратно
        else {
          TwoOptUndoSwap(firstPath, i, j + 1);
        }

        //это работает только в случае симметрии матрицы смежности
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
  //запоминаем лучший результат
  minPathValue = curLength;
  path = firstPath;
}
