#include "header_matrix.h"
#define PI 3.14159265

using namespace std;

//________________________ Конструкторы/деструктор базового класса ________________________________

// определение конструктора по умолчанию (вектор 1х1 из элемента 1)
Matrix::Matrix(): rows(1), cols(1)
{
	matrix = new double[1];
	matrix[0] = 1.0;
}

// реализация конструктора для создания конкретной матрицы/вектора 
Matrix::Matrix(int r, int c, int flag): rows(r), cols(c)
{
	if (rows < 1 || cols < 1) throw InputError(string("Wrong matrix dimensions were given"));

	matrix = new double[rows * cols];
	if (flag) {
		cout << "\nWrite down the values of matrix/vector:" << endl;	// задание значений элементов массива
		string temp;	// переменная для проверки вводимых значений элементов матрицы
		int k = 0;

		for (int i = 0; i < rows; ++i)	// ввод элементов массива
		{
			for (int j = 0; j < cols; ++j)
			{
				cout << "A[" << i + 1 << ", " << j + 1 << "] = ";
				cin >> temp;
				try {
					ValueError(temp);	// проверям введённое значение
					matrix[k] = stof(temp);
				}
				catch (...)		// любые ошибки пробрасываем дальше, до главной программы
				{
					throw;
				}
				++k;
			}
		}
	}
	else {
		for (int i = 0; i < rows * cols; ++i)	// ввод элементов массива
		{
			matrix[i] = 0.0;	// создание матрицы нужного размера, заполненной нулями
		}
	}
}

// инициализация матрицы переданным в конструктор массивом
Matrix::Matrix(double* arr, int r, int c): rows(r), cols(c)
{
	if (rows < 1 || cols < 1) throw InputError(string("Wrong matrix dimensions were given"));

	matrix = new double[rows * cols];
	for (int i = 0; i < rows * cols; ++i) matrix[i] = arr[i];
}

// реализация конструктора с переданным initializer_list (ЛР5)
Matrix::Matrix(std::initializer_list<double> list, int r, int c): rows(r), cols(c)
{
	if (rows < 1 || cols < 1 || rows*cols != list.size()) throw InputError(string("Wrong matrix dimensions were given"));

	matrix = new double[rows*cols];
	int j = 0;

	for (double i : list) 
	{
		matrix[j] = i;
		++j;
	}
}

// реализация деструктора по умолчанию
Matrix::~Matrix()
{
	delete[] matrix;
}

// реализация конструктора копирования
Matrix::Matrix(const Matrix& M)
{
	rows = M.rows;
	cols = M.cols;
	matrix = new double[rows * cols];

	for (int i = 0; i < rows * cols; ++i)	// копирование массива
	{
			matrix[i] = M.matrix[i];
	}
}

// реализация перегрузки оператора присваивания
void Matrix::operator =(const Matrix& M)
{
	rows = M.rows;
	cols = M.cols;
	matrix = new double[rows * cols];

	for (int i = 0; i < rows * cols; ++i)	// копирование массива
	{
		matrix[i] = M.matrix[i];
	}
}

//_______________________________________ Конструкторы дочерних классов __________________________________________________

// конструктор единичной матрицы
Unit_Matrix::Unit_Matrix(int d): Matrix(d, d, 0)
{
	if (d < 1) throw InputError(string("Wrong unit matrix dimensions were given"));

	int k = 0;

	for (int i = 0; i < d; ++i)	// ввод элементов массива
	{
		for (int j = 0; j < d; ++j)
		{
			matrix[k] = i == j ? 1.0 : 0.0;
			++k;
		}
	}
}

// конструктор диагональной матрицы
Diagonal::Diagonal(int d): Matrix(d, d, 0)
{
	if (d < 1) throw InputError(string("Wrong diagonal matrix dimensions were given"));

	string temp;
	int k = 0;
	cout << "\nWrite down the values of diagonal matrix:" << endl;	// задание значений элементов массива

	for (int i = 0; i < d; ++i)	// ввод элементов массива
	{
		for (int j = 0; j < d; ++j)
		{
			if (i == j) {
				cout << "A[" << i + 1 << ", " << j + 1 << "] = ";
				cin >> temp;
				try {
					ValueError(temp);	// проверям введённое значение
					matrix[k] = stof(temp);
				}
				catch (...)		// любые ошибки пробрасываем дальше, до главной программы
				{
					throw;
				}
			}
			else matrix[k] = 0;
			++k;
		}
	}
}

// инициализация диагональной матрицы переданным в конструктор массивом
Diagonal::Diagonal(double* arr, int d) : Matrix(d, d, 0)
{
	if (d < 1) throw InputError(string("Wrong diagonal matrix dimensions were given"));
	for (int i = 0; i < d; ++i)
	{
		for (int j = 0; j < d; ++j)
		{
			if (i != j && arr[i * d + j] != 0) throw InputError(string("The matrix given is not diagonal"));
		}
	}

	for (int i = 0; i < d * d; ++i)
	{
		matrix[i] = arr[i];
	}
}

// конструктор верхнетреугольной матрицы
Upper_triangular::Upper_triangular(int d): Matrix(d, d, 0)
{
	if (d < 1) throw InputError(string("Wrong upper triangular matrix dimensions were given"));

	string temp;
	int k = 0;
	cout << "\nWrite down the values of upper triangular matrix:" << endl;	// задание значений элементов массива

	for (int i = 0; i < d; ++i)	// ввод элементов массива
	{
		for (int j = 0; j < d; ++j)
		{
			if (i <= j) {
				cout << "A[" << i + 1 << ", " << j + 1 << "] = ";
				cin >> temp;
				try {
					ValueError(temp);	// проверям введённое значение
					matrix[k] = stof(temp);
				}
				catch (...)		// любые ошибки пробрасываем дальше, до главной программы
				{
					throw;
				}
			}
			else matrix[k] = 0;
			++k;
		}
	}
}

Upper_triangular::Upper_triangular(double* arr, int d) : Matrix(d, d, 0)
{
	if (d < 1) throw InputError(string("Wrong upper triangular matrix dimensions were given"));
	for (int i = 0; i < d; ++i)
	{
		for (int j = 0; j < d; ++j)
		{
			if (i > j && arr[i * d + j] != 0) throw InputError(string("The matrix given is not upper triangular"));
		}
	}

	for (int i = 0; i < d * d; ++i)
	{
		matrix[i] = arr[i];
	}
}

