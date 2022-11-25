#include "TestSpeed.h"

namespace ts
{
  double TestSpeed::TestAlg(Algorithm* alg)
  {
	clock_t start = clock();
	alg->Run();
	clock_t end = clock();
	return (double)(end - start) / CLOCKS_PER_SEC;
  }

  void TestSpeed::CompareAlgs(Algorithm* alg1, Algorithm* alg2)
  {
	double alg1Seconds = TestAlg(alg1);
	double alg2Seconds = TestAlg(alg2);

	std::cout << "The time(seconds) of " << alg1->GetAlgName() << " :" << alg1Seconds << std::endl;
	std::cout << "The time(seconds) of " << alg2->GetAlgName() << " :" << alg2Seconds << std::endl;
  }
}
