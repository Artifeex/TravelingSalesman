#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <list>
template<class T>
class Matrix
{
private:
  std::vector<std::vector<T>> matrix;
  int rows;
  int columns;
  //Нужны для алгоритма Литтла
  std::list<int> realRowsIndices;
  std::list<int> realColumnsIndices;
public:
  // Конструкторы
  // Базовый конструктор
  Matrix(int countRows, int countColumns);
  // Конструктор преобразования типа
  Matrix(const std::vector<std::vector<T>>& m); 
  Matrix() = default;
  //Методы
  int GetCountRows() const { return rows; }
  int GetCountColumns() const { return columns; }
  void AddRow(std::vector<T>& values);
  void AddColumn(std::vector<T>& values);
  // Операторы
  std::vector<T>& operator[](int index) { return matrix[index]; } 
  std::vector<T> operator[](int index) const { return matrix[index]; }
  Matrix& operator=(const Matrix& m);

  //Нужны для алгоритма Литтла
  void RemoveRowColumn(int row, int column);
  int RowIndex(int index) const;
  int ColumnIndex(int index) const;
  /*friend std::ifstream& operator>>(std::ifstream& in, Matrix<T>& m)
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
	return 
  }*/

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
	realRowsIndices.push_back(i);
  }
  for (size_t i = 0; i < countColumns; i++)
  {
	realColumnsIndices.push_back(i);
  }
}

template<class T>
inline Matrix<T>::Matrix(const std::vector<std::vector<T>>& m)
{
  rows = m.size();
  columns = m[0].size();
  matrix = m;
  for (size_t i = 0; i < rows; i++)
  {
	realRowsIndices.push_back(i);
  }

  for (size_t i = 0; i < columns; i++)
  {
	realColumnsIndices.push_back(i);
  }
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

template<class T>
inline Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m)
{
  if (this == &m)
	return *this;
  else
  {
	matrix = m.matrix;
	rows = m.rows;
	columns = m.columns;
	realRowsIndices = m.realRowsIndices;
	realColumnsIndices = m.realColumnsIndices;
	return *this;
  }

}

template<class T>
inline void Matrix<T>::RemoveRowColumn(int row, int column)
{
  //Удаление индексов, соответсвующей этой строке и столбцу
  auto itRow = realRowsIndices.begin();
  auto itColumn = realColumnsIndices.begin();
  for (int i = 0; i < column; i++) {
	++itColumn;
  }
  for (int i = 0; i < row; i++) {
	++itRow;
  }
	
  realRowsIndices.erase(itRow);
  realColumnsIndices.erase(itColumn);
  matrix.erase(matrix.begin() + row);

  for (size_t i = 0; i < matrix.size(); i++) {
	matrix[i].erase(matrix[i].begin() + column);
  }
  this->rows--;
  this->columns--;
}

template<class T>
inline int Matrix<T>::RowIndex(int index) const
{
  auto it = realRowsIndices.begin();
  for (int i = 0; i < index; i++) {
	++it;
  }
  return *it;
}

template<class T>
inline int Matrix<T>::ColumnIndex(int index) const
{
  auto it = realColumnsIndices.begin();
  for (int i = 0; i < index; i++) {
	++it;
  }
  return *it;
}

