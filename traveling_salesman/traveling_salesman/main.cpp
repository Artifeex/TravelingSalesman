#include "Matrix.h"
#include <iostream>
#include "AntColonyAlg.h"
#include "BruteForceAlg.h"
#include "TestSpeed.h"
#include "NearestNeighboor.h"
#include "ImprovedNearestNeighboor.h"
#include "TwoOpt.h"
#include "LittleAlg.h"
#include <random>
#include <fstream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

const int COUNT_ALGS = 6;

//��������� ����������� ���������
double alfa = 1.0;
double beta = 2.0;
double startPheromone = 0.2;
double constClosness = 1.0;
int countAnts = 12;
double pheromoneResidue = 0.3;
double totalPheromone = 1.0;
int countIterations = 5;

//��������� ���������
int minBound = 10;
int maxBound = 100;
bool isSymmetric = false;
int dimension = 10;

enum class Algs
{
  bruteForce = 0,
  ant = 1,
  nearNeigh = 2,
  upNearNeigh = 3,
  bounds = 4,
  opt = 5
};

void ShowMenu() {
  cout << "1) ��������� ���������" << endl;
  cout << "2) ������������� �������" << endl;
  cout << "3) ������ ������� �� �����" << endl;
  cout << "4) ��������� �������" << endl;
  cout << "5) �������� ������� �������" << endl;
  cout << "6) ������� ���������" << endl;
  cout << "7) ���������" << endl;
  cout << "8) �����������" << endl;
  cout << "0) �����" << endl;
}

void GenerationPreference(bool& isSymetric, int& dem, int& minBound, int& maxBound) {

  int choice = 0;
  cout << "������������ ?(1 - ��, 2 - ���): ";
  cin >> choice;
  if (choice == 1) {
    isSymetric = true;
  }
  else {
    isSymetric = false;
  }
  cout << endl;
  cout << "����������� �������: ";
  cin >> dem;
  cout << endl;
  cout << "������ ������� ���������: ";
  cin >> minBound;
  cout << endl;
  cout << "������� ������� ���������: ";
  cin >> maxBound;
  cout << endl;
}

//������� ������� � �������������, ������� ���������� ������ ���������� ��� ����������� ���������
void GetParamsAntColonyAlg() {
  cout << "������� �������� ��������� alfa: ";
  cin >> alfa;
  cout << endl;
  cout << "������� �������� ��������� beta: ";
  cin >> beta;
  cout << endl;
  cout << "������� �������� ���������� �������� �������� �� ������ �����: ";
  cin >> startPheromone;
  cout << endl;
  cout << "������� ���������� ��������: ";
  cin >> countAnts;
  cout << endl;
  cout << "������� �������� ��������� �������� �������� ����� ����������: ";
  cin >> pheromoneResidue;
  cout << endl;
  cout << "������� �������� ��������, ������� �������� ���������� � ����� ��������: ";
  cin >> totalPheromone;
  cout << endl;
  cout << "������� ����� ��������: ";
  cin >> countIterations;
  cout << endl;
}

int GenerateNum(int minBound, int maxBound) {
  std::random_device random_device;
  std::mt19937 generator(random_device());
  std::uniform_int_distribution<> distribution(minBound, maxBound);
  return distribution(generator);
}

AdjacencyMatrixG<int>* GenerateMatrix(bool isSymetric, int dem, int minBound, int maxBound) {
  vector<vector<int>> matrix;
  matrix.resize(dem);
  for (size_t i = 0; i < dem; i++)
  {
    matrix[i].resize(dem);
  }
  for (size_t i = 0; i < dem; i++)
  {
    if (isSymetric) {
      for (size_t j = i; j < dem; j++)
      {
        if (i == j) {
          matrix[i][j] = INT_MAX - 1;
        }
        else {
          int generatedValue = GenerateNum(minBound, maxBound);
          matrix[i][j] = generatedValue;
          matrix[j][i] = generatedValue;
        }
      }
    }
    else {
      for (size_t j = 0; j < dem; j++)
      {
        if (i == j) {
          matrix[i][j] = INT_MAX - 1;
        }
        else {
          matrix[i][j] = GenerateNum(minBound, maxBound);
        }
      }
    }
  }
  return new AdjacencyMatrixG<int>(matrix);
}

AdjacencyMatrixG<int>* ReadMatrixFromFile(string filePath, int dimension) {
  std::ifstream file(filePath);
  vector<vector<int>> matrix;
  matrix.resize(dimension);
  for (size_t i = 0; i < dimension; i++)
  {
    matrix[i].resize(dimension);
    for (size_t j = 0; j < dimension; j++)
    {
      file >> matrix[i][j];
    }
  }
  file.close();
  return new AdjacencyMatrixG<int>(matrix);
}

