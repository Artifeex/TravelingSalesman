#include "AntColonyCell.h"

void AntColonyCell::ChangeCloseness(double nCloseness)
{
  if (nCloseness < 0)
	throw std::string("Ошибка значения близости");
  closeness = nCloseness;
}

void AntColonyCell::ChangePheromone(double nPheromone)
{
  if (nPheromone < 0)
	throw std::string("Ошибка значения близости");
  amountPheromone = nPheromone;
}

double AntColonyCell::GetCloseness()
{
  return closeness;
}

double AntColonyCell::GetPheromone()
{
  return amountPheromone;
}
