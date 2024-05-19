#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>

namespace parser {
  class TSPParser
  {
    public: 
      static std::vector<std::vector<int>> tspToDistanceMatrix(const std::string& tspFile);
  };
}