// конструктор нижнетреугольной матрицы
Lower_triangular::Lower_triangular(int d): Matrix(d, d, 0)
{
	if (d < 1) throw InputError(string("Wrong lower triangular matrix dimensions were given"));

	string temp;
	int k = 0;
	cout << "\nWrite down the values of lower triangular matrix:" << endl;	// задание значений элементов массива

	for (int i = 0; i < d; ++i)	// ввод элементов массива
	{
		for (int j = 0; j < d; ++j)
		{
			if (i >= j) {
				cout << "A[" << i + 1 << ", " << j + 1 << "] = ";
				cin >> temp;
				try {
					ValueError(temp);	// проверям введённое значение
					matrix[k] = stof(temp);
				}
				catch (...)		// любые ошибки пробрасываем дальше, до главной программы
				{
					throw;
				}
			}
			else matrix[k] = 0;
			++k;
		}
	}
}

Lower_triangular::Lower_triangular(double* arr, int d) : Matrix(d, d, 0)
{
	if (d < 1) throw InputError(string("Wrong lower triangular matrix dimensions were given"));
	for (int i = 0; i < d; ++i)
	{
		for (int j = 0; j < d; ++j)
		{
			if (i < j && arr[i * d + j] != 0) throw InputError(string("The matrix given is not lower triangular"));
		}
	}

	for (int i = 0; i < d * d; ++i)
	{
		matrix[i] = arr[i];
	}
}

// конструктор симметричной матрицы
Symmetrical::Symmetrical(int d): Matrix(d, d, 0)
{
	if (d < 1) throw InputError(string("Wrong symmetrical matrix dimensions were given"));

	string temp;
	int k = 0;
	cout << "\nWrite down the values of symmetrical matrix:" << endl;	// задание значений элементов массива

	for (int i = 0; i < d; ++i)	// ввод элементов массива
	{
		for (int j = 0; j < d; ++j)
		{
			if (i >= j) {
				cout << "A[" << i + 1 << ", " << j + 1 << "] = ";
				cin >> temp;
				try {
					ValueError(temp);	// проверям введённое значение
					matrix[k] = stof(temp);
				}
				catch (...)		// любые ошибки пробрасываем дальше, до главной программы
				{
					throw;
				}
			}
			else matrix[k] = 0;
			++k;
		}
	}

	for (int i = 0; i < d; ++i)	// цикл для создания симметричности
	{
		for (int j = 0; j < d; ++j)
		{
			if (i < j) {
				matrix[i * d + j] = matrix[j * d + i];
			}
		}
	}
}

Symmetrical::Symmetrical(double* arr, int d) : Matrix(d, d, 0)
{
	if (d < 1) throw InputError(string("Wrong symmetrical matrix dimensions were given"));
	for (int i = 0; i < d; ++i)
	{
		for (int j = 0; j < d; ++j)
		{
			if (arr[i * d + j] != arr[j * d + i]) throw InputError(string("The matrix given is not symmetrical"));
		}
	}

	for (int i = 0; i < d * d; ++i)
	{
		matrix[i] = arr[i];
	}
}

//______________________ Перегрузка операторов для выполнения арифметических операций _________________________

// перегрузка оператора сложения (матрицы должны быть одинаковой размерности)
Matrix Matrix::operator +(const Matrix& R)
{
	if (rows != R.rows || cols != R.cols) throw SizeError(string("Matrices have different sizes"));
	Matrix result = *this;
	
	for (int k = 0; k < rows * cols; ++k)
	{
		result.matrix[k] += R.matrix[k];
	}

	return result;
}

// перегрузка оператора вычитания (матрицы должны быть одинаковой размерности)
Matrix Matrix::operator -(const Matrix& R)
{
	if (rows != R.rows || cols != R.cols) throw SizeError(string("Matrices have different sizes"));

	Matrix result = *this;

	for (int k = 0; k < rows * cols; ++k)
	{
		result.matrix[k] -= R.matrix[k];
	}

	return result;
}

// перегрузка оператора умножения матрицы на число справа
Matrix Matrix::operator *(double num)
{
	Matrix result = *this;

		for (int i = 0; i < rows * cols; ++i)
		{
			result.matrix[i] *= num;
		}

	return result;
}

// перегрузка оператора умножения матриц (размерности должны быть вида n*m и m*k)
Matrix Matrix::operator *(const Matrix& R)
{
	if (cols != R.rows) throw \
		SizeError(string("Matrices' dimensions do not respond the conditions, consequently, they cannot be multiplied"));

	Matrix result(rows, R.cols, 0);

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < R.cols; ++j)
		{
			for (int k = 0; k < cols; ++k)
			{
				result.matrix[i * R.cols + j] += matrix[i * cols + k] * R.matrix[k * R.cols + j];
			}
		}
	}

	return result;
}

// перегрузка оператора умножения матрицы на число слева
Matrix operator *(double num, const Matrix& L)
{
	Matrix result = L;

	for (int i = 0; i < L.rows * L.cols; ++i)
	{
		result.matrix[i] *= num;
	}

	return result;
}

//_________________________________ Перегрузка оператора вывода для матрицы/вектора _______________________________

