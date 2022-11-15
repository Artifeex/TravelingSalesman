#pragma once
#include <string>

class AntColonyCell
{
private:
  double closeness;
  double amountPheromone;
  bool isVisited;
  double probabilityTransition;

public:
  AntColonyCell(double _closeness, double _amountPheromone)
  {
	if (_closeness < 0 || _amountPheromone < 0)
	{
	  throw std::string("Ошибка ввода числа феромонов или близости!");
	}
	closeness = _closeness;
	amountPheromone = _amountPheromone;
	isVisited = false;
	probabilityTransition = 0.0;
  }

  void ChangeCloseness(double nCloseness);
  void ChangePheromone(double nPheromone);
  void ChangeProbabilityTransition(double probability);
  
  double GetCloseness();
  double GetPheromone();

  void Visit();
};

