#include "header_matrix.h"

using namespace std;

/* Чтобы получить вектор, создать объект класса Matrix с одним измерением = 1 */

int main()
{
	try
	{
		//___________________ Проверка ЛР5 __________________________________________________________________________________
		
		// проверка конструктора для матрицы через initializer_list
		Matrix in_list({ 1,3,3,4,8,0,1,3,2 }, 3, 3);	// матрица X
		cout << "Matrix X:\n" << in_list << endl;

		// проверка функций класса PCA
		PCA check(in_list);
		cout << "Matrix X after scaling (now it is matrix D):\n" << check.scaling() << endl;

		auto tup = check.NIPALS(3);
		cout << "T:\n" << get<0>(tup) << endl;
		cout << "P:\n" << get<1>(tup) << endl;
		cout << "E:\n" << get<2>(tup) << endl;

		// отсюда видно, что после предобработки T * P' + E = D, где D - предобработанная матрица X
		cout << "D = T * P' + E:\n" << get<0>(tup) * get<1>(tup).Transpose() + get<2>(tup) << endl;	



		// проверка работы функций класса PCA на предоставленной выборке ("Люди и страны")
		cout << "\n\nPeople and countires data:\n" << endl;
		Matrix DATA;
		ifstream file_in("people and countries.txt", ios_base::in);
		file_in >> DATA;
		file_in.close();
		cout << "Matrix read from file:" << endl;
		cout << DATA << endl;

		cout << "\nCentering and scaling of the matrix:\n";		// центрирование и шкалирование матрицы
		PCA __df(DATA);
		Matrix DATA_centered(__df.center());
		PCA _df(DATA_centered);
		Matrix DATA_scaled(_df.scaling());
		cout << DATA_scaled << endl;

		// ВАЖНО!!! Все функции ниже самостоятельно шкалируют и предобрабатывают данные!!!

		cout << "\nUsing NIPALS algorithm to create score and loadings matrices:\n";	// разложение матрицы алгоритмом NIPALS
		PCA df(DATA);
		auto tupp = df.NIPALS(12);
		cout << "T:\n" << get<0>(tupp) << endl;
		cout << "P:\n" << get<1>(tupp) << endl;
		cout << "E:\n" << get<2>(tupp) << endl;

		cout << "D = T * P' + E:\n" << get<0>(tupp) * get<1>(tupp).Transpose() + get<2>(tupp) << endl;

		cout << "\nLeverages for this matrix:\n";		// подсчёт размахов для данной матрицы
		cout << df.leverage(12) << endl;

		cout << "\nDeviations for this matrix:\n";		// подсчёт отклонений для данной матрицы
		cout << df.deviation(12) << endl;

		cout << "\nDispersions for this matrix:\n";	// подсчёт полной и объяснённой дисперсий остатков для матрицы
		auto df_dispersions = df.dispersion(12);
		cout << "TRV = " << df_dispersions.first << endl;
		cout << "ERV = " << df_dispersions.second << endl;


		//_________________________ Проверка ЛР6 (вариант 13) _______________________________________________________________________________

		/*
		
		Использовать классы thread, mutex (или более подходящий подкласс), lock_guard/unique_lock, condition_variable, atomic, 
		future и async при решении заданий (в зависимости от условий задания).
		
		Вариант 13: Дана настольная игра с двумя игроками(потоки) с шестигранными кубиками и полем.
		Игроки бросают кубик и ходят по общему полю. На поле есть интерактивные клетки: сделать шаг +- [от 1 до 3], 
		переместится на клетку с номером n. Победитель пишет свой номер. 
		
		*/

		cout << "\nThe game task:\n\n";
		thread first_player(Game, 1);
		thread second_player(Game, 2);
		first_player.join();
		second_player.join();
		


		//______________________________________ НИЖЕ ПРИМЕРЫ ДЛЯ ЛР №1-4 (не нужны в ЛР № 5) ___________________________________________________


		//// создадим матрицу, запишем её в файл и сохраним во вторую
		//Matrix l(1, 1, 0);
		//cout << "Create matrix to put into file:" << endl;
		//Symmetrical r(3);

		//ofstream file_out("check.txt", ios_base::out);
		//file_out << r;
		//cout << r << endl;
		//file_out.close();

		//ifstream file_in("check.txt", ios_base::in);
		//file_in >> l;
		//file_in.close();
		//cout << "MAtrix read from file:" << endl;
		//cout << l << endl;

		//// Создадим матрицы разных типов
		//Unit_Matrix one(4);
		//cout << one << endl;

		//Upper_triangular uptr(4);
		//cout << uptr << endl;

		//Diagonal diag(4);
		//cout << diag << endl;

		//Symmetrical sym(5);
		//cout << sym << endl;

		//// Проверка арифметических операций
		//cout << "Unit Matrix and Upper triangular:\n" << one * uptr << endl;
		//cout << "Diagonal and Upper triangular:\n" << diag * uptr << endl;
		//cout << "Diagonal Matrix and number:\n" << diag * 5 << endl;
		////cout << "Symmetrical and diagonal:\n" << diag * sym << endl;

		//// Определитель
		//cout << "Determinant of upper triangular: " << Det(uptr) << endl;
		//cout << "Determinant of symmetrical: " << sym.Det() << endl;

		////норма вектора
		//Matrix vec(5, 1);
		//cout << vec << endl;
		//cout << "Vector Norm: " << vec.EuclidNorm() << endl;

		//// транспонирование матрицы
		//cout << "Transposed upper triangular matrix:\n" << uptr.Transpose() << endl;

		//// Умножение матрицы на обратную
		//cout << "Reverse matrix of upper triangular:\n" << uptr.Reverse() << endl;
		//cout << "Upper triangular * Reverse matrix:\n" << uptr.Reverse() * uptr << endl;

		//// ранг матрицы
		//double vecс[6] = { 1 ,2,3,4,5,6 };
		//Matrix MM(vecс, 2, 3);
		//
		//cout << MM << endl;
		//cout << MM.Transpose() << endl;
		//cout << "Rank of new matrix: " << MM.Rank() << endl;

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