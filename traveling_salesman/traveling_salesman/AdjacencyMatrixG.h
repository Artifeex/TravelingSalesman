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
  AdjacencyMatrixG(const Matrix<T>& matrix);
  AdjacencyMatrixG()
  {
	countVertices = 0;
  }

  int GetCountRows() const
  { 
	return m.GetCountRows(); 
  }
  int GetCountColumns() const
  { 
	return m.GetCountColumns(); 
  }

  void GenerateByRandom(T(*RandomFunc)(int i, int j)) override
  {
	if (countVertices <= 0)
	  throw std::string("count vertices <= 0");

	for (size_t i = 0; i < countVertices; i++)
	{
	  for (size_t j = 0; j < countVertices; j++)
	  {
		m[i][j] = RandomFunc(i, j);
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
		//file >> m;
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

  int GetCountVertices() const;
  Matrix<T> GetMatrix();
  std::vector<T>& operator[](int index) { return m[index]; }
  std::vector<T> operator[](int index) const { return m[index]; }

  friend std::ostream& operator<<(std::ostream& out, const AdjacencyMatrixG<T>& matr)
  {
	out << matr.m;
	return out;
  }


  //Нужны для алгоритма Литтла
  void RemoveRowColumn(int row, int column) { m.RemoveRowColumn(row, column); };
  int RowIndex(int index) const
  { 
	return m.RowIndex(index);
  }
  int ColumnIndex(int index) const
  { 
	return m.ColumnIndex(index);
  }
};

template<class T>
inline AdjacencyMatrixG<T>::AdjacencyMatrixG(int _countVertices): m(_countVertices, _countVertices)
{
  countVertices = _countVertices;
  
  if (countVertices <= 0)
	throw std::string("Bad value of count vertices!");
}

template<class T>
inline AdjacencyMatrixG<T>::AdjacencyMatrixG(const Matrix<T>& matrix)
{
  m = matrix;
  countVertices = m.GetCountRows();
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

template<class T>
inline int AdjacencyMatrixG<T>::GetCountVertices() const
{
  return countVertices;
}