ostream& operator <<(ostream& out, const Matrix& N)
{
	int max = MaxLenElem(N.matrix, N.cols * N.rows);	// нахождение максимальной длины элемента массива
	int elem = 0;	// для подсчёта числа цифр в каждом элементе
	string spaces;		// строка с пробелами для использования её среза
	for (int i = 0; i < max; i++) spaces.append(" ");

	if (N.rows == 1)	// для вывода вектора - строки
	{
		out << "\n< ";	// верхняя часть левой скобки
		for (int i = 0; i < N.cols; ++i)	// выводим первую строку матрицы/вектора
		{
			if (N.matrix[i] == round(N.matrix[i]))
			{
				elem = to_string(int(N.matrix[i])).length();

				if ((max - elem) % 2 == 0) out << spaces.substr(0, (max - elem) / 2 + 1) << N.matrix[i] << \
					spaces.substr(0, (max - elem) / 2 + 1);
				else out << spaces.substr(0, (max - elem) / 2 + 1) << N.matrix[i] << \
					spaces.substr(0, (max - elem) / 2 + 2);
			}
			else
			{
				cout.precision(6);	// установка числа значащих знаков после запятой
				cout.setf(ios::fixed);	// переход к режиму числа с фиксированной точкой
				elem = to_string(N.matrix[i]).length();

				if ((max - elem) % 2 == 0) out << spaces.substr(0, (max - elem) / 2 + 1) << N.matrix[i] << \
					spaces.substr(0, (max - elem) / 2 + 1);
				else out << spaces.substr(0, (max - elem) / 2 + 1) << N.matrix[i] << \
					spaces.substr(0, (max - elem) / 2 + 2);
				cout.unsetf(ios::fixed);	// отключить вывод вещественных чисел в фиксированной форме
			}
		}
		out << " >" << endl;

		return out;
	}
	else	// для вывода всего остального
	{
		out << "\n/ ";	// верхняя часть левой скобки
		for (int i = 0; i < N.cols; ++i)	// выводим первую строку матрицы/вектора
		{
			if (N.matrix[i] == round(N.matrix[i]))
			{
				elem = to_string(int(N.matrix[i])).length();

				if ((max - elem) % 2 == 0) out << spaces.substr(0, (max - elem) / 2 + 1) << N.matrix[i] << \
					spaces.substr(0, (max - elem) / 2 + 1);
				else out << spaces.substr(0, (max - elem) / 2 + 2) << N.matrix[i] << \
					spaces.substr(0, (max - elem) / 2 + 1);
			}
			else
			{
				cout.precision(6);	// установка числа значащих знаков после запятой
				cout.setf(ios::fixed);	// переход к режиму числа с фиксированной точкой
				elem = to_string(N.matrix[i]).length();

				if ((max - elem) % 2 == 0) out << spaces.substr(0, (max - elem) / 2 + 1) << N.matrix[i] << \
					spaces.substr(0, (max - elem) / 2 + 1);
				else out << spaces.substr(0, (max - elem) / 2 + 2) << N.matrix[i] << \
					spaces.substr(0, (max - elem) / 2 + 1);
				cout.unsetf(ios::fixed);	// отключить вывод вещественных чисел в фиксированной форме
			}
		}
		out << " \\" << endl;		// верхняя часть правой скобки

		for (int i = 1; i < N.rows - 1; ++i)	// центральная часть матрицы/вектора
		{
			out << "| ";
			for (int j = 0; j < N.cols; ++j)
			{
				if (N.matrix[i * N.cols + j] == round(N.matrix[i * N.cols + j]))
				{
					elem = to_string(int(N.matrix[i * N.cols + j])).length();

					if ((max - elem) % 2 == 0) out << spaces.substr(0, (max - elem) / 2 + 1) << \
						N.matrix[i * N.cols + j] << spaces.substr(0, (max - elem) / 2 + 1);
					else out << spaces.substr(0, (max - elem) / 2 + 2) << N.matrix[i * N.cols + j] << \
						spaces.substr(0, (max - elem) / 2 + 1);
				}
				else
				{
					cout.precision(6);	// установка числа значащих знаков после запятой
					cout.setf(ios::fixed);	// переход к режиму числа с фиксированной точкой
					elem = to_string(N.matrix[i * N.cols + j]).length();

					if ((max - elem) % 2 == 0) out << spaces.substr(0, (max - elem) / 2 + 1) << N.matrix[i * N.cols + j] << \
						spaces.substr(0, (max - elem) / 2 + 1);
					else out << spaces.substr(0, (max - elem) / 2 + 2) << N.matrix[i * N.cols + j] << \
						spaces.substr(0, (max - elem) / 2 + 1);
					cout.unsetf(ios::fixed);	// отключить вывод вещественных чисел в фиксированной форме
				}
			}
			out << " |" << endl;
		}

		if (N.cols == 1)
		{
			if (N.matrix[N.rows - 1] == round(N.matrix[N.rows - 1]))
			{
				elem = to_string(int(N.matrix[N.rows - 1])).length();

				if ((max - elem) % 2 == 0) out << "\\ " << spaces.substr(0, (max - elem) / 2 + 1) << \
					N.matrix[N.rows - 1] << spaces.substr(0, (max - elem) / 2 + 1) << " /" << endl;
				else out << "\\ " << spaces.substr(0, (max - elem) / 2 + 2) << N.matrix[N.rows - 1] << \
					spaces.substr(0, (max - elem) / 2 + 1) << " /" << endl;
			}
			else
			{
				cout.precision(6);	// установка числа значащих знаков после запятой
				cout.setf(ios::fixed);	// переход к режиму числа с фиксированной точкой
				elem = to_string(N.matrix[N.rows - 1]).length();

				if ((max - elem) % 2 == 0) out << "\\ " << spaces.substr(0, (max - elem) / 2 + 1) << N.matrix[N.rows - 1] << \
					spaces.substr(0, (max - elem) / 2 + 1) << " /" << endl;
				else out << "\\ " << spaces.substr(0, (max - elem) / 2 + 2) << N.matrix[N.rows - 1] << \
					spaces.substr(0, (max - elem) / 2 + 1) << " /" << endl;
				cout.unsetf(ios::fixed);	// отключить вывод вещественных чисел в фиксированной форме
			}

			return out;
		}

		out << "\\ ";		// нижняя часть левой скобки
		for (int i = N.cols * (N.rows - 1); i < N.cols * N.rows; ++i)
		{
			if (N.matrix[i] == round(N.matrix[i]))
			{
				elem = to_string(int(N.matrix[i])).length();

				if ((max - elem) % 2 == 0) out << spaces.substr(0, (max - elem) / 2 + 1) << N.matrix[i] <<\
					spaces.substr(0, (max - elem) / 2 + 1);
				else out << spaces.substr(0, (max - elem) / 2 + 2) << N.matrix[i] << \
					spaces.substr(0, (max - elem) / 2 + 1);
			}
			else
			{
				cout.precision(6);	// установка числа значащих знаков после запятой
				cout.setf(ios::fixed);	// переход к режиму числа с фиксированной точкой
				elem = to_string(N.matrix[i]).length();

				if ((max - elem) % 2 == 0) out << spaces.substr(0, (max - elem) / 2 + 1) << N.matrix[i] << \
					spaces.substr(0, (max - elem) / 2 + 1);
				else out << spaces.substr(0, (max - elem) / 2 + 2) << N.matrix[i] << \
					spaces.substr(0, (max - elem) / 2 + 1);
				cout.unsetf(ios::fixed);	// отключить вывод вещественных чисел в фиксированной форме
			}
		}
		out << " /" << endl;	// нижняя часть правой скобки

		return out;
	}
}

