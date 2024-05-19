#pragma once
#include "Algorithm.h"
#include "AdjacencyMatrixG.h"
#include "AntColonyCell.h"
#include <cmath>
#include <random>
#include <ctime>
#include <float.h>
//#include <valarray>
//O(t * m * n^2) t Ц число итераций, m Ц количество муравьЄв, n Ц количество вершин в графе

class AntColonyAlg : public Algorithm
{
private:
  double alfa; // ¬ли€ние количества феромонов на выбор муравь€
  double beta; //¬ли€ние близости вершины на выбор муравь€
  double pheromoneResidue; // сколько феромона остаетс€ после конца итерации
  int countAnts;
  double startPheromone;
  int countVertecies;
  std::vector<int> visitedVertecies; // дл€ определени€ доступных вершин дл€ выбора муравь€
  std::vector<std::vector<int>> antRoute;// дл€ отслеживани€ путей, по который ходили муравьи дл€ обн-€ фер-на
  AdjacencyMatrixG<AntColonyCell> matrix;
  int weightIndex; // указывает на положение веса всего маршрута муравь€
  int minWeightRoute = INT_MAX;

  std::mt19937 generator;
  std::uniform_real_distribution<double> distribution;

  std::vector<int> bestRoute;
  std::vector<int> iterationBestResults;

  double closConst; // дл€ близости
  double pheromoneConst; // —колько феромона выделил муравей суммарно на всем пути
  int countIterations;
  //ћетоды
  std::vector<int> GetCurFreeVert();
  // –абота с веро€тностью
  double ProbabilityTransition(int i, int j, double probabilitySum); 
  double SumProbabilityTransition(int start); 
  double DesireTransition(int i, int j); // тау умножить на q 
  void UpdateProbabilityTransition(int start);
  int SelectVert(int start);
  void UpdatePheromones();

  void ClearVisitedVert();

  void ClearAntRoute();

  void UpdateBestRouteWeight();

  void UpdateBestRoute();

  int CalculateMinWeight() noexcept;

  std::vector<int> CalculateMinRoute();

  void UpdateResults();
  void SetNameAlg(std::string _nameAlg);

public:
  void Run() override;

  void SetMatrix(const AdjacencyMatrixG<int>& adjacencyMatr) override;

  AntColonyAlg(double _alfa=1, double _beta = 2,
	double _startPheromone = 0.2, double _closConst = 1, int _countAnts = 12, 
	double _pheromoneResidue = 0.3, double _pheromoneConst = 1, int _countIterations = 1);
  int GetMinWeight() override;
  std::vector<int>  GetMinRoute() override;
  
  std::vector<int> historyResults();
  
};

