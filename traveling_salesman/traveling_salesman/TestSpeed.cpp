#include "TestSpeed.h"

namespace ts
{
  double TestSpeed::TestAlg(Algorithm* alg, int& weight, std::vector<int>& route)
  {
	Timer t;
	alg->Run();
	weight = alg->GetMinWeight();
	route = alg->GetMinRoute();
	return t.elapsed();
  }
}
