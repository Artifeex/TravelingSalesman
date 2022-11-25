#pragma once
#include "AntColonyAlg.h"
#include "BruteForceAlg.h"
#include <stdio.h> 
#include <time.h> 

namespace ts
{
  class TestSpeed
  {
  public:
	static double TestAlg(Algorithm* alg);
	static void CompareAlgs(Algorithm* alg1, Algorithm* alg2);
  };
}