void SaveMatrix(string filePath, const AdjacencyMatrixG<int>* matrPtr) {
  std::ofstream file(filePath);
  file << *matrPtr;
  file.close();
}

void ChoiceAlgs(vector<bool>& algs) {
  algs.resize(COUNT_ALGS);
  bool isExit = false;
  int choice;
  cout << "���������: " << endl;
  cout << "1) ������� �������" << endl;
  cout << "2) ���������� ��������" << endl;
  cout << "3) ���������� ������" << endl;
  cout << "4) ����������������� �������� ���������� ������" << endl;
  cout << "5) ����� ������ � ������" << endl;
  cout << "6) ����� 2-opt" << endl;
  while (!isExit) {
    cout << "�������� ��������(��� ������ ������� 0): " << endl;
    cin >> choice;
    switch (choice)
    {
    case 1:
      algs[static_cast<int>(Algs::bruteForce)] = true;
      break;
    case 2:
      GetParamsAntColonyAlg();
      algs[static_cast<int>(Algs::ant)] = true;
      break;
    case 3:
      algs[static_cast<int>(Algs::nearNeigh)] = true;
      break;
    case 4:
      algs[static_cast<int>(Algs::upNearNeigh)] = true;
      break;
    case 5:
      algs[static_cast<int>(Algs::bounds)] = true;
      break;
    case 6:
      algs[static_cast<int>(Algs::opt)] = true;
      break;
    case 0:
      isExit = true;
      break;
    default:
      cout << "������ ������ ���������" << endl;
      break;
    }
  }
}

void CreateAlgs(vector<Algorithm*>& algs, vector<bool> algsBoolean) {
  algs.clear();
  algs.resize(COUNT_ALGS);
  for (int algsIndex = 0; algsIndex < COUNT_ALGS; algsIndex++) {
    if (algsBoolean[algsIndex] == true) {
      switch (algsIndex)
      {
      case 0:
        algs[0] = new BruteForceAlg();
        break;
      case 1:
        algs[1] = new AntColonyAlg(alfa, beta,
          startPheromone, constClosness, countAnts, pheromoneResidue,
          totalPheromone, countIterations);
        break;
      case 2:
        algs[2] = new NearestNeighboor();
        break;
      case 3:
        algs[3] = new ImprovedNearestNeighboor();
        break;
      case 4:
        algs[4] = new LittleAlg(INT_MAX - 1);
        break;
      case 5:
        algs[5] = new TwoOpt();
        break;
      default:
        cout << "������ � �������� ����������!" << endl;
        break;
      }
    }
  }
}

double TestAlg(Algorithm* alg) {
  int weight = -1;
  vector<int> minRoute;
  double time = ts::TestSpeed::TestAlg(alg, weight, minRoute);
  cout << "��������: " << alg->GetAlgName() << endl;
  cout << "��������� ������������ ���������� ����: " << weight << endl;
  cout << "������� � ������������ ��������� �����: ";
  for (auto val : minRoute) {
    cout << val << " ";
  }
  cout << endl;
  cout << "����� ������: " << time << " c" << endl;
  return time;
}

void SaveResultsAfterExp(const vector<Algorithm*>& algs,
  const vector<vector<double>>& results, const vector<int>& dimensions, bool isByTime) {
  int sizeAlgName = 30;
  int sizeDim = 7;
  int sizeResults = 10;
  int choice = 0;
  
  std::cout << std::setw(sizeAlgName) << std::left << "Algorithm" << std::setw(sizeDim) <<
    "Dim" << std::setw(sizeResults); 
  if (isByTime) {
    std::cout << "Time" << std::endl;
  }
  else {
    cout << "Mean Value" << std::endl;
  }
  for (size_t i = 0; i < COUNT_ALGS; i++)
  {
    if (algs[i] != nullptr) {
      int k = 0;
      for (auto dim : dimensions) {
        std::cout << std::setw(sizeAlgName) << std::left << algs[i]->GetAlgName()
          << std::setw(sizeDim) <<
          dim << std::setw(sizeResults) << results[i][k] << std::endl;
        k++;
      }
    }
  }

  std::cout << std::endl;
  std::cout << "��������� ���������� � ����? (1-��, 2-���)" << std::endl;
  cin >> choice;
  if (choice == 1) {
    string filePath;
    std::cout << "������� �������� �����: " << std::endl;
    cin >> filePath;
    std::ofstream file(filePath);
    cout << endl;
    cout << "��������� ��� ������� Latex?(1 - ��, 2 - ���)" << std::endl;
    cin >> choice;
    if (choice == 1) {
      file << "Dim";
      for (size_t i = 0; i < COUNT_ALGS; i++)
      {
        if (algs[i] != nullptr) {
          file << " & " << algs[i]->GetAlgName();
        }
      }
      file << endl;
      for (size_t dim = 0; dim < dimensions.size(); dim++)
      {
        file << dimensions[dim];
        for (size_t i = 0; i < COUNT_ALGS; i++)
        {
          if (algs[i] != nullptr) {
            file << " & " << results[i][dim];
          }
        }
        file << " \\\\" << endl;
      }
    }
    else {
      file << std::setw(sizeAlgName) << std::left << "Algorithm" << std::setw(sizeDim) <<
        "Dim" << std::setw(sizeResults);
      if (isByTime) {
        cout << "Time" << std::endl;
      }
      else {
        cout << "Mean Value" << std::endl;
      }
      for (size_t i = 0; i < COUNT_ALGS; i++)
      {
        if (algs[i] != nullptr) {
          int k = 0;
          for (auto dim : dimensions) {
            file << std::setw(sizeAlgName) << std::left << algs[i]->GetAlgName()
              << std::setw(sizeDim) <<
              dim << std::setw(sizeResults) << results[i][k] << std::endl;
            k++;
          }
        }
      }
      file.close();
      std::cout << "���������� ���������!" << std::endl;
    }
  }
  else if (choice == 2) {
    return;
  }
  else {
    std::cout << "������!" << std::endl;
  }

}

