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
#include <iomanip>

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

//Параметры генерации
int minBound = 10;
int maxBound = 100;
bool isSymmetric = false;
int dimension = 10;

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

void SaveResultsAfterExpByTime(const vector<Algorithm*>& algs,
  const vector<vector<double>>& times, const vector<int>& dimensions) {
  int sizeAlgName = 30;
  int sizeDim = 7;
  int sizeTime = 10;
  int choice = 0;
  std::cout << std::setw(sizeAlgName) <<std::left << "Algorithm" <<  std::setw(sizeDim) <<
	"Dim" << std::setw(sizeTime) << "Time" << std::endl;

  for (size_t i = 0; i < COUNT_ALGS; i++)
  {
	if (algs[i] != nullptr) {
	  int k = 0;
	  for (auto dim : dimensions) {
		std::cout << std::setw(sizeAlgName) << std::left << algs[i]->GetAlgName()
		  << std::setw(sizeDim) <<
		  dim << std::setw(sizeTime) << times[i][k] << std::endl;
		k++;
	  }
	}
  }

  std::cout << std::endl;
  std::cout << "Сохранить результаты в файл? (1-Да, 2-Нет)" << std::endl;
  cin >> choice;
  if (choice == 1) {
	string filePath;
	std::cout << "Введите название файла: " << std::endl;
	cin >> filePath;
	std::ofstream file(filePath);
	file << std::setw(sizeAlgName) << std::left << "Algorithm" << std::setw(sizeDim) <<
	  "Dim" << std::setw(sizeTime) << "Time" << std::endl;

	for (size_t i = 0; i < COUNT_ALGS; i++)
	{
	  if (algs[i] != nullptr) {
		int k = 0;
		for (auto dim : dimensions) {
		  file << std::setw(sizeAlgName) << std::left << algs[i]->GetAlgName()
			<< std::setw(sizeDim) <<
			dim << std::setw(sizeTime) << times[i][k] << std::endl;
		  k++;
		}
	  }
	}
	file.close();
	std::cout << "Результаты сохранены!" << std::endl;
  }
  else if (choice == 2) {
	return;
  }
  else {
	std::cout << "Ошибка!" << std::endl;
  }
  
}

