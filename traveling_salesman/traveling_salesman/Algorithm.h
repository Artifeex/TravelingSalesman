#pragma once
#include <string>
#include <vector>
class Algorithm
{
protected:
  std::string algName;
public:
  virtual void Run() = 0;
  virtual std::vector<int> GetMinRoute() = 0;
  virtual int GetMinWeight() = 0;
  std::string GetAlgName() { return algName; };
};