void SaveResultsAfterTestAlgs(const vector<Algorithm*>& algs, const vector<double>& times) {
  int choice;
  string path;
  cout << "��������� ���������� � ����?(1 - ��, 2 - ���): ";
  cin >> choice;
  if (choice == 1) {
    cout << endl;
    cout << "������� ��� �����: ";
    cin >> path;
    cout << endl;
    std::ofstream file(path);
    for (size_t i = 0; i < COUNT_ALGS; i++)
    {
      if (algs[i] != nullptr) {
        file << "��������: " << algs[i]->GetAlgName() << endl;
        file << "��������� ������������ ���������� ����: " << algs[i]->GetMinWeight() << endl;
        file << "������� � ������������ ��������� �����: ";
        for (auto val : algs[i]->GetMinRoute()) {
          file << val << " ";
        }
        file << endl;
        file << "����� ������: " << times[i] << " c" << endl;
        file << endl;
      }
    }
  }
}


void ExperimentByResults(const vector<Algorithm*>& algs) {
  int nMin = 10;
  int nMax = 100;
  int step = 10;
  int countExperiments = 5;
  vector<vector<double>> results(COUNT_ALGS);
  vector<int> dimensions;
  cout << "������� ��������� �������� ����������� �������: ";
  cin >> nMin;
  cout << std::endl;
  cout << "������� �������� �������� ����������� �������: ";
  cin >> nMax;
  cout << std::endl;
  cout << "������� �������� ���� ���������� ����������� �������: ";
  cin >> step;
  cout << std::endl;
  cout << "������� ����� �������������: ";
  cin >> countExperiments;
  vector<double> expResults(COUNT_ALGS, 0.0);
  for (size_t curN = nMin; curN <= nMax; curN += step)
  {
    dimensions.push_back(curN);
    for (size_t i = 0; i < expResults.size(); i++)
    {
      expResults[i] = 0.0;
    }
    for (size_t experiment = 0; experiment < countExperiments; experiment++)
    {
      AdjacencyMatrixG<int>* matr = GenerateMatrix(isSymmetric, curN, minBound, maxBound);
      for (size_t algI = 0; algI < COUNT_ALGS; algI++)
      {
        if (algs[algI] != nullptr) {
          algs[algI]->SetMatrix(*matr);
          algs[algI]->Run();
          expResults[algI] += algs[algI]->GetMinWeight();
        }
      }
      delete matr;
    }
    for (size_t algI = 0; algI < COUNT_ALGS; algI++)
    {
      if (algs[algI] != nullptr) {
        results[algI].push_back(expResults[algI] / countExperiments);
      }
    }
  }
  SaveResultsAfterExp(algs, results, dimensions, false);
}

void ExperimentByTime(const vector<Algorithm*>& algs) {
  int nMin = 10;
  int nMax = 100;
  int step = 10;
  int countExperiments = 5;
  vector<vector<double>> times(COUNT_ALGS);
  vector<int> dimensions;
  cout << "������� ��������� �������� ����������� �������: ";
  cin >> nMin;
  cout << std::endl;
  cout << "������� �������� �������� ����������� �������: ";
  cin >> nMax;
  cout << std::endl;
  cout << "������� �������� ���� ���������� ����������� �������: ";
  cin >> step;
  cout << std::endl;
  cout << "������� ����� �������������: ";
  cin >> countExperiments;
  cout << std::endl;
  vector<double> expTimes(COUNT_ALGS, 0.0);
  for (size_t curN = nMin; curN <= nMax; curN += step)
  {
    dimensions.push_back(curN);
    for (size_t i = 0; i < expTimes.size(); i++)
    {
      expTimes[i] = 0.0;
    }
    for (size_t experiment = 0; experiment < countExperiments; experiment++)
    {
      AdjacencyMatrixG<int>* matr = GenerateMatrix(isSymmetric, curN, minBound, maxBound);
      for (size_t algI = 0; algI < COUNT_ALGS; algI++)
      {
        if (algs[algI] != nullptr) {
          algs[algI]->SetMatrix(*matr);
          expTimes[algI] += ts::TestSpeed::TestAlg(algs[algI]);
        }
      }
      delete matr;
    }
    for (size_t algI = 0; algI < COUNT_ALGS; algI++)
    {
      if (algs[algI] != nullptr) {
        times[algI].push_back(expTimes[algI]);
      }
    }
  }
  std::cout << endl;
  SaveResultsAfterExp(algs, times, dimensions, true);
}