void SaveResultsAfterTestAlgs(const vector<Algorithm*>& algs, const vector<double>& times) {
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

void SaveResultsAfterExpByRes(const vector<Algorithm*>& algs,
  const vector<double>& results, int countExperiments) {
  int sizeAlgName = 30;
  int sizeDim = 7;
  int sizeResults = 15;
  int choice;

  std::cout << "Число экспериментов: " << countExperiments << std::endl;
  std::cout << std::setw(sizeAlgName) << std::left << "Algorithm" << std::setw(sizeDim) <<
	"Dim" << std::setw(sizeResults) << "Solution Mean" << std::endl;

  for (size_t algI = 0; algI < COUNT_ALGS; algI++)
  {
	if (algs[algI] != nullptr) {
	  std::cout << std::setw(sizeAlgName) << std::left << algs[algI]->GetAlgName()
		<< std::setw(sizeDim) <<
		dimension << std::setw(sizeResults) << results[algI] << std::endl;
	}
  }

  std::cout << std::endl;
  std::cout << "Сохранить результаты в файл? (1-Да, 2-Нет)" << std::endl;
  cin >> choice;
  if (choice == 1) {
	string filePath;
	std::cout << "Введите название файла: " << std::endl;
	cin >> filePath;
	std::ofstream file(filePath);
	file << "Число экспериментов: " << countExperiments << std::endl;
	for (size_t algI = 0; algI < COUNT_ALGS; algI++)
	{
	  if (algs[algI] != nullptr) {
		file << std::setw(sizeAlgName) << std::left << algs[algI]->GetAlgName()
		  << std::setw(sizeDim) <<
		  dimension << std::setw(sizeResults) << results[algI] << std::endl;
	  }
	}
	file.close();
	std::cout << "Результаты сохранены!" << std::endl;
  }
  else if (choice == 2) {
	return;
  }
  else {
	std::cout << "Ошибка!" << std::endl;
  }
}

void ExperimentByResults(const vector<Algorithm*>& algs) {
  int countExperiments = 5;
  std::vector<double> results(COUNT_ALGS, 0);
  cout << "Введите число экспериментов: ";
  cin >> countExperiments;
  for (size_t experiment = 0; experiment < countExperiments; experiment++)
  {
	AdjacencyMatrixG<int>* matrix = GenerateMatrix(isSymmetric, dimension, minBound, maxBound);
	for (size_t algI = 0; algI < COUNT_ALGS; algI++)
	{
	  if (algs[algI] != nullptr) {
		algs[algI]->SetMatrix(*matrix);
		algs[algI]->Run();
		results[algI] += algs[algI]->GetMinWeight();
	  }
	}
  }

  for (size_t i = 0; i < COUNT_ALGS; i++)
  {
	results[i] /= countExperiments;
  }

  SaveResultsAfterExpByRes(algs, results, countExperiments);
}

void ExperimentByTime(const vector<Algorithm*>& algs) {
  int nMin = 10;
  int nMax = 100;
  int step = 10;
  vector<vector<double>> times(COUNT_ALGS);
  vector<int> dimensions;
  cout << "Введите начальное значение размерности матрицы: ";
  cin >> nMin;
  cout << std::endl;
  cout << "Введите конечное значение размерности матрицы: ";
  cin >> nMax;
  cout << std::endl;
  cout << "Введите значение шага увеличения размерности матрицы: ";
  cin >> step;
  cout << std::endl;
  for (size_t curN = nMin; curN <= nMax; curN+=step) 
  {
	dimensions.push_back(curN);
	AdjacencyMatrixG<int>* matr = GenerateMatrix(isSymmetric, curN, minBound, maxBound);
	for (size_t algI = 0; algI < COUNT_ALGS; algI++)
	{
	  if (algs[algI] != nullptr) {
		algs[algI]->SetMatrix(*matr);
		times[algI].push_back(ts::TestSpeed::TestAlg(algs[algI]));
	  }
	}
  }

  SaveResultsAfterExpByTime(algs, times, dimensions);
}


int main(int argc, char* argv[])
{

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
	  GenerationPreference(isSymmetric, dimension, minBound, maxBound);
	  break;
	case 2: // Генерация матрицы и вывод ее на экран
	  matrixPtr = GenerateMatrix(isSymmetric, dimension, minBound, maxBound);
	  cout << "Сгенерированная матрица: " << endl;
	  cout << *matrixPtr;
	  cout << endl;
	  break;
	case 3: //Считывание матрицы из файла
	  cout << "Введите размерность матрицы: " << endl;
	  cin >> dimension;
	  cout << "Введите путь до файла: " << endl;
	  //cin >> filePath;
	  filePath = "input_matrix.txt";
	  if (matrixPtr != nullptr) {
		delete matrixPtr;
	  }
	  matrixPtr = ReadMatrixFromFile(filePath, dimension);
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
	case 8://Эксперимент

	  if (std::count_if(algsBoolean.begin(), algsBoolean.end(),
		[](bool i) {return i; }) == 0) 
	  {
		cout << "Не выбрано ни одного алгоритма!" << endl;
		break;
	  }
	  CreateAlgs(algs, algsBoolean);
	  cout << "Выберите тип эксперимента: " << endl;
	  cout << "1)Эксперимент по изучению времени работы" << endl;
	  cout << "2)Эксперимент по изучению результата работы" << endl;
	  cin >> choice;
	  if (choice == 1) {
		ExperimentByTime(algs);
	  }
	  else if (choice == 2) {
		ExperimentByResults(algs);
	  }
	  else {
		cout << "Ошибка выбора типа эксперимента" << endl;
	  }
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