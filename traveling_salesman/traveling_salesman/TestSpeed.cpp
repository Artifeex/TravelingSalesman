#include "TestSpeed.h"

namespace ts
{
  double TestSpeed::TestAlg(Algorithm* alg)
  {
	Timer t;
	alg->Run();
	return t.elapsed();
  }

  void TestSpeed::CompareAlgs(Algorithm* alg1, Algorithm* alg2)
  {
	std::vector<int> result;
	double alg1Seconds = TestAlg(alg1);
	std::cout << "The time(seconds) of " << alg1->GetAlgName() << " :" << alg1Seconds << std::endl;
	std::cout << "Min route: " << alg1->GetMinWeight() << std::endl;
	std::cout << "Path: " << std::endl;
	result = alg1->GetMinRoute();
	for (size_t i = 0; i < result.size(); i++)
	{
	  std::cout << result[i] << " ";
	}
	std::cout << std::endl << std::endl;

	double alg2Seconds = TestAlg(alg2);
	std::cout << "The time(seconds) of " << alg2->GetAlgName() << " :" << alg2Seconds << std::endl;
	std::cout << "Min route: " << alg2->GetMinWeight() << std::endl;
	std::cout << "Path: " << std::endl;
	result = alg2->GetMinRoute();
	for (size_t i = 0; i < result.size(); i++)
	{
	  std::cout << result[i] << " ";
	}
	std::cout << std::endl << std::endl;
  }
}
