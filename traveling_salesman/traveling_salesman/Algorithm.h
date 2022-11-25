#pragma once
#include <string>

class Algorithm
{
protected:
  std::string algName;
public:
  virtual void Run() = 0;
  std::string GetAlgName() { return algName; };
};

