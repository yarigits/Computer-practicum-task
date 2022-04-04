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

//______________________ ������� ����� ___________________________________________

class Matrix	// ����� ��� ������� ������ � �������� ������ �����������
{
	int rows, cols;	// ����� ����� � ��������

protected:
	double* matrix;		// ������������ ������, ���������� �������� �������/�������

public:
	Matrix();	// ����������� �� ���������
	Matrix(int r, int c, int flag = 1);		// ����������� ��� ������� ���������� �������/������� 
	Matrix(double* arr, int r, int c);	// ����������� ��� ������������� ������� ���������� � ����������� ��������

	Matrix(std::initializer_list<double> list, int r, int c);	// ����������� ��� ��5

	/* flag �������� �� ������ ��� �������������� ������������� ��������� ������� - ����� ��� ������������ ������ ��� 
	��� ������������� �������� �������� �������. �� ��������� = 1 - ������������� ������, �� ���� ����� ������� */

	~Matrix();	// ����������
	Matrix(const Matrix& M);	// ����������� �����������
	void operator =(const Matrix& M);	// ���������� ��������� ������������

	//___________ ���������� ���������� � ���������� ������� � ������� ��� ��1 ___________

	Matrix operator +(const Matrix& R);
	Matrix operator -(const Matrix& R);
	Matrix operator *(double num);	// ���������� �������� ��������� ������� �� ����� ������
	friend Matrix operator *(double num, const Matrix& L);	// ���������� �������� ��������� ������� �� ����� �����
	Matrix operator *(const Matrix& R);
	Matrix Adamar(const Matrix& R);	// ������������ ������� ��� ������
	friend Matrix Adamar(const Matrix& L, const Matrix& R);	// ������������ ������� � ����� �����������
	friend ostream& operator <<(ostream& out, const Matrix& N);	// ���������� ��������� ������ � �������� �����

	//____________ ���������� ������� � ������� ��� ��2 _______________________________

	double Trace();	// ����� ��� �������� ����� ������� (������� ������ ���� ����������)
	friend double Trace(const Matrix& N);	// ������� ��� �������� �����
	double Det();	// ����� ��� �������� ������������ ������� (������� ������ ���� ����������)
	friend double Det(const Matrix& N);	// ������� ��� �������� ������������
	Matrix Gauss(int flag = 0);	// ������� ��� �������������� ������� ������� ������
	double Scalar(const Matrix& R);	// ����� ��� ���������� ������������ ��������
	friend double Scalar(const Matrix& L, const Matrix& R);	// ������� ��� ���������� ������������ ��������
	double EuclidNorm();	// ����� ��� ���������� ���������� �����
	friend double EuclidNorm(const Matrix& N);	// ������� ��� ���������� ���������� ����� �������
	double MaxNorm();	// ����� ��� ���������� ������������ ����� �������
	friend double MaxNorm(const Matrix& N);	// ������� ��� ���������� ������������ ����� ��������

	/* ����� ���������� ��� ������� ����������� ��� ��, ��� ��������� ����� ������� - ������� EuclidNorm */

	//___________ ���������� ������� � ������� ��� ��3 _______________________________

	double Angle(const Matrix& R);	// ����� ��� ������ ���� ����� ��������� (� ��������)
	friend double Angle(const Matrix& L, const Matrix& R);	// ������� ��� ������ ���� ����� ���������
	int Rank();	//  ����� ��� ������ ����� �������
	friend int Rank(const Matrix& N);	// ������� ��� ����� ����� �������
	Matrix Reverse();	// ����� ��� ���������� �������� �������
	friend Matrix Reverse(const Matrix& N);	// ������� ��� ���������� �������� �������
	Matrix Transpose();	// ����� ��� ���������� ����������������� ������
	friend Matrix Transpose(const Matrix& N);	// ������� ��� ���������� ����������������� ������

	//_______  ���������� ���������� � ���������� ������� � ������� ��� ��4  _________

	friend ofstream& operator <<(ofstream& out, const Matrix& N);	// ���������� ��������� ������ � ��������� ����
	friend ifstream& operator >>(ifstream& in, Matrix& N);	// ���������� ��������� ����� �� ���������� �����
	void ReadBin(ifstream& in);	// ����� ��� ������ �� ��������� �����
	void WriteBin(ofstream& out);	// ����� ��� ������ � �������� ����

	//___________ ���������� ��� ���������� ��5 ______________________________________

	friend class PCA;	// ��� ������� � ����� ������ Matrix
};

//____________________ ���������� ������ ________________________________________

class Unit_Matrix : public Matrix	// ��������� ������� (����������)
{
public:
	Unit_Matrix(int d = 1);	
};

class Diagonal : public Matrix	// ������������ ������� (����������)
{
public:
	Diagonal(int d = 1);		// ����������� �����������
	Diagonal(double* arr, int d = 1);	// ����������� ��� ������������� ������� ���������� � ����������� ��������

	/* ��� ���� ���������� ������ ������ ���� ������� dxd, �� ���� ������ ����� ��������� ���������� � �������. 
	�� ����� �������, ��� ������ ������ ���� ��������� ������� - �� ������ ������ ����� �����-�� �����,
	� �� ���� ��������� - ���� */
};

class Upper_triangular : public Matrix	// ����������������� ������� (����������)
{
public:
	Upper_triangular(int d = 1);
	Upper_triangular(double* arr, int d = 1);
};

class Lower_triangular : public Matrix	// ���������������� ������� (����������)
{
public:
	Lower_triangular(int d = 1);
	Lower_triangular(double* arr, int d = 1);
};

class Symmetrical : public Matrix	// ������������ ������� (����������)
{
public:
	Symmetrical(int d = 1);
	Symmetrical(double* arr, int d = 1);
};

//_____________________ �������������� ������ ______________________________________________________

class PCA	// ����� � ��5 ��� ������������ ������� ��������� ������� ������
{
public:
	Matrix matrix;	// ���� ��� �������� ������ �������

	PCA(Matrix mat) : matrix(mat) {}	// �����������

	// ������ ��� ������������� ������
	Matrix center();	// �������������
	Matrix scaling();	// ������������

	std::tuple<Matrix, Matrix, Matrix> NIPALS(int PC);	// ����� ��� ���������� ������� ���������� NIPALS
	Matrix leverage(int PC);	// ����� ��� �������� �������� ��� ���� ����� �������
	Matrix deviation(int PC);	// ����� ��� �������� ���������� ��� ���� ����� �������
	std::pair<double, double> dispersion(int PC);	// ����� ��� �������� ������ � ���������� ��������� �������
};

//_____________________ ��������������� ������� ______________________________________________________

int MaxLenElem(double* arr, int size);	// ������� ��� ������ ������������ ����� �������� ������� (���������� ���� � �����)
void ValueError(string& s);		// ������� ��� �������� ������������ �������� ��������
void Game(int id);	// ������� ��� ��6 ��� ����������� ���� �� ���� (id - ����� ������)

//_____________________ ������ ��� ������ ���������� _________________________________________

class SizeError	// ��� �������� ������������� �� ������� ������ ��������
{
public:
	string size_err;
	SizeError(string e) : size_err(e) {};
};

class InputError	// ��� �������� ������������ �������� ������/������������ ���������� ��� ��������
{
public:
	string input_err;
	InputError(string e) : input_err(e) {};
};

class ZeroDetError	// ��� �������� ������������� �������
{
public:
	string det_err;
	ZeroDetError(string e) : det_err(e) {};
};