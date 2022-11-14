#pragma once
#include "Algorithm.h"
#include "AdjacencyMatrixG.h"
#include "AntColonyCell.h"

class AntColonyAlg : public Algorithm
{
private:
  double alfa; // Влияние количества феромонов на выбор муравья
  double beta; //Влияние близости вершины на выбор муравья
  AdjacencyMatrixG<AntColonyCell> matrix;
public:
  void Run() override;
  AntColonyAlg(AdjacencyMatrixG<int> matrix);
};

