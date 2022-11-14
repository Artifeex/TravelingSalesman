#pragma once
#include "Graph.h"
#include "Matrix.h"
template<class T>
class AdjacencyMatrixG final: public Graph
{
private:
  Matrix<T> m;

public:
  AdjacencyMatrixG(int countVertices)

  void GenerateByRandom() override
  {

  }

  void MakeByFile() override
  {

  }

  void AddVertex();
  void AddEdje();
};

template<class T>
inline AdjacencyMatrixG<T>::AdjacencyMatrixG(int countVertices)
{
}
