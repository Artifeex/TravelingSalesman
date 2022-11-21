#pragma once
#include "Algorithm.h"
#include "AdjacencyMatrixG.h"
#include "AntColonyCell.h"
#include <cmath>
#include <float.h>

class AntColonyAlg : public Algorithm
{
  
private:
  double alfa; // ¬ли€ние количества феромонов на выбор муравь€
  double beta; //¬ли€ние близости вершины на выбор муравь€
  double pheromoneResidue; // сколько феромона остаетс€ после конца итерации
  int countAnts;
  std::vector<int> vertVisitStat; // дл€ определени€ доступных вершин дл€ выбора муравь€
  std::vector<std::vector<int>> road;// дл€ отслеживани€ путей, по который ходили муравьи дл€ обн-€ фер-на
  AdjacencyMatrixG<AntColonyCell> matrix;

  int minRoad;
  double Q; // дл€ близости
  double pheromoneConst; // —колько феромона выделил муравей суммарно на всем пути
  const double infinity = DBL_MAX;
  //ћетоды
  std::vector<int> GetCurFreeVert();
  // –абота с веро€тностью
  double CalculateProbabilityTransition(int i, int j, double probabilitySum); 
  double CalculateSumProbabilityTransition(int start); 
  double CalculateDesireTransition(int i, int j); // тау умножить на q 
  void UpdateProbabilityTransition(int start);

  int SelectVert(int start);
  //–аботы с феромоном
  void UpdatePheromones();
  
public:
  void Run() override;
  AntColonyAlg(const AdjacencyMatrixG<int>& matrix, double _alfa=1.0, double _beta = 1.0,
	double _startPheromone = 0.2, double _Q = 200, int _countAnts = 5, 
	double _pheromoneResidue = 0.6, double _pheromoneConst = 4);
  int GetMinRoad();
};

