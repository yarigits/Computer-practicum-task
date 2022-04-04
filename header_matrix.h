#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <cmath>
#include <fstream>
#include <sstream>
#include <tuple>
#include <vector>
#include <thread>
#include <atomic>
#include <cstdlib>

using namespace std;

//______________________ Базовый класс ___________________________________________

class Matrix	// класс для задания матриц и векторов разной размерности
{
	int rows, cols;	// число строк и столбцов

protected:
	double* matrix;		// динамический массив, содержащий элементы матрицы/вектора

public:
	Matrix();	// конструктор по умолчанию
	Matrix(int r, int c, int flag = 1);		// конструктор для задания конкретной матрицы/вектора 
	Matrix(double* arr, int r, int c);	// конструктор для инициализации матрицы переданным в конструктор массивом

	Matrix(std::initializer_list<double> list, int r, int c);	// конструктор для ЛР5

	/* flag отвечает за РУЧНУЮ или АВТОМАТИЧЕСКУЮ инициализацию элементов матрицы - нужен при произведении матриц или 
	при инициализации объектов дочерних классов. По умолчанию = 1 - инициализация РУЧНАЯ, то есть через консоль */

	~Matrix();	// деструктор
	Matrix(const Matrix& M);	// конструктор копирования
	void operator =(const Matrix& M);	// перегрузка оператора присваивания

	//___________ Перегрузка операторов и объявление методов и функций для ЛР1 ___________

	Matrix operator +(const Matrix& R);
	Matrix operator -(const Matrix& R);
	Matrix operator *(double num);	// перегрузка операции умножения матрицы на число справа
	friend Matrix operator *(double num, const Matrix& L);	// перегрузка операции умножения матрицы на число слева
	Matrix operator *(const Matrix& R);
	Matrix Adamar(const Matrix& R);	// произведения Адамара для матриц
	friend Matrix Adamar(const Matrix& L, const Matrix& R);	// произведение Адамара с двумя параметрами
	friend ostream& operator <<(ostream& out, const Matrix& N);	// перегрузка оператора вывода в выходной поток

	//____________ Объявление методов и функций для ЛР2 _______________________________

	double Trace();	// метод для подсчёта следа матрицы (матрицы должна быть квадратной)
	friend double Trace(const Matrix& N);	// функция для подсчёта следа
	double Det();	// метод для подсчёта определителя матрицы (матрица должна быть квадратной)
	friend double Det(const Matrix& N);	// функция для подсчёта определителя
	Matrix Gauss(int flag = 0);	// функция для преобразования матрицы методом Гаусса
	double Scalar(const Matrix& R);	// метод для скалярного произведения векторов
	friend double Scalar(const Matrix& L, const Matrix& R);	// функция для скалярного произведения векторов
	double EuclidNorm();	// метод для вычисления эвклидовой нормы
	friend double EuclidNorm(const Matrix& N);	// функция для вычисление евклидовой нормы вектора
	double MaxNorm();	// метод для нахождения максимальной нормы вектора
	friend double MaxNorm(const Matrix& N);	// функция для нахождения максимальной нормы впектора

	/* норма Фробениуса для матрицы вычисляется так же, как евклидова норма вектора - функция EuclidNorm */

	//___________ Объявление методов и функций для ЛР3 _______________________________

	double Angle(const Matrix& R);	// метод для поиска угла между векторами (в градусах)
	friend double Angle(const Matrix& L, const Matrix& R);	// функция для поиска угла между векторами
	int Rank();	//  метод для поиска ранга матрицы
	friend int Rank(const Matrix& N);	// функция для поика ранга матрицы
	Matrix Reverse();	// метод для нахождения обратной матрицы
	friend Matrix Reverse(const Matrix& N);	// функция для нахождения обратной матрицы
	Matrix Transpose();	// метод для нахождения транспонированной матриц
	friend Matrix Transpose(const Matrix& N);	// функция для нахождения транспонированной матриц

	//_______  Перегрузка операторов и объявление методов и функций для ЛР4  _________

	friend ofstream& operator <<(ofstream& out, const Matrix& N);	// перегрузка оператора вывода в текстовый файл
	friend ifstream& operator >>(ifstream& in, Matrix& N);	// перегрузка оператора ввода из текстового файла
	void ReadBin(ifstream& in);	// метод для чтения из бинарного файла
	void WriteBin(ofstream& out);	// метод для записи в бинарный файл

	//___________ Дополнение для выполнения ЛР5 ______________________________________

	friend class PCA;	// для доступа к полям класса Matrix
};

//____________________ Порождённые классы ________________________________________

class Unit_Matrix : public Matrix	// Единичная матрица (квадратная)
{
public:
	Unit_Matrix(int d = 1);	
};

class Diagonal : public Matrix	// диагональная матрица (квадратная)
{
public:
	Diagonal(int d = 1);		// стандартный конструктор
	Diagonal(double* arr, int d = 1);	// конструктор для инициализации матрицы переданным в конструктор массивом

	/* При этом переданный массив должен быть размера dxd, то есть массив будет полностью скопирован в матрицу. 
	Из этого следует, что массив должен быть корректно написан - на нужных местах стоят КАКИЕ-ТО ЧИСЛА,
	а на всех остальных - НУЛИ */
};

class Upper_triangular : public Matrix	// верхнетреугольная матрица (квадратная)
{
public:
	Upper_triangular(int d = 1);
	Upper_triangular(double* arr, int d = 1);
};

class Lower_triangular : public Matrix	// нижнетреугольная матрица (квадратная)
{
public:
	Lower_triangular(int d = 1);
	Lower_triangular(double* arr, int d = 1);
};

class Symmetrical : public Matrix	// симметричная матрица (квадратная)
{
public:
	Symmetrical(int d = 1);
	Symmetrical(double* arr, int d = 1);
};

//_____________________ Дополнительные классы ______________________________________________________

class PCA	// класс в ЛР5 для реализования методов обработки матрицы данных
{
public:
	Matrix matrix;	// поле для хранения данных матрицы

	PCA(Matrix mat) : matrix(mat) {}	// конструктор

	// методы для предобработки данных
	Matrix center();	// центрирование
	Matrix scaling();	// шкалирование

	std::tuple<Matrix, Matrix, Matrix> NIPALS(int PC);	// метод для разложения матрицы алгоритмом NIPALS
	Matrix leverage(int PC);	// метод для подсчёта размахов для всех строк матрицы
	Matrix deviation(int PC);	// метод для подсчёта отклонений для всех строк матрицы
	std::pair<double, double> dispersion(int PC);	// метод для подсчёта полной и объяснённой дисперсий матрицы
};

//_____________________ Вспомогательные функции ______________________________________________________

int MaxLenElem(double* arr, int size);	// функция для поиска максимальной длины элемента массива (количества цифр в числе)
void ValueError(string& s);		// функция для проверки правильности введённых значений
void Game(int id);	// функция для ЛР6 для изображения игры на поле (id - номер игрока)

//_____________________ Классы для вызова исключений _________________________________________

class SizeError	// для проверки соответствуют ли размеры матриц условиям
{
public:
	string size_err;
	SizeError(string e) : size_err(e) {};
};

class InputError	// для проверки правильности вводимых данных/передаваемых параметров или массивов
{
public:
	string input_err;
	InputError(string e) : input_err(e) {};
};

class ZeroDetError	// для проверки вырожденности матрицы
{
public:
	string det_err;
	ZeroDetError(string e) : det_err(e) {};
};