#pragma once
#include "Graph.h"
#include "Matrix.h"
#include <fstream>

template<class T>
class AdjacencyMatrixG final: public Graph<T>
{
private:
  Matrix<T> m;
  int countVertices;
public:
  AdjacencyMatrixG(int countVertices);

  AdjacencyMatrixG()
  {
	countVertices = 0;
  }

  void GenerateByRandom(T(*RandomFunc)()) override
  {
	for (size_t i = 0; i < countVertices; i++)
	{
	  for (size_t j = 0; j < countVertices; j++)
	  {
		m[i][j] = RandomFunc();
	  }
	}
  }

  void MakeByFile(const std::string& filePath) override
  {
	std::ifstream file(filePath);
	if (file.is_open())
	{
	  try
	  {
		file >> m;
	  }
	  catch (const std::exception&)
	  {
		std::cout << std::string("something bad happened");
		file.close();
		return;
	  }
	  countVertices = m.GetCountRows();
	}
	else
	  throw std::string("Не удалось открыть файл!");
  }

  void AddVertex(T& infinityValue);
  void AddVertex(const std::vector<T>& AdjacencyValues);
  void AddEdje(int indexFirst, int indexSecond, const T& weight);
};

template<class T>
inline AdjacencyMatrixG<T>::AdjacencyMatrixG(int countVertices)
{
  if (countVertices <= 0)
	throw std::string("Bad value of count vertices!");
  m(countVertices, countVertices);
}

template<class T>
inline void AdjacencyMatrixG<T>::AddVertex(T& infinityValue)
{
  countVertices++;
  std::vector<T> values;
  for (size_t i = 0; i < countVertices; i++)
  {
	values.push_back(infinityValue);
  }
  m.AddRow(values);
}

template<class T>
inline void AdjacencyMatrixG<T>::AddVertex(const std::vector<T>& adjacencyValues)
{
  countVertices++;
  if (adjacencyValues.size() == countVertices)
  {
	m.AddRow(adjacencyValues);
	m.AddColumn(adjacencyValues);
  }
}

template<class T>
inline void AdjacencyMatrixG<T>::AddEdje(int indexFirst, int indexSecond, const T& weight)
{
  m[indexFirst][indexSecond] = weight;
}
