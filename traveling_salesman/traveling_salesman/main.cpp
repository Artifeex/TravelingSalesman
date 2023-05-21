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

//Параметры Муравьиного алгоритма
double alfa = 1.0;
double beta = 2.0;
double startPheromone = 0.2;
double constClosness = 1.0;
int countAnts = 12;
double pheromoneResidue = 0.3;
double totalPheromone = 1.0;
int countIterations = 5;


enum class Algs
{
  bruteForce=0,
  ant=1,
  nearNeigh=2,
  upNearNeigh=3,
  bounds=4
};

void ShowMenu() {
  cout << "1) Параметры генерации" << endl;
  cout << "2) Сгенерировать матрицу" << endl;
  cout << "3) Задать матрицу из файла" << endl;
  cout << "4) Сохранить матрицу" << endl;
  cout << "5) Показать текущую матрицу" << endl;
  cout << "6) Выбрать алгоритмы" << endl;
  cout << "7) Вычислить" << endl;
  cout << "8) Эксперимент" << endl;
  cout << "0) Выход" << endl;
}

void GenerationPreference(bool& isSymetric, int& dem, int& minBound, int& maxBound) {

  int choice = 0;
  cout << "Симметричная ?(1 - Да, 2 - Нет): ";
  cin >> choice;
  if (choice) {
	isSymetric = true;
  }
  else {
	isSymetric = false;
  }
  cout << endl;
  cout << "Размерность матрицы: ";
  cin >> dem;
  cout << endl;
  cout << "Нижняя граница генерации: ";
  cin >> minBound;
  cout << endl;
  cout << "Верхняя граница генерации: ";
  cin >> maxBound;
  cout << endl;
}

//Функция общения с пользователем, которая занимается сбором параметров для муравьиного алгоритма
void GetParamsAntColonyAlg() {

}

int GenerateNum(int minBound, int maxBound) {
  std::random_device random_device;
  std::mt19937 generator(random_device());
  std::uniform_int_distribution<> distribution(minBound, maxBound);
  return distribution(generator);
  //return rand() % (maxBound - minBound) + minBound;
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
  cout << "Алгоритмы: " << endl;
  cout << "1) Простой перебор" << endl;
  cout << "2) Муравьиный алгоритм" << endl;
  cout << "3) Ближайшего соседа" << endl;
  cout << "4) Модернизированный алгоритм ближайшего соседа" << endl;
  cout << "5) Метод ветвей и границ" << endl;
  while (!isExit) {
	cout << "Выберите алгоритм(для выхода введите 0): " << endl;
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
	  break;
	default:
	  cout << "Ошибка выбора алгоритма" << endl;
	  break;
	}
  }
}

void CreateAlgs(vector<Algorithm*>& algs, vector<bool> algsBoolean,
  const AdjacencyMatrixG<int>& matrix) {
  for (int algsIndex = 0; algsIndex < COUNT_ALGS; algsIndex++) {
	if (algsBoolean[algsIndex] == true) {
	  switch (algsIndex)
	  {
	  case 0:
		algs[0] = new BruteForceAlg(matrix);
		break;
	  case 1:
		algs[1] = new AntColonyAlg(matrix, alfa, beta,
		  startPheromone, constClosness, countAnts, pheromoneResidue,
		  totalPheromone, countIterations);
		break;
	  case 2:
		algs[2] = new NearestNeighboor(matrix);
		break;
	  case 3:
		algs[3] = new ImprovedNearestNeighboor(matrix);
		break;
	  case 4:
		algs[4] = new LittleAlg(matrix, INT_MAX - 1);
		break;
	  default:
		cout << "Ошибка в создании алгоритмов!" << endl;
		break;
	  }
	}
  }
}

double TestAlg(Algorithm* alg) {
  int weight = -1;
  vector<int> minRoute;
  double time = ts::TestSpeed::TestAlg(alg, weight, minRoute);
  cout << "Алгоритм: " << alg->GetAlgName() << endl;
  cout << "Стоимость минимального найденного пути: " << weight << endl;
  cout << "Маршрут с минимального найденным путем: ";
  for (auto val : minRoute) {
	cout << val << " ";
  }
  cout << endl;
  cout << "Время работы: " << time << " c" << endl;
  return time;
}

