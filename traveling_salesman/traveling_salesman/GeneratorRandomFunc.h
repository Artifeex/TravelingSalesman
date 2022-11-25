#pragma once
#include <utility>

class GeneratorRandomFunc
{
private:
  bool isSymmetric;
  bool isFullyConnected;
  std::pair<int, int> range;
  int infinity = INT_MAX;
  double edjeMissingProbability = 0.0;
public:
  GeneratorRandomFunc(bool _isSymmetric, bool _isFullyConnected, int minR, int maxR) :
	isSymmetric(_isSymmetric), isFullyConnected(_isFullyConnected), range(minR, maxR) 
  {}
  int (*GetRandomFunc())(int i, int j);

  void ChangeSymmetric(bool _isSymmetric);
  void ChangeFullyConnected(bool _isFullyConnected);
  void ChangeMaxMinRange(int minR, int maxR);
  void ChangeEdjeMissingProbability(double newProb);
};

