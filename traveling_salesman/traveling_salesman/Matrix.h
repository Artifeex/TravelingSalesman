#pragma once
#include <vector>
#include <string>
#include <iostream>

template<class T>
class Matrix
{
private:
  std::vector<std::vector<T>> matrix;
  int rows;
  int columns; 
public:
  // Конструкторы
  // Базовый конструктор
  Matrix(int countRows, int countColumns);
  // Конструктор преобразования типа
  Matrix(const std::vector<std::vector<T>>& m); 

  //Методы
  int GetCountRows() const { return rows; }
  int GetCountColumns() const { return columns; }
  void AddRow(std::vector<T>& values);
  void AddColumn(std::vector<T>& values);
  // Операторы
  std::vector<T>& operator[](int index) { return matrix[index]; } 
  std::vector<T> operator[](int index) const { return matrix[index]; }

  friend std::ifstream& operator>>(std::ifstream& in, Matrix<T>& m)
  {
	std::string line;
	for (size_t i = 0; i < m.GetCountRows(); i++)
	{
	  std::getline(in, line);
	  for (size_t j = 0; j < m.GetCountColumns(); j++)
	  {
		line >> m[i][j];
	  }
	}
  }

  friend std::ostream& operator<<(std::ostream& out, const Matrix<T>& m)
  {
	for (size_t i = 0; i < m.GetCountRows(); i++)
	{
	  for (size_t j = 0; j < m.GetCountColumns(); j++)
	  {
		out << m[i][j] << " ";
	  }
	  out << std::endl;
	}
	return out;
  }

  friend std::ostream& operator<<(std::ostream& out, const std::vector<T>& v)
  {
	for (size_t i = 0; i < v.size(); i++)
	{
	 out << v[i];
	}
	return out;
  }
};

template<class T>
inline Matrix<T>::Matrix(int countRows, int countColumns): rows(countRows),columns(countColumns)
{
  if (countRows <= 0 || countColumns <= 0)
	throw std::string("BadValues!");
  matrix.resize(rows);
  for (size_t i = 0; i < countRows; i++)
  {
	matrix[i].resize(columns);
  }
  
}

template<class T>
inline Matrix<T>::Matrix(const std::vector<std::vector<T>>& m)
{
  rows = m.size();
  columns = m[0].size();
  matrix = m;
}

template<class T>
inline void Matrix<T>::AddRow(std::vector<T>& values)
{
  if (values.size() == columns)
  {
	rows++;
	matrix.push_back(values);
  }
  else
	throw std::string("Count columns != columns matrix");
}

template<class T>
inline void Matrix<T>::AddColumn(std::vector<T>& values)
{
  if (values.size() == rows)
  {
	columns++;
	for (size_t i = 0; i < rows; i++)
	{
	  matrix[i].push_back(values[i]);
	}
  }
  else
	throw std::string("Count rows != rows matrix");
}

