#include "GeneratorRandomFunc.h"

int(*GeneratorRandomFunc::GetRandomFunc())(int i, int j)
{
  if (isSymmetric)
  {

  }
  else
  {

  }
}

void GeneratorRandomFunc::ChangeSymmetric(bool _isSymmetric)
{
  isSymmetric = _isSymmetric;
}

void GeneratorRandomFunc::ChangeFullyConnected(bool _isFullyConnected)
{
  isFullyConnected = _isFullyConnected;
}

void GeneratorRandomFunc::ChangeMaxMinRange(int minR, int maxR)
{
  range.first = minR;
  range.second = maxR;
}

void GeneratorRandomFunc::ChangeEdjeMissingProbability(double newProb)
{
  edjeMissingProbability = newProb;
}
