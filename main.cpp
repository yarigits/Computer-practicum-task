#include "header_matrix.h"

using namespace std;

/* ����� �������� ������, ������� ������ ������ Matrix � ����� ���������� = 1 */

int main()
{
	try
	{
		//___________________ �������� ��5 __________________________________________________________________________________
		
		// �������� ������������ ��� ������� ����� initializer_list
		Matrix in_list({ 1,3,3,4,8,0,1,3,2 }, 3, 3);	// ������� X
		cout << "Matrix X:\n" << in_list << endl;

		// �������� ������� ������ PCA
		PCA check(in_list);
		cout << "Matrix X after scaling (now it is matrix D):\n" << check.scaling() << endl;

		auto tup = check.NIPALS(3);
		cout << "T:\n" << get<0>(tup) << endl;
		cout << "P:\n" << get<1>(tup) << endl;
		cout << "E:\n" << get<2>(tup) << endl;

		// ������ �����, ��� ����� ������������� T * P' + E = D, ��� D - ���������������� ������� X
		cout << "D = T * P' + E:\n" << get<0>(tup) * get<1>(tup).Transpose() + get<2>(tup) << endl;	



		// �������� ������ ������� ������ PCA �� ��������������� ������� ("���� � ������")
		cout << "\n\nPeople and countires data:\n" << endl;
		Matrix DATA;
		ifstream file_in("people and countries.txt", ios_base::in);
		file_in >> DATA;
		file_in.close();
		cout << "Matrix read from file:" << endl;
		cout << DATA << endl;

		cout << "\nCentering and scaling of the matrix:\n";		// ������������� � ������������ �������
		PCA __df(DATA);
		Matrix DATA_centered(__df.center());
		PCA _df(DATA_centered);
		Matrix DATA_scaled(_df.scaling());
		cout << DATA_scaled << endl;

		// �����!!! ��� ������� ���� �������������� ��������� � ���������������� ������!!!

		cout << "\nUsing NIPALS algorithm to create score and loadings matrices:\n";	// ���������� ������� ���������� NIPALS
		PCA df(DATA);
		auto tupp = df.NIPALS(12);
		cout << "T:\n" << get<0>(tupp) << endl;
		cout << "P:\n" << get<1>(tupp) << endl;
		cout << "E:\n" << get<2>(tupp) << endl;

		cout << "D = T * P' + E:\n" << get<0>(tupp) * get<1>(tupp).Transpose() + get<2>(tupp) << endl;

		cout << "\nLeverages for this matrix:\n";		// ������� �������� ��� ������ �������
		cout << df.leverage(12) << endl;

		cout << "\nDeviations for this matrix:\n";		// ������� ���������� ��� ������ �������
		cout << df.deviation(12) << endl;

		cout << "\nDispersions for this matrix:\n";	// ������� ������ � ���������� ��������� �������� ��� �������
		auto df_dispersions = df.dispersion(12);
		cout << "TRV = " << df_dispersions.first << endl;
		cout << "ERV = " << df_dispersions.second << endl;


		//_________________________ �������� ��6 (������� 13) _______________________________________________________________________________

		/*
		
		������������ ������ thread, mutex (��� ����� ���������� ��������), lock_guard/unique_lock, condition_variable, atomic, 
		future � async ��� ������� ������� (� ����������� �� ������� �������).
		
		������� 13: ���� ���������� ���� � ����� ��������(������) � ������������� �������� � �����.
		������ ������� ����� � ����� �� ������ ����. �� ���� ���� ������������� ������: ������� ��� +- [�� 1 �� 3], 
		������������ �� ������ � ������� n. ���������� ����� ���� �����. 
		
		*/

		cout << "\nThe game task:\n\n";
		thread first_player(Game, 1);
		thread second_player(Game, 2);
		first_player.join();
		second_player.join();
		


		//______________________________________ ���� ������� ��� �� �1-4 (�� ����� � �� � 5) ___________________________________________________


		//// �������� �������, ������� � � ���� � �������� �� ������
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

		//// �������� ������� ������ �����
		//Unit_Matrix one(4);
		//cout << one << endl;

		//Upper_triangular uptr(4);
		//cout << uptr << endl;

		//Diagonal diag(4);
		//cout << diag << endl;

		//Symmetrical sym(5);
		//cout << sym << endl;

		//// �������� �������������� ��������
		//cout << "Unit Matrix and Upper triangular:\n" << one * uptr << endl;
		//cout << "Diagonal and Upper triangular:\n" << diag * uptr << endl;
		//cout << "Diagonal Matrix and number:\n" << diag * 5 << endl;
		////cout << "Symmetrical and diagonal:\n" << diag * sym << endl;

		//// ������������
		//cout << "Determinant of upper triangular: " << Det(uptr) << endl;
		//cout << "Determinant of symmetrical: " << sym.Det() << endl;

		////����� �������
		//Matrix vec(5, 1);
		//cout << vec << endl;
		//cout << "Vector Norm: " << vec.EuclidNorm() << endl;

		//// ���������������� �������
		//cout << "Transposed upper triangular matrix:\n" << uptr.Transpose() << endl;

		//// ��������� ������� �� ��������
		//cout << "Reverse matrix of upper triangular:\n" << uptr.Reverse() << endl;
		//cout << "Upper triangular * Reverse matrix:\n" << uptr.Reverse() * uptr << endl;

		//// ���� �������
		//double vec�[6] = { 1 ,2,3,4,5,6 };
		//Matrix MM(vec�, 2, 3);
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