#pragma once
#include <string>

class AntColonyCell
{
private:
  double closeness;
  double amountPheromone;
  double probabilityTransition;
  int weight;
public:
  AntColonyCell(double _closeness, double _amountPheromone, int _weight)
  {
    if (_closeness < 0 || _amountPheromone < 0)
    {
      throw std::string("Ошибка ввода числа феромонов или близости!");
    }

    closeness = _closeness;
    amountPheromone = _amountPheromone;
    probabilityTransition = 0.0;
    weight = _weight;
  }
  AntColonyCell() = default;

  void ChangeCloseness(double nCloseness);
  void ChangePheromone(double nPheromone);
  void ChangeProbabilityTransition(double probability);

  double GetCloseness();
  double GetPheromone();
  double GetProbability();
  int GetWeight();
};

