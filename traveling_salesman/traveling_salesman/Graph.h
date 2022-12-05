#pragma once
#include <vector>
#include <string>

template<class T>
class Graph
{
public:
  virtual void GenerateByRandom(T(*RandomFunc)(int i, int j)) = 0;
  virtual void MakeByFile(const std::string& filePath) = 0;
};