//_______________________________ Вспомогательные функции и методы ЛР1 _________________________________________________

// произведение Адамара как метод класса (матрицы должны быть одинаковой размерности)
Matrix Matrix::Adamar(const Matrix& R)
{
	if (rows != R.rows || cols != R.cols) throw SizeError(string("Matrices have different sizes"));

	Matrix result = *this;

	for (int i = 0; i < rows * cols; ++i)
	{
		result.matrix[i] *= R.matrix[i];
	}

	return result;
}

// произведение Адамара с двумя параметрами - дружественная функция (матрицы должны быть одинаковой размерности)
Matrix Adamar(const Matrix& L, const Matrix& R)
{
	if (L.rows != R.rows || L.cols != R.cols) throw SizeError(string("Matrices have different sizes"));

	Matrix result = L;

	for (int i = 0; i < L.rows * L.cols; ++i)
	{
		result.matrix[i] *= R.matrix[i];
	}

	return result;
}

// нахождение максимальной длины элемента массива
int MaxLenElem(double* arr, int size)
{
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		if ( (arr[i] == round(arr[i])) && (max < (int) to_string(int(arr[i])).length()) )
		{
			max = to_string(int(arr[i])).length();
		}

		if ((arr[i] != round(arr[i])) && (max < (int) to_string(arr[i]).length()))
		{
			max = to_string(arr[i]).length();
		}
	 }
	return max;
}

// функция для проверки правильности введённого значения
void ValueError(string& s)
{
	setlocale(LC_NUMERIC, "en");	// вещественные числа пишутся через точку

	try		// если stof не сработает, то есть было введено не число, происходит пробрасывание исключения
	{
		if (s.find(",") != -1) throw InputError(string("Incorrect input values - real numbers should be written using '.' "));

		stof(s);

	}
	catch (invalid_argument)
	{
		throw InputError(string("Incorrect input values - should be numbers"));
	}
	catch (out_of_range)
	{
		throw InputError(string("Input values are too great"));
	}
	catch (InputError)
	{
		throw;
	}
	catch (...)
	{
		throw InputError(string("Unknown error emerged: Incorrect input values"));
	}
}

//________________________________ Вспомогательные функции и методы ЛР2 _________________________________________________

// метод для подсчёта следа матрицы
double Matrix::Trace()
{
	if (rows != cols) throw SizeError(string("Matrix is not square, consequently, the trace cannot be calculated"));

	double tr = 0;

	for (int i = 0; i < rows; ++i)
	{
		tr += matrix[i * rows + i];
	}

	return tr;
}

// функция для подсчёта следа матрицы
double Trace(const Matrix& N)
{
	if (N.rows != N.cols) throw SizeError(string("Matrix is not square, consequently, the trace cannot be calculated"));

	Matrix temp(N);
	double tr = temp.Trace();
	return tr;
}

// функция для преобразования матрицы методом Гаусса
Matrix Matrix::Gauss(int flag)
{
	Matrix temp(*this);

	double x;
	int change_sign = 1;

	// сначала нам нужно выбрать строку, элемент A[i,i] должен быть ненулевым

	for (int i = 0; (i < temp.rows && i < temp.cols); i++) {
		//если temp[i,i] == 0 - ищем ненулевой из строк ниже
		if (temp.matrix[i * temp.cols + i] == 0) {
			for (int i1 = i + 1; i1 < temp.rows; i1++) {
				//если есть ненулевой вектор ниже - меняем строки местами
				if (temp.matrix[i1 * temp.cols + i] != 0) {
					change_sign *= (-1);
					for (int j1 = 0; j1 < temp.cols; j1++) {
						x = temp.matrix[i * temp.cols + j1];
						temp.matrix[i * temp.cols + j1] = temp.matrix[i1 * temp.cols + j1];
						temp.matrix[i1 * temp.cols + j1] = x;
					}
					break;
				}
			}
		}
		// теперь для этой строки производим стандартные преобразования Гаусса (вычитаем этроку из остальных)
		if (temp.matrix[i * temp.cols + i] != 0) {
			for (int i1 = 0; i1 < i; i1++) {
				x = temp.matrix[i1 * temp.cols + i] / temp.matrix[i * temp.cols + i];
				for (int j1 = i; j1 < temp.cols; j1++) {
					temp.matrix[i1 * temp.cols + j1] = temp.matrix[i1 * temp.cols + j1] - temp.matrix[i * temp.cols + j1] * x;
				}
			}
			for (int i1 = i + 1; i1 < temp.rows; i1++) {
				x = temp.matrix[i1 * temp.cols + i] / temp.matrix[i * temp.cols + i];
				for (int j1 = i; j1 < temp.cols; j1++) {
					temp.matrix[i1 * temp.cols + j1] = temp.matrix[i1 * temp.cols + j1] - temp.matrix[i * temp.cols + j1] * x;
				}
			}
		}
	}
	if (flag)	// в процессе мы меняем строки местами, следовательно по свойствам детерминанта его знак меняется
		for (int i = 0; i < temp.cols; i++) {
			temp.matrix[(temp.rows - 1) * temp.cols + i] *= change_sign;
		}

	return temp;
}

// метод для подсчёта определителя матрицы
double Matrix::Det()
{
	if (rows != cols) throw SizeError(string("Matrix is not square, consequently, the determinant cannot be calculated"));

	double det = 1;

	Matrix A(this->Gauss(true));

	for (int i = 0; i < this->rows; i++) {
		det *= A.matrix[i * cols + i];
	}
	return det;

}

