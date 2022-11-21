#include "AntColonyCell.h"

void AntColonyCell::ChangeCloseness(double nCloseness)
{
  if (nCloseness < 0)
	throw std::string("������ �������� ��������");
  closeness = nCloseness;
}

void AntColonyCell::ChangePheromone(double nPheromone)
{
  if (nPheromone < 0)
	throw std::string("������ �������� ��������");
  amountPheromone = nPheromone;
}

void AntColonyCell::ChangeProbabilityTransition(double probability)
{
  probabilityTransition = probability;
}

double AntColonyCell::GetCloseness()
{
  return closeness;
}

double AntColonyCell::GetPheromone()
{
  return amountPheromone;
}

double AntColonyCell::GetProbability()
{
  return probabilityTransition;
}

int AntColonyCell::GetWeight()
{
  return weight;
}


