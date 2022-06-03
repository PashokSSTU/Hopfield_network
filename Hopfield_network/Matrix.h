#pragma once
#include <vector>
#include <initializer_list>
#include <iostream>
#include <cmath>

#define ERROR_DIVISION_BY_ZERO "Error! Division by zero exception!"
#define ERROR_OF_ADDING "Error! The dimensions of the matrices are not respected when adding!"
#define ERROR_OF_SUBSTRACTING "Error! The dimensions of the matrices are not respected when substracting!"
#define ERROR_OF_MULTIPLYING "Error! Matrix sizes not respected when multiplying!"
#define ERROR_OF_CALCULATING_DETERMINANT "Determinant calculation error! This matrix is not square!"
//"Inverse matrix calculation error! For this matrix, it does not exist!"
#define ERROR_OF_CONVERTING_TO_IDENTITY_MATRIX "Error! This matrix cannot be converted to the identity matrix, since it is not square!"
#define ERROR_OF_CREATING_IDENTITY_MATRIX "Error! You cannot create an identity matrix of this size because the matrix must be square!"

struct Matrix_Size;
class Matrix;

bool operator==(const Matrix_Size size1, const Matrix_Size size2);
bool operator!=(const Matrix_Size size1, const Matrix_Size size2);
Matrix operator+(const Matrix& obj1, const Matrix& obj2);
Matrix operator-(const Matrix& obj1, const Matrix& obj2);
Matrix operator*(const Matrix& obj1, const Matrix& obj2);
Matrix operator*(double number, const Matrix& obj);
Matrix operator/(const Matrix& obj, double number);
std::ostream& operator<<(std::ostream& out, const Matrix& obj);
double multipy_of_vectors(int row, int col, const Matrix& obj1, const Matrix& obj2);


double det(const Matrix& obj);
Matrix t(const Matrix& obj);
int rank(const Matrix& obj);
Matrix& adj(const Matrix& obj);	
Matrix& inv(const Matrix& obj);


struct Matrix_Size
{
	unsigned int rows;
	unsigned int columns;

	friend bool operator==(const Matrix_Size size1, const Matrix_Size size2);
	friend bool operator!=(const Matrix_Size size1, const Matrix_Size size2);
};

typedef Matrix_Size matrix_size_t;

class Matrix
{
public:
	
	Matrix(unsigned int rows = 3, unsigned int columns = 3) : size({ rows, columns })
	{
		matrix.resize(rows);

		for (int j = 0; j < rows; j++)
		{
			matrix[j].resize(columns);
		}
	}

	Matrix(const Matrix& _matrix)
	{
		if (this->size != _matrix.size)
		{
			this->size = _matrix.size;

			matrix.resize(_matrix.size.rows);

			for (int i = 0; i < _matrix.size.rows; i++)
			{
				matrix[i].resize(_matrix.size.columns);
			}

			for (int i = 0; i < size.rows; i++)
			{
				for (int j = 0; j < size.columns; j++)
				{
					matrix[i][j] = _matrix.matrix[i][j];
				}
			}
		}
		else
		{
			for (int i = 0; i < size.rows; i++)
			{
				for (int j = 0; j < size.columns; j++)
				{
					matrix[i][j] = _matrix.matrix[i][j];
				}
			}
		}
	}

	Matrix(const std::initializer_list<std::initializer_list<double>>& list) : size({ list.size(), 0 })
	{
		for (auto& x : list)
			if (x.size() > size.columns)
				size.columns = x.size();
		
		matrix.resize(size.rows);
		for (int i = 0; i < size.rows; i++)
		{
			matrix[i].resize(size.columns);
		}

		auto it = list.begin();
		for (int i = 0; i < size.rows; i++, it++)
		{
			std::copy(it->begin(), it->end(), matrix[i].begin());
		}
	}

	~Matrix()
	{
	}

	void resize(matrix_size_t size);
	void resize(unsigned int rows, unsigned int columns);

	double& operator()(int i, int j);
	Matrix& operator=(const Matrix& obj);
	Matrix& operator=(std::initializer_list<std::initializer_list<double>> &l);
	Matrix operator+() const;
	Matrix operator-() const;

	bool is_square() const;
	matrix_size_t get_size() const;
	double get_elem(int row, int col) const;
	void set_elem(double data, int row, int col);

	friend Matrix operator+(const Matrix& obj1, const Matrix& obj2);
	friend Matrix operator-(const Matrix& obj1, const Matrix& obj2);
	friend Matrix operator*(const Matrix& obj1, const Matrix& obj2);
	friend Matrix operator*(double number, const Matrix& obj);
	friend Matrix operator/(const Matrix& obj, double number);
	friend double det(const Matrix& obj);

	friend std::ostream& operator<<(std::ostream& out ,const Matrix& obj);
	friend double multipy_of_vectors(int row, int col, const Matrix& obj1, const Matrix& obj2);

	static Matrix Zeros(int rows, int columns);
	static Matrix Identity(int rows, int columns);

	static struct Convert
	{
		static Matrix ToZeros(const Matrix& obj);
		static Matrix ToIdentity(const Matrix& obj);
	};

private:
	matrix_size_t size;
	std::vector<std::vector<double>> matrix;
};