int main(int argc, char* argv[])
{

  //���������
  vector<Algorithm*> algs(COUNT_ALGS, nullptr);
  vector<bool> algsBoolean(COUNT_ALGS, false);
  //��������� ����������
  bool isExit = false;
  int choice = -1;
  string filePath;
  //�������
  AdjacencyMatrixG<int>* matrixPtr = nullptr;


  setlocale(LC_ALL, "Russian");
  while (!isExit) {
    ShowMenu();
    cout << "��� �����: ";
    cin >> choice;
    switch (choice)
    {
    case 1: // ����� �������, ���������� �� ������ � ����������
      GenerationPreference(isSymmetric, dimension, minBound, maxBound);
      break;
    case 2: // ��������� ������� � ����� �� �� �����
      matrixPtr = GenerateMatrix(isSymmetric, dimension, minBound, maxBound);
      cout << "��������������� �������: " << endl;
      cout << *matrixPtr;
      cout << endl;
      break;
    case 3: //���������� ������� �� �����
      cout << "������� ����������� �������: " << endl;
      cin >> dimension;
      cout << "������� ���� �� �����: " << endl;
      //cin >> filePath;
      filePath = "input_matrix.txt";
      if (matrixPtr != nullptr) {
        delete matrixPtr;
      }
      matrixPtr = ReadMatrixFromFile(filePath, dimension);
      cout << "��������� �������: " << endl;
      cout << *matrixPtr;
      cout << endl;
      break;
    case 4: // ��������� ������� � ����
      if (matrixPtr == nullptr) {
        cout << "������� ������� �������!" << endl;
        break;
      }
      cout << "������� �������� �����: ";
      cin >> filePath;
      filePath = "saved_matrix.txt";
      SaveMatrix(filePath, matrixPtr);
      break;
    case 5: //������� ������� �� �������
      if (matrixPtr == nullptr) {
        cout << "������� �����������!" << endl;
        break;
      }
      else {
        cout << "������� �������: " << endl;
        cout << *matrixPtr;
        cout << endl;
      }
      break;
    case 6:
      algsBoolean.resize(COUNT_ALGS, false);
      //������� ������ ����������
      ChoiceAlgs(algsBoolean);
      break;
    case 7:
      //���������� � ����� ����������� + ��������� ��� �� ��������� ����������
      if (matrixPtr == nullptr) {
        cout << "������� ������� ������� ���������!" << endl;
        break;
      }
      else if (std::count_if(algsBoolean.begin(), algsBoolean.end(),
        [](bool i) {return i; }) == 0) {
        cout << "�� ������� �� ������ ���������!" << endl;
        break;
      }
      else {
        algs.resize(COUNT_ALGS, nullptr);
        CreateAlgs(algs, algsBoolean);
        vector<double> times(COUNT_ALGS, 0.0);
        for (Algorithm* alg : algs) {
          if (alg != nullptr) {
            alg->SetMatrix(*matrixPtr);
            TestAlg(alg);
          }
        }
        SaveResultsAfterTestAlgs(algs, times);
        break;
      }
    case 8://�����������

      if (std::count_if(algsBoolean.begin(), algsBoolean.end(),
        [](bool i) {return i; }) == 0)
      {
        cout << "�� ������� �� ������ ���������!" << endl;
        break;
      }
      CreateAlgs(algs, algsBoolean);
      cout << "�������� ��� ������������: " << endl;
      cout << "1)����������� �� �������� ������� ������" << endl;
      cout << "2)����������� �� �������� ��������" << endl;
      cin >> choice;
      if (choice == 1) {
        ExperimentByTime(algs);
      }
      else if (choice == 2) {
        ExperimentByResults(algs);
      }
      else {
        cout << "������ ������ ���� ������������" << endl;
      }
      break;
    case 0: //���������� ������ ���������
      exit(1);
      break;
    default:
      cout << "������, ��� ����� ������!" << endl;
      break;
    }
  }
}