// функция для подсчёта определителя матрицы
double Det(const Matrix& N)
{
	if (N.rows != N.cols) throw SizeError(string("Matrix is not square, consequently, the determinant cannot be calculated"));

	Matrix temp(N);
	return temp.Det();
}

// метод для скалярного произведения векторов
double Matrix::Scalar(const Matrix& R)
{
	if (  (max(rows, cols) != max(R.rows, R.cols))  ||  (min(rows, cols) != 1)  ||  (min(R.rows, R.cols) != 1)  )\
		throw SizeError(string("Vectors' sizes do not respond the conditions of the task"));

	double sum = 0;
	for (int i = 0; i < rows * cols; ++i) sum += matrix[i] * R.matrix[i];

	return sum;
}

// функция для скалярного произведения векторов
double Scalar(const Matrix& L, const Matrix& R)
{
	if ((max(L.rows, L.cols) != max(R.rows, R.cols)) || (min(L.rows, L.cols) != 1) || (min(R.rows, R.cols) != 1))\
		throw SizeError(string("Vectors' sizes do not respond the conditions of the task"));

	double sum = 0;
	for (int i = 0; i < L.rows * L.cols; ++i) sum += L.matrix[i] * R.matrix[i];
	
	return sum;
}

// функция для вычисления евклидовой нормы вектора = норма Фронебиуса у матриц
double Matrix::EuclidNorm() 
{
	double sum = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			sum = sum + pow(matrix[i * cols + j], 2);
		}
	}
	sum = pow(sum, 0.5);
	return sum;
}

// функция для нахождение евклидово нормы вектора = норма Фронебиуса у матриц
double EuclidNorm(const Matrix& N)
{
	Matrix temp(N);
	return temp.EuclidNorm();
}

// метод для вычисления максимальной нормы вектора
double Matrix::MaxNorm() 
{
	if (min(rows, cols) != 1) throw SizeError(string("Max norm cannot be taken from a non-vector object"));

	double vec_max = -1;
	for (int i = 0; i < rows * cols; i++) 
	{
		vec_max = ( abs(matrix[i]) > vec_max ) ? abs(matrix[i]) : vec_max;
	}
	return vec_max;
}

// функция для вычисления максимальной нормы вектора
double MaxNorm(const Matrix& N) 
{
	if (min(N.rows, N.cols) != 1) throw SizeError(string("Max norm cannot be taken from a non-vector object"));

	double vec_max = -1;
	for (int i = 0; i < N.rows * N.cols; i++)
	{
		vec_max = ( abs(N.matrix[i]) > vec_max ) ? abs(N.matrix[i]) : vec_max;
	}
	return vec_max;
}

//_____________________________ Вспомогательные функции и методы ЛР3 _________________________________________________

// метод для вычисления угла между векторами (в градусах)
double Matrix::Angle(const Matrix& R)
{
	if ((max(rows, cols) != max(R.rows, R.cols)) || (min(rows, cols) != 1) || (min(R.rows, R.cols) != 1))\
		throw SizeError(string("Vectors' sizes do not respond the conditions of the task"));

	Matrix temp(R);

	return 180 * acos( this->Scalar(temp) / (this->EuclidNorm() * temp.EuclidNorm()) ) / PI;
}

// функция для вычисления угла между векторами (в градусах)
double Angle(const Matrix& L, const Matrix& R)
{
	if ((max(L.rows, L.cols) != max(R.rows, R.cols)) || (min(L.rows, L.cols) != 1) || (min(R.rows, R.cols) != 1))\
		throw SizeError(string("Vectors' sizes do not respond the conditions of the task"));

	Matrix tempL(L), tempR(R);

	return 180 * acos(Scalar(tempL, tempR) / (tempL.EuclidNorm() * tempR.EuclidNorm())) / PI;
}

// метод для поиска ранга матрицы
int Matrix::Rank()
{
	Matrix temp = this->Gauss();

	int Ran = 0;
	for (int i = 0; i < temp.rows; i++)
		for (int j = 0; j < temp.cols; j++)
			if (temp.matrix[i * temp.cols + j] != 0) {
				Ran++;
				break;
			}

	return Ran;
}

// функция для поиска ранга матрицы
int Rank(const Matrix& N)
{
	Matrix temp = N;
	return temp.Rank();
}

// метод для нахождения обратной матрицы
Matrix Matrix::Reverse()
{
	if (rows != cols) throw SizeError(string("Matrix is not square => Reverse matrix does not exist"));
	
	//	создаём матрицу для создания обратной (A|E)
	Matrix temp(rows, cols * 2, 0);

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			temp.matrix[i * temp.cols + j] = matrix[i * cols + j];
		}
		temp.matrix[i * temp.cols + rows + i] = 1;
	}

	//	применяем метод Гаусса для приведения всей матрицы к виду (E|A'), A' = A^(-1)
	Matrix temp2 = temp.Gauss();
	double k;
	for (int i = 0; i < temp2.rows; i++) 
	{
		if (temp2.matrix[i * temp2.cols + i] != 0) 
		{
			k = temp2.matrix[i * temp2.cols + i];
			for (int j = 0; j < temp2.cols; j++) 
			{
				temp2.matrix[i * temp2.cols + j] = temp2.matrix[i * temp2.cols + j] / k;
			}
		}
		else throw ZeroDetError(string("The matrix's determinant is 0 => Reverse matrix does not exist"));
	}

	Matrix final(rows, cols, 0);
	for (int i = 0; i < rows; i++) 
	{
		for (int j = 0; j < cols; j++)
		{
			final.matrix[i * final.cols + j] = temp2.matrix[i * temp2.cols + temp2.rows + j];
		}
	}
	
	return final;
}

// функция для нахождения обратной матрицы
Matrix Reverse(const Matrix& N)
{
	try {
		Matrix tmp(N);
		return tmp.Reverse();
	}
	catch (...)
	{
		throw;
	}
}

// метод для нахождения транспонированной матрицы
Matrix Matrix::Transpose()
{
	Matrix temp(cols, rows, 0);

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			temp.matrix[j * temp.cols + i] = matrix[i * cols + j];
		}
	}

	return temp;
}

