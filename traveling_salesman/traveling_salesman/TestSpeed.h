#pragma once
#include "AntColonyAlg.h"
#include "BruteForceAlg.h"
#include "NearestNeighboor.h"
#include <stdio.h> 
#include <time.h> 
#include "Timer.h"
namespace ts
{
  class TestSpeed
  {
  public:
	static double TestAlg(Algorithm* alg, int& weight, std::vector<int>& route);
	static double TestAlg(Algorithm* alg);
  };
}


