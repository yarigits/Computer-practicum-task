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