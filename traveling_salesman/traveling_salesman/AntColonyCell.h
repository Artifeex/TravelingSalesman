#pragma once
#include <string>

class AntColonyCell
{
private:
  double closeness;
  double amountPheromone;
public:
  AntColonyCell(double _closeness, double _amountPheromone)
  {
	if (_closeness < 0 || _amountPheromone < 0)
	{
	  throw std::string("Ошибка ввода числа феромонов или близости!");
	}
	closeness = _closeness;
	amountPheromone = _amountPheromone;
  }

  void ChangeCloseness(double nCloseness);
  void ChangePheromone(double nPheromone);
  
  double GetCloseness();
  double GetPheromone();
};

