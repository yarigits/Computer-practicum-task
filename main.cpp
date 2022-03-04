#include "header_matrix.h"

using namespace std;

/* Чтобы получить вектор, создать объект класса Matrix с одним измерением = 1 */

int main()
{
	try
	{
		// создадим матрицу, запишем её в файл и сохраним во вторую
		Matrix l(1, 1, 0);
		cout << "Create matrix to put into file:" << endl;
		Symmetrical r(3);

		ofstream file_out("check.txt", ios_base::out);
		file_out << r;
		cout << r << endl;
		file_out.close();

		ifstream file_in("check.txt", ios_base::in);
		file_in >> l;
		file_in.close();
		cout << "MAtrix read from file:" << endl;
		cout << l << endl;

		// Создадим матрицы разных типов
		Unit_Matrix one(4);
		cout << one << endl;

		Upper_triangular uptr(4);
		cout << uptr << endl;

		Diagonal diag(4);
		cout << diag << endl;

		Symmetrical sym(5);
		cout << sym << endl;

		// Проверка арифметических операций
		cout << "Unit Matrix and Upper triangular:\n" << one * uptr << endl;
		cout << "Diagonal and Upper triangular:\n" << diag * uptr << endl;
		cout << "Diagonal Matrix and number:\n" << diag * 5 << endl;
		//cout << "Symmetrical and diagonal:\n" << diag * sym << endl;

		// Определитель
		cout << "Determinant of upper triangular: " << Det(uptr) << endl;
		cout << "Determinant of symmetrical: " << sym.Det() << endl;

		//норма вектора
		Matrix vec(5, 1);
		cout << vec << endl;
		cout << "Vector Norm: " << vec.EuclidNorm() << endl;

		// транспонирование матрицы
		cout << "Transposed upper triangular matrix:\n" << uptr.Transpose() << endl;

		// Умножение матрицы на обратную
		cout << "Reverse matrix of upper triangular:\n" << uptr.Reverse() << endl;
		cout << "Upper triangular * Reverse matrix:\n" << uptr.Reverse() * uptr << endl;

		// ранг матрицы
		double vecс[6] = { 1 ,2,3,4,5,6 };
		Matrix MM(vecс, 2, 3);
		
		cout << MM << endl;
		cout << MM.Transpose() << endl;
		cout << "Rank of new matrix: " << MM.Rank() << endl;

	}
	catch (const SizeError& Err) 
	{
		cout << Err.size_err << endl;
	}
	catch (const InputError& Err)
	{
		cout << Err.input_err << endl;
	}
	catch (const ZeroDetError& Err)
	{
		cout << Err.det_err << endl;
	}
	catch (...)
	{
		cout << "Unknown error emerged" << endl;
	}

	return 0;
}