void SaveResultsAfterTestAlgs(const vector<Algorithm*>& algs, vector<double> times) {
  int choice;
  string path;
  cout << "Сохранить результаты в файл?(1 - Да, 2 - Нет): ";
  cin >> choice;
  if (choice == 1) {
	cout << endl;
	cout << "Введите имя файла: ";
	cin >> path;
	cout << endl;
	std::ofstream file(path);
	for (size_t i = 0; i < COUNT_ALGS; i++)
	{
	  if (algs[i] != nullptr) {
		file << "Алгоритм: " << algs[i]->GetAlgName() << endl;
		file << "Стоимость минимального найденного пути: " << algs[i]->GetMinWeight() << endl;
		file << "Маршрут с минимального найденным путем: ";
		for (auto val : algs[i]->GetMinRoute()) {
		  file << val << " ";
		}
		file << endl;
		file << "Время работы: " << times[i] << " c" << endl;
		file << endl;
	  }
	}
  }
}


int main(int argc, char* argv[])
{
  srand(3);
  //Параметры генерации
  int minBound = 10;
  int maxBound = 100;
  bool isSymmetric = false;
  int demension = 10;

  //Алгоритмы
  vector<Algorithm*> algs(COUNT_ALGS, nullptr);
  vector<bool> algsBoolean(COUNT_ALGS, false);
  //Служебные переменные
  bool isExit = false;
  int choice = -1;
  string filePath;
  //Матрица
  AdjacencyMatrixG<int>* matrixPtr = nullptr;
  

  setlocale(LC_ALL, "Russian");
  while (!isExit) {
	ShowMenu();
	cout << "Ваш выбор: ";
	cin >> choice;
	switch (choice)
	{
	case 1: // Вызов функции, отвечающей за работу с генерацией
	  GenerationPreference(isSymmetric, demension, minBound, maxBound);
	  break;
	case 2: // Генерация матрицы и вывод ее на экран
	  matrixPtr = GenerateMatrix(isSymmetric, demension, minBound, maxBound);
	  cout << "Сгенерированная матрица: " << endl;
	  cout << *matrixPtr;
	  cout << endl;
	  break;
	case 3: //Считывание матрицы из файла
	  cout << "Введите размерность матрицы: " << endl;
	  cin >> demension;
	  cout << "Введите путь до файла: " << endl;
	  //cin >> filePath;
	  filePath = "input_matrix.txt";
	  if (matrixPtr != nullptr) {
		delete matrixPtr;
	  }
	  matrixPtr = ReadMatrixFromFile(filePath, demension);
	  cout << "Считанная матрица: " << endl;
	  cout << *matrixPtr;
	  cout << endl;
	  break;
	case 4: // Сохранить матрицу в файл
	  if (matrixPtr == nullptr) {
		cout << "Сначала задайте матрицу!" << endl;
		break;
	  }
	  cout << "Введите название файла: " << endl;
	  //cin >> filePath;
	  filePath = "saved_matrix.txt";
	  SaveMatrix(filePath, matrixPtr);
	  break;
	case 5: //Вывести матрицу на консоль
	  if (matrixPtr == nullptr) {
		cout << "Матрица отсутствует!" << endl;
		break;
	  }
	  else {
		cout << "Текущая матрица: " << endl;
		cout << *matrixPtr;
		cout << endl;
	  }
	  break;
	case 6:
	  algsBoolean.resize(COUNT_ALGS, false);
	  //Функция выбора алгоритмов
	  ChoiceAlgs(algsBoolean);
	  break;
	case 7:
	  //Вычисление и вывод результатов + сохранить или не сохранить результаты
	  if (matrixPtr == nullptr) {
		cout << "Сначала задайте матрицу смежности!" << endl;
		break;
	  }
	  else if (std::count_if(algsBoolean.begin(), algsBoolean.end(),
		[](bool i) {return i; }) == 0) {
		cout << "Не выбрано ни одного алгоритма!" << endl;
		break;
	  }
	  else {
		algs.resize(COUNT_ALGS, nullptr);
		CreateAlgs(algs, algsBoolean, *matrixPtr);
		vector<double> times(COUNT_ALGS, 0.0);
		for (Algorithm* alg : algs) {
		  if (alg != nullptr) {
			TestAlg(alg);
		  }
		}
		SaveResultsAfterTestAlgs(algs, times);
		break;
	  }
	case 8:
	  //Эксперимент и предложение сохранить результаты
	  break;
	case 0: //Завершение работы программы
	  exit(1);
	  break;
	default:
	  cout << "Ошибка, нет такой кнопки!" << endl;
	  break;
	}
  }
}