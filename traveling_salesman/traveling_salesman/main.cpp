#include "Matrix.h"
#include <iostream>
#include "AntColonyAlg.h"
#include "BruteForceAlg.h"
#include "TestSpeed.h"
#include "NearestNeighboor.h"
#include "ImprovedNearestNeighboor.h"
#include "LittleAlg.h"
#include <random>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

const int COUNT_ALGS = 5;

enum class Algs
{
  bruteForce=0,
  ant=1,
  nearNeigh=2,
  upNearNeigh=3,
  bounds=4
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
  if (choice) {
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
	if (isSymetric) {
	  for (size_t j = i; j < dem; j++)
	  {
		if (i == j) {
		  matrix[i][j] = INT_MAX;
		}
		else {
		  matrix[i][j] = GenerateNum(minBound, maxBound);
		}
	  }
	}
	else {
	  for (size_t j = 0; j < dem; j++)
	  {
		if (i == j) {
		  matrix[i][j] = INT_MAX;
		}
		else {
		  matrix[i][j] = GenerateNum(minBound, maxBound);
		}
	  }
	}
  }
  return new AdjacencyMatrixG<int>(matrix);
}

AdjacencyMatrixG<int>* ReadMatrixFromFile(string filePath, int demension) {
  std::ifstream file(filePath);
  vector<vector<int>> matrix;
  matrix.resize(demension);
  for (size_t i = 0; i < demension; i++)
  {
	matrix[i].resize(demension);
	for (size_t j = 0; j < demension; j++)
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
  while (!isExit) {
	cout << "�������� ��������(��� ������ ������� 0): " << endl;
	cin >> choice;
	switch (choice)
	{
	case 1:
	  algs[static_cast<int>(Algs::bruteForce)] = true;
	  break;
	case 2:
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
	case 0:
	  isExit = true;
	default:
	  cout << "������ ������ ���������" << endl;
	  break;
	}
  }
}

int main(int argc, char* argv[])
{
  srand(3);
  //��������� ���������
  int minBound = 10;
  int maxBound = 100;
  bool isSymmetric = false;
  int demension = 10;

  //���������
  vector<Algorithm*> algs;
  //��������� ����������
  bool isExit = false;
  int choice = -1;
  string filePath;
  //�������
  AdjacencyMatrixG<int>* matrixPtr;
  

  setlocale(LC_ALL, "Russian");
  while (!isExit) {
	ShowMenu();
	cout << "��� �����: ";
	cin >> choice;
	switch (choice)
	{
	case 1: // ����� �������, ���������� �� ������ � ����������
	  GenerationPreference(isSymmetric, demension, minBound, maxBound);
	  break;
	case 2: // ��������� ������� � ����� �� �� �����
	  matrixPtr = GenerateMatrix(isSymmetric, demension, minBound, maxBound);
	  cout << "��������������� �������: " << endl;
	  cout << *matrixPtr;
	  cout << endl;
	  break;
	case 3: //���������� ������� �� �����
	  cout << "������� ���� �� �����: " << endl;
	  //cin >> filePath;
	  filePath = "input_matrix.txt";
	  if (matrixPtr == nullptr)
		delete matrixPtr;
	  matrixPtr = ReadMatrixFromFile(filePath, demension);
	  cout << "��������� �������: " << endl;
	  cout << *matrixPtr;
	  cout << endl;
	  break;
	case 4: // ��������� ������� � ����
	  cout << "������� �������� �����: " << endl;
	  //cin >> filePath;
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
	  //������� ������ ����������

	  break;
	case 7:
	  //���������� � ����� ����������� + ��������� ��� �� ��������� ����������
	  break;
	case 8:
	  //����������� � ����������� ��������� ����������
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