// функция для нахождения транспонированной матрицы
Matrix Transpose(const Matrix& N)
{
	Matrix temp(N.cols, N.rows, 0);

	for (int i = 0; i < N.rows; ++i)
	{
		for (int j = 0; j < N.cols; ++j)
		{
			temp.matrix[j * temp.cols + i] = N.matrix[i * N.cols + j];
		}
	}

	return temp;
}

//____________ Вспомогательные функции, методы и перегрузки операторов ЛР4 __________________

//	перегрузка оператора вывода в текстовый файл
ofstream& operator <<(ofstream& out, const Matrix& N) 
{
	for (int i = 0; i < N.rows; i++) 
	{
		for (int j = 0; j < N.cols; j++) 
		{
			out << right << setw(12) << setfill(' ') << N.matrix[i * N.cols + j];
		}
		out << endl;
	}
	return out;
}

// перегрузка оператора ввода из текстового файла
ifstream& operator	>>(ifstream& in, Matrix& N)
{
	if (in.fail()) throw InputError(string("Text file with this name does not exist"));
	if (in.peek() == EOF) throw InputError(string("Text file given is empty"));

	//_________ нахождение размера матрицы _____________

	streampos pos = 0;
	in.seekg(0, in.end);
	pos = in.tellg();	// нахождение конца файла
	in.seekg(0, in.beg);

	string line, check;
	stringstream instr;
	int rows = 1, cols = 0, maxcols = 0;
	double x;

	getline(in, line);
	while (line.find(',') != string::npos)	// цикл для замены всех "," на "."
	{
		line.replace(line.find(','), 1, ".");
	}

	instr << line;
	while (!instr.eof())	// цикл для подсчёта столбцов в первой строке
	{
		instr >> x;
		++cols;
	}
	maxcols = cols;

	while (1)	// цикл для подсчёта строк в матрице
	{
		if (in.tellg() == pos) break;

		getline(in, line);
		++rows;
	}

	in.seekg(0, in.beg);
	
	N.rows = rows;
	N.cols = maxcols;
	delete[] N.matrix;
	N.matrix = new double[rows * maxcols];

	//______________ запись матрицы в массив __________________

	getline(in, line);
	while (line.find(',') != string::npos)	// цикл для замены всех "," на "."
	{
		line.replace(line.find(','), 1, ".");
	}

	instr.str(string());
	instr.clear();
	
	for (int i = 0; i < rows; ++i)
	{
		cols = 0;
		instr << line;
		while (!instr.eof())
		{
			instr >> check;
			try 
			{
				x = stof(check);
			}
			catch (invalid_argument)
			{
				throw InputError(string("The text file contains a value different from numbers"));
			}
			catch (out_of_range)
			{
				throw InputError(string("The text file contains a value too great to be read"));
			}
			catch (...) 
			{
				throw;
			}

			// проверка того, что мы не выйдем за пределы выделенной памяти, чтобы компилятор "не ругался"
			if ( (i * maxcols + cols) >= (rows * maxcols) ) break;

			N.matrix[i * maxcols + cols] = x;
			++cols;
		}

		if (cols != maxcols) throw SizeError(string("Matrix in text file has different dimensions from those that are given"));

		getline(in, line);
		while (line.find(',') != string::npos)	// цикл для замены всех "," на "."
		{
			line.replace(line.find(','), 1, ".");
		}

		instr.str(string());
		instr.clear();
	}

	instr.str(string());

	return in;
}

// метод для чтения матрицы из бинарного файла
void Matrix::ReadBin(ifstream& in) 
{
	if (in.fail()) throw InputError(string("Binary file with this name does not exist"));
	if (in.peek() == EOF) throw InputError(string("Binary file given is empty"));

	int sizeMatrix[2];
	double x = 0;
	in.read((char*)&sizeMatrix, sizeof(int) * 2);
	rows = sizeMatrix[0];
	cols = sizeMatrix[1];
	delete[] matrix;
	matrix = new double[rows * cols];

	for (int i = 0; i < rows; i++) 
	{
		for (int j = 0; j < cols; j++) 
		{
			if (in.peek() == EOF) throw SizeError(string("Matrix in binary file has different dimensions from those that are given"));

			in.read((char *)&x, sizeof(double));
			matrix[i * cols + j] = x;
		}
	}
}

// метод для записи матрицы в бинарный файл
void Matrix::WriteBin(ofstream& out) 
{
	int sizeMatrix[2] = { rows, cols };
	double x;
	out.write((char*)&sizeMatrix, sizeof(int) * 2);
	for (int i = 0; i < rows; i++) 
	{
		for (int j = 0; j < cols; j++)
		{
			x = matrix[i * cols + j];
			out.write((char*)&x, sizeof(double));
		}
	}
}

//_______________________ Методы класса PCA для ЛР5 _________________________________________

Matrix PCA::center()	// реализация метода центрирования матрицы
{
	Matrix tmp = matrix;

	double* mean = new double[matrix.cols]{ 0 };	// массив для записи средних для всех столбцов

	for (int c = 0; c < matrix.cols; ++c)
	{
		for (int r = 0; r < matrix.rows; ++r)
		{
			mean[c] += tmp.matrix[r*matrix.cols + c];
		}
		mean[c] = mean[c] / matrix.rows;
	}


	for (int c = 0; c < matrix.cols; ++c)
	{
		for (int r = 0; r < matrix.rows; ++r)
		{
			tmp.matrix[r*matrix.cols + c] -= mean[c];
		}
	}

	return tmp;
}

Matrix PCA::scaling()	// реализация метода шкалирования матрицы
{
	Matrix tmp = matrix;

	double* mean = new double[matrix.cols]{ 0 };	// массив для записи средних для всех столбцов
	double* std = new double[matrix.cols]{ 0 };	// массив для записи стандартных отклонений для всех столбцов


	for (int c = 0; c < matrix.cols; ++c)
	{
		for (int r = 0; r < matrix.rows; ++r)
		{
			mean[c] += tmp.matrix[r * matrix.cols + c];
		}
		mean[c] = mean[c] / matrix.rows;
	}

	for (int c = 0; c < matrix.cols; ++c)
	{
		for (int r = 0; r < matrix.rows; ++r)
		{
			std[c] += (tmp.matrix[r * matrix.cols + c] - mean[c]) * (tmp.matrix[r * matrix.cols + c] - mean[c]);
		}
		std[c] = std::sqrt(std[c] / (matrix.rows - 1));
	}

	for (int c = 0; c < matrix.cols; ++c)
	{
		for (int r = 0; r < matrix.rows; ++r)
		{
			if (std[c] != 0)
				tmp.matrix[r * matrix.cols + c] = (tmp.matrix[r * matrix.cols + c] - mean[c]) / std[c];
		}
	}

	return tmp;
}

std::tuple<Matrix, Matrix, Matrix> PCA::NIPALS(int PC)	// реализация метода для разложения матрицы алгоритмом NIPALS
{

	if(PC < 1 || PC > std::min(matrix.rows, matrix.cols)) throw InputError(string("Wrong input of PC parameter in NIPALS function"));

	double eps = 1e-8;

	PCA _D((*this).center());	// предобработка данных для матрицы образцов 
	PCA D(_D.scaling());	// (число строк = числу образцов, число столбцов = число независимых переменных)

	int Erows = D.matrix.rows, Ecols = D.matrix.cols;
	Matrix E(D.matrix.matrix, Erows, Ecols);	// матрица остатков размера - Erows * Ecols

	double* temp = new double[Erows];	// временный массив для хранения столбцов матрицы E

	Matrix t, t_old;	// t - новая переменная (вектор как линейная комбинация столбцов матрицы D)
	Matrix p, d;
	double* Pmatr = new double[Ecols * PC];	// матрицы чисел, которые мы будем дополнять до нужных нам T и P
	double* Tmatr = new double[Erows * PC];
	int p_counter = 0, t_counter = 0;	// счётчики для запоминания текущей позиции в матрицах T и Р

	for (int h = 0; h < PC; ++h)	// цикл для нахождения T и Р
	{
		for (int k = 0; k < Erows; ++k)
		{
			temp[k] = (E.Transpose()).matrix[h * Erows + k];
		}
		t = Matrix(temp, Erows, 1);	// присваеваем столбец h к переменной t

		do
		{
			p = ((t.Transpose() * E)   *   (1 / (t.Transpose() * t).matrix[0])).Transpose();
			p = p * (1 / p.EuclidNorm());	// размер - Ecols * 1
			t_old = t;

			t = (E * p)   *   (1 / (p.Transpose() * p).matrix[0]);	// размер - Erows * 1
			d = t_old - t;
		} while (d.EuclidNorm() > eps);

		E = E - t * (p.Transpose());

		for (int k = 0; k < Ecols; ++k)
		{
			Pmatr[p_counter] = p.matrix[k];
			++p_counter;
		}

		for (int k = 0; k < Erows; ++k)
		{
			Tmatr[t_counter] = t.matrix[k];
			++t_counter;
		}
	}

	Matrix P(Pmatr, PC, Ecols);
	P = P.Transpose();	// матрица нагрузок размера - Ecols * PC
	Matrix T(Tmatr, PC, Erows);
	T = T.Transpose();	// матрица счётов размера - Erows * PC

	//E = D.matrix - T * P.Transpose();		// формула для матрицы остатков из файла (был предложен на сайте)

	delete[] temp;
	delete[] Pmatr;
	delete[] Tmatr;

	return std::make_tuple(T, P, E);	// D = T * P.Transpose() + E
}

Matrix PCA::leverage(int PC)	// реализация метода для подсчёта размахов матрицы для каждой строки
{
	if (PC < 1 || PC > std::min(matrix.rows, matrix.cols)) throw InputError(string("Wrong input of PC parameter in 'leverages' method"));

	std::tuple<Matrix, Matrix, Matrix> nipals_res = this->NIPALS(PC);

	Matrix T = std::get<0>(nipals_res);
	Matrix t;
	double* leverages = new double[T.rows];
	double* temp = new double[T.cols];

	for (int h = 0; h < T.rows; ++h)
	{
		for (int k = 0; k < T.cols; ++k)
		{
			temp[k] = T.matrix[h * T.cols + k];
		}
		t = Matrix(temp, T.cols, 1);	// h-ая строка матрицы T (h-ый образец) => преобразуем в столбец

		leverages[h] = (t.Transpose() * ((T.Transpose() * T).Reverse()) * t).matrix[0];
	}

	Matrix h(leverages, T.rows, 1);

	delete[] leverages;
	delete[] temp;

	return h;
}

Matrix PCA::deviation(int PC)	// реализация метода для подсчёта отклонений для всех строк матрицы
{
	if (PC < 1 || PC > std::min(matrix.rows, matrix.cols)) throw InputError(string("Wrong input of PC parameter in 'deviation' method"));

	std::tuple<Matrix, Matrix, Matrix> nipals_res = this->NIPALS(PC);

	Matrix E = std::get<2>(nipals_res);

	double* temp = new double[E.rows];

	double sum = 0;		// отклонение для строки матрицы Е - это сумма квадратов остатков в этой строке

	for (int i = 0; i < E.rows; i++) {
		for (int j = 0; j < E.cols; j++) {
			sum += pow(E.matrix[i * E.cols + j], 2);
		}
		temp[i] = sum;
		sum = 0;
	}

	Matrix res(temp, E.rows, 1);

	delete[] temp;

	return res;
}

std::pair<double, double> PCA::dispersion(int PC)	// метод для подсчёта полной и объяснённой дисперсий матрицы
{
	if (PC < 1 || PC > std::min(matrix.rows, matrix.cols)) throw InputError(string("Wrong input of PC parameter in 'dispersion' method"));

	// TRV - полная дисперсия остатков, ERV - объяснённая дисперсия остатков

	Matrix v = this->deviation(PC);	// вектор отклонений

	double v0 = 0;
	int I = matrix.rows;
	int J = matrix.cols;

	for (int i = 0; i < I; ++i)
	{
		v0 += v.matrix[i];
	}
	v0 = v0 / I;

	double TRV = v0 / J;	// полная дисперсия остатков

	double ERV = 0;

	Matrix X = this->scaling();

	for (int i = 0; i < I; ++i)
	{
		for (int j = 0; j < J; ++j) ERV += pow(X.matrix[i * J + j], 2);
	}

	ERV = 1 - I * v0 / ERV;	// объяснённая дисперсия остатков

	return std::make_pair(TRV, ERV);	// сначала полная, затем объяснённая дисперсии остатков
}

//__________________________________ Вспомогательные функции для ЛР6 _______________________________________

std::atomic_flag lock_stdout = ATOMIC_FLAG_INIT;	// атомарный флаг для блокировки вывода сообщений в консоль
void Game(int id)	// реализация функции для ЛР6 для изображения игры на поле (id - номер игрока)
{
	static int flag = 0;	// флаг для отображения конца игры (0 - игра ещё не окончена, 1 - победа первого игрока, 2 - победа второго)
	int curr_pos = 1;	// текущая позиция игрока на поле
	srand(time(nullptr)); // используем текущее время как параметр seed для генератора псевдослучайных чисел
	int dice;	// значение на игральной кости после броска

	while (lock_stdout.test_and_set()) {}	// используются для блокировки вывода сообщений в консоль, чтобы не наслаивались друг на друга
	std::cout << "Player " << id << " starts from position ---> " << curr_pos << endl;
	lock_stdout.clear();

	while (1)
	{

		if (flag != 0)
		{
			while (lock_stdout.test_and_set()) {}
			std::cout << "Player " << id << " loses\n";
			lock_stdout.clear();
			break;
		}

		dice = 1 + std::rand() / (RAND_MAX / 6);
		curr_pos += dice;
		if (curr_pos >= 30) {
			while (lock_stdout.test_and_set()) {}
			flag = id;
			std::cout << "\nNew throw for the " << id << " player:\n\tDice points ---> " << dice << "\n\tCurrent position ---> " << 30 << endl;
			std::cout << "The winner is " << id << " player\n";
			lock_stdout.clear();
			break;
		}

		while (lock_stdout.test_and_set()) {}
		switch (curr_pos)
		{
		case 3:
			std::cout << "\nNew throw for the " << id << " player:\n\tDice points ---> " << dice << "\n\tCurrent position ---> " << curr_pos << endl;
			std::cout << "It was an interaction cell => now the position for player " << id << " is ---> " << curr_pos + 3 << endl;
			curr_pos += 3;
			break;
		case 5:
			std::cout << "\nNew throw for the " << id << " player:\n\tDice points ---> " << dice << "\n\tCurrent position ---> " << curr_pos << endl;
			std::cout << "It was an interaction cell => now the position for player " << id << " is ---> " << curr_pos - 1 << endl;
			curr_pos -= 1;
			break;
		case 8:
			std::cout << "\nNew throw for the " << id << " player:\n\tDice points ---> " << dice << "\n\tCurrent position ---> " << curr_pos << endl;
			std::cout << "It was an interaction cell => now the position for player " << id << " is ---> " << 21 << endl;
			curr_pos = 21;
			break;
		case 9:
			std::cout << "\nNew throw for the " << id << " player:\n\tDice points ---> " << dice << "\n\tCurrent position ---> " << curr_pos << endl;
			std::cout << "It was an interaction cell => now the position for player " << id << " is ---> " << curr_pos - 3 << endl;
			curr_pos -= 3;
			break;
		case 11:
			std::cout << "\nNew throw for the " << id << " player:\n\tDice points ---> " << dice << "\n\tCurrent position ---> " << curr_pos << endl;
			std::cout << "It was an interaction cell => now the position for player " << id << " is ---> " << curr_pos + 3 << endl;
			curr_pos += 3;
			break;
		case 13:
			std::cout << "\nNew throw for the " << id << " player:\n\tDice points ---> " << dice << "\n\tCurrent position ---> " << curr_pos << endl;
			std::cout << "It was an interaction cell => now the position for player " << id << " is ---> " << curr_pos + 1 << endl;
			curr_pos += 1;		
			break;
		case 15:
			std::cout << "\nNew throw for the " << id << " player:\n\tDice points ---> " << dice << "\n\tCurrent position ---> " << curr_pos << endl;
			std::cout << "It was an interaction cell => now the position for player " << id << " is ---> " << curr_pos - 3 << endl;
			curr_pos -= 3;	
			break;
		case 16:
			std::cout << "\nNew throw for the " << id << " player:\n\tDice points ---> " << dice << "\n\tCurrent position ---> " << curr_pos << endl;
			std::cout << "It was an interaction cell => now the position for player " << id << " is ---> " << 7 << endl;
			curr_pos = 7;
			break;
		case 19:
			std::cout << "\nNew throw for the " << id << " player:\n\tDice points ---> " << dice << "\n\tCurrent position ---> " << curr_pos << endl;
			std::cout << "It was an interaction cell => now the position for player " << id << " is ---> " << curr_pos + 1 << endl;
			curr_pos += 1;	
			break;
		case 23:
			std::cout << "\nNew throw for the " << id << " player:\n\tDice points ---> " << dice << "\n\tCurrent position ---> " << curr_pos << endl;
			std::cout << "It was an interaction cell => now the position for player " << id << " is ---> " << curr_pos - 2 << endl;
			curr_pos -= 2;	
			break;
		case 25:
			std::cout << "\nNew throw for the " << id << " player:\n\tDice points ---> " << dice << "\n\tCurrent position ---> " << curr_pos << endl;
			std::cout << "It was an interaction cell => now the position for player " << id << " is ---> " << 1 << endl;
			curr_pos = 1;
			break;
		case 27:
			std::cout << "\nNew throw for the " << id << " player:\n\tDice points ---> " << dice << "\n\tCurrent position ---> " << curr_pos << endl;
			std::cout << "It was an interaction cell => now the position for player " << id << " is ---> " << curr_pos + 1 << endl;
			curr_pos += 1;
			break;
		case 29:
			std::cout << "\nNew throw for the " << id << " player:\n\tDice points ---> " << dice << "\n\tCurrent position ---> " << curr_pos << endl;
			std::cout << "It was an interaction cell => now the position for player " << id << " is ---> " << curr_pos - 3 << endl;
			curr_pos -= 3;
			break;
		default:
			std::cout << "\nNew throw for the " << id << " player:\n\tDice points ---> " << dice << "\n\tCurrent position ---> " << curr_pos << endl;
			break;
		}
		lock_stdout.clear();
	}
}