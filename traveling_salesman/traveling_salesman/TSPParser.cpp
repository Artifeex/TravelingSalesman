#include "TSPParser.h"
namespace parser {
  struct City {
    double x, y;
  };

  int euclideanDistance(const City& city1, const City& city2) {
    return (int) std::sqrt(std::pow(city1.x - city2.x, 2) + std::pow(city1.y - city2.y, 2));
  }

  std::vector<std::vector<int>> TSPParser::tspToDistanceMatrix(const std::string& tspFile)
  {
    std::ifstream file(tspFile);
    if (!file.is_open()) {
      std::cerr << "Ошибка открытия файла: " << tspFile << std::endl;
      return {};
    }

    std::vector<City> cities;
    std::string line;
    bool readingCoordinates = false;
    while (std::getline(file, line)) {
      if (readingCoordinates) {
        if (line == "EOF")
          break;
        std::istringstream iss(line);
        int index;
        double x, y;
        iss >> index >> x >> y;
        cities.push_back({ x, y });
      }
      else if (line == "NODE_COORD_SECTION") {
        readingCoordinates = true;
      }
    }

    int numCities = cities.size();
    std::vector<std::vector<int>> distanceMatrix(numCities, std::vector<int>(numCities, 0));

    for (int i = 0; i < numCities; ++i) {
      for (int j = 0; j < numCities; ++j) {
        if (i != j) {
          distanceMatrix[i][j] = euclideanDistance(cities[i], cities[j]);
        }
      }
    }

    return distanceMatrix;
  }
}

