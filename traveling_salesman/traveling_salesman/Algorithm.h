#pragma once
#include <string>
#include <vector>
#include "AdjacencyMatrixG.h"
class Algorithm
{
protected:
  std::string algName;
public:
  virtual void Run() = 0;
  virtual std::vector<int> GetMinRoute() = 0;
  virtual int GetMinWeight() = 0;
  virtual void SetMatrix(const AdjacencyMatrixG<int>& m) = 0;

  std::string GetAlgName() { return algName; };
};
