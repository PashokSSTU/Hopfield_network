#pragma once
#include <iostream>
#include "Matrix.h"


void Matrix::resize(matrix_size_t size)
{
	this->size = size;
	matrix.resize(size.rows);
	for (int i = 0; i < size.rows; i++)
	{
		matrix[i].resize(size.columns);
	}
}

void Matrix::resize(unsigned int rows, unsigned int columns)
{
	this->size = { rows, columns };
	matrix.resize(rows);
	for (int i = 0; i < rows; i++)
	{
		matrix[i].resize(columns);
	}
}

bool Matrix::is_square() const
{
	return (size.rows == size.columns);
}

matrix_size_t Matrix::get_size() const
{
	return size;
}

double Matrix::get_elem(int row, int col) const
{
	return matrix[row - 1][col - 1];
}

void Matrix::set_elem(double data, int row, int col)
{
	this->matrix[row - 1][col - 1] = data;
}

bool operator==(const Matrix_Size size1, const Matrix_Size size2)
{
	return (size1.rows == size2.rows && size1.columns == size2.columns);
}

bool operator!=(const Matrix_Size size1, const Matrix_Size size2)
{
	return !(size1.rows == size2.rows && size1.columns == size2.columns);
}

std::ostream& operator<<(std::ostream& out, const Matrix& obj)
{
	for (int i = 0; i < obj.size.rows; i++)
	{
		for (int j = 0; j < obj.size.columns; j++)
		{
			out << obj.matrix[i][j] << "   ";
		}
		out << std::endl;
	}

	return out;
}

double& Matrix::operator()(int i, int j)
{
	return matrix[i - 1][j - 1];
}

Matrix& Matrix::operator=(const Matrix& obj) 
{
	if (this == &obj)
	{
		return *this;
	}

	if (!(size == obj.size))
	{
		size = obj.size;

		matrix.resize(size.rows);
		for (int i = 0; i < size.rows; i++)
		{
			matrix[i].resize(size.columns);
		}
	}

	for (int i = 0; i < size.rows; i++)
	{
		for (int j = 0; j < size.columns; j++)
		{
			matrix[i][j] = obj.matrix[i][j];
		}
	}

	return *this;
}

Matrix& Matrix::operator=(std::initializer_list<std::initializer_list<double>>& list)
{
	size.rows = list.size();
	size.columns = 0;

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

	return *this;
}

bool operator==(const Matrix& obj1, const Matrix& obj2)
{
	if (obj1.get_size() != obj2.get_size())
	{
		return false;
	}

	bool flag_equals = true;
	for (int i = 1; i <= obj1.get_size().rows; i++)
	{
		for (int j = 1; j <= obj1.get_size().columns; j++)
		{
			if(obj1.get_elem(i, j) != obj2.get_elem(i, j))
			{
				flag_equals = false;
			}
		}
	}

	return flag_equals;
}

bool operator!=(const Matrix& obj1, const Matrix& obj2)
{
	return !(operator==(obj1, obj2));
}

Matrix Matrix::operator+() const
{
	return *this;
}

Matrix Matrix::operator-() const
{
	Matrix result;
	result.resize(size);

	for (int i = 0; i < size.rows; i++)
	{
		for (int j = 0; j < size.columns; j++)
		{
			result.matrix[i][j] = -1 * matrix[i][j];
		}
	}

	return result;
}


void Matrix::operator+=(const Matrix& obj)
{
	if (this->get_size() != obj.get_size())
	{
		throw ERROR_OF_ADDING;
	}

	for (int i = 1; i <= obj.get_size().rows; i++)
	{
		for (int j = 1; j <= obj.get_size().columns; j++)
		{
			this->set_elem(this->get_elem(i, j) + obj.get_elem(i, j), i, j);
		}
	}
}

void Matrix::operator-=(const Matrix& obj)
{
	if (this->get_size() != obj.get_size())
	{
		throw ERROR_OF_SUBSTRACTING;
	}

	for (int i = 1; i <= obj.get_size().rows; i++)
	{
		for (int j = 1; j <= obj.get_size().columns; j++)
		{
			this->set_elem(this->get_elem(i, j) - obj.get_elem(i, j), i, j);
		}
	}
}

void Matrix::operator*=(const Matrix& obj)
{
	if (this->size.columns != obj.size.rows)
	{
		throw ERROR_OF_MULTIPLYING;
	}
	
	Matrix tmp = (*this);
	this->resize(this->size.rows, obj.size.columns);

	for (int i = 0; i < this->size.rows; i++)
	{
		for (int j = 0; j < this->size.columns; j++)
		{
			this->matrix[i][j] = multipy_of_vectors(i, j, tmp, obj);
		}
	}
}

void Matrix::operator*=(const double number)
{
	for (int i = 1; i <= this->get_size().rows; i++)
	{
		for (int j = 1; j <= this->get_size().columns; j++)
		{
			this->set_elem(this->get_elem(i, j) * number, i, j);
		}
	}
}

void Matrix::operator/=(const double number)
{
	for (int i = 1; i <= this->get_size().rows; i++)
	{
		for (int j = 1; j <= this->get_size().columns; j++)
		{
			this->set_elem(this->get_elem(i, j) / number, i, j);
		}
	}
}

Matrix operator+(const Matrix& obj1, const Matrix& obj2)
{
	Matrix result;

	if (obj1.size != obj2.size)
	{
		throw ERROR_OF_ADDING;
	}

	result.size = obj1.size;
	result.resize(result.size);

	for (int i = 0; i < result.size.rows; i++)
	{
		for (int j = 0; j < result.size.columns; j++)
		{
			result.matrix[i][j] = obj1.matrix[i][j] + obj2.matrix[i][j];
		}
	}

	return result;
}

Matrix operator*(double number, const Matrix& obj)
{
	Matrix result = obj;

	for (int i = 0; i < result.size.rows; i++)
	{
		for (int j = 0; j < result.size.columns; j++)
		{
			result.matrix[i][j] *= number;
		}
	}

	return result;
}

Matrix operator/(const Matrix& obj, double number)
{
	if (number == 0)
		throw ERROR_DIVISION_BY_ZERO;

	Matrix result = obj;

	for (int i = 0; i < result.size.rows; i++)
	{
		for (int j = 0; j < result.size.columns; j++)
		{
			result.matrix[i][j] /= number;
		}
	}

	return result;
}

Matrix operator-(const Matrix& obj1, const Matrix& obj2)
{
	Matrix result;

	if (obj1.size != obj2.size)
	{
		throw ERROR_OF_SUBSTRACTING;
	}

	result.size = obj1.size;
	result.resize(result.size);

	for (int i = 0; i < result.size.rows; i++)
	{
		for (int j = 0; j < result.size.columns; j++)
		{
			result.matrix[i][j] = obj1.matrix[i][j] - obj2.matrix[i][j];
		}
	}

	return result;
}

Matrix operator*(const Matrix& obj1, const Matrix& obj2)
{
	Matrix result;
	result.resize(obj1.size.rows, obj2.size.columns);

	if (obj1.size.columns != obj2.size.rows)
	{
		throw ERROR_OF_MULTIPLYING;
	}

	for (int i = 0; i < result.size.rows; i++)
	{
		for (int j = 0; j < result.size.columns; j++)
		{
			result.matrix[i][j] = multipy_of_vectors(i, j, obj1, obj2);
		}
	}

	return result;
}

double multipy_of_vectors(int row, int col, const Matrix& obj1, const Matrix& obj2)
{
	double elem = 0;

	for (int i = 0; i < obj1.size.columns; i++)
	{
		elem += obj1.matrix[row][i] * obj2.matrix[i][col];
	}

	return elem;
}

double Matrix::dot(const Matrix& obj1, const Matrix& obj2)
{
	double result = 0;

	if ((obj1.get_size().rows != 1 && obj1.get_size().columns != 1 || obj2.get_size().rows != 1 && obj2.get_size().columns != 1) ||
		(obj1.get_size().rows != obj2.get_size().rows && obj1.get_size().columns != obj2.get_size().columns &&
			obj1.get_size().rows != obj2.get_size().columns && obj1.get_size().columns != obj2.get_size().rows))
	{
		throw ERROR_OF_SCALAR_MULTIPLAYING;
	}

	if (obj1.get_size().rows == obj2.get_size().rows)
	{
		for (int i = 1; i <= obj1.get_size().columns; i++)
		{
			result += obj1.get_elem(1, i) * obj2.get_elem(1, i);
		}
	}
	else if (obj1.get_size().columns == obj2.get_size().columns)
	{
		for (int i = 1; i <= obj1.get_size().rows; i++)
		{
			result += obj1.get_elem(i, 1) * obj2.get_elem(i, 1);
		}
	}
	else if (obj1.get_size().rows == obj2.get_size().columns)
	{
		for (int i = 1; i <= obj1.get_size().columns; i++)
		{
			result += obj1.get_elem(1, i) * obj2.get_elem(i, 1);
		}
	}
	else if (obj1.get_size().columns == obj2.get_size().rows)
	{
		for (int i = 1; i <= obj1.get_size().rows; i++)
		{
			result += obj1.get_elem(i, 1) * obj2.get_elem(1, i);
		}
	}

	return result;
}

Matrix Matrix::Hadamard_product(const Matrix& obj1, const Matrix& obj2)
{
	if (obj1.get_size() != obj2.get_size())
	{
		throw ERROR_OF_HADAMARD_PRODUCT;
	}

	Matrix result(obj1.get_size());

	for (int i = 1; i <= obj1.get_size().rows; i++)
	{
		for (int j = 1; j <= obj1.get_size().columns; j++)
		{
			result.set_elem(obj1.get_elem(i, j) * obj2.get_elem(i, j), i, j);
		}
	}

	return result;
}

double Matrix::det(const Matrix& obj)
{
	if (!obj.is_square())
	{
		throw ERROR_OF_CALCULATING_DETERMINANT;
	}

	double result = 0;

	if (obj.get_size().rows == 1)
	{
		return obj.get_elem(1, 1);
	}
	else if (obj.get_size().rows == 2)
	{
		return (obj.get_elem(1, 1) * obj.get_elem(2, 2) - obj.get_elem(1, 2) * obj.get_elem(2, 1));
	}
	else if (obj.get_size().rows == 3)
	{
		return (obj.get_elem(1, 1) * obj.get_elem(2, 2) * obj.get_elem(3, 3) + obj.get_elem(1, 2) * obj.get_elem(2, 3) * obj.get_elem(3, 1)
			+ obj.get_elem(1, 3) * obj.get_elem(2, 1) * obj.get_elem(3, 2) - obj.get_elem(1, 3) * obj.get_elem(2, 2) * obj.get_elem(3, 1) 
			- obj.get_elem(1, 1) * obj.get_elem(2, 3) * obj.get_elem(3, 2) - obj.get_elem(1, 2) * obj.get_elem(2, 1) * obj.get_elem(3, 3)
			);
	}
	else
	{
		for (int _j = 1; _j <= obj.get_size().columns; _j++)
		{
			Matrix tmp(obj.get_size().rows - 1, obj.get_size().columns - 1);
			unsigned int j_tmp = 1;

			for (int i = 2; i <= obj.get_size().rows; i++)
			{
				for (int j = 1; j <= obj.get_size().columns; j++)
				{
					if (j == _j)
					{
						continue;
					}

					tmp.set_elem(obj.get_elem(i, j), i - 1, j_tmp++);

					if (j_tmp == (obj.get_size().columns))
						j_tmp = 1;
				}
			}

			result += std::pow((-1), (1 + (_j))) * obj.get_elem(1, _j) * det(tmp);
		}
	}
	return result;
}

Matrix Matrix::t(const Matrix& obj)
{
	Matrix result(obj.get_size().columns, obj.get_size().rows);

	for (int i = 1; i <= result.get_size().rows; i++)
	{
		for (int j = 1; j <= result.get_size().columns; j++)
		{
			result.set_elem(obj.get_elem(j, i), i, j);
		}
	}

	return result;
}

double Matrix::A(const Matrix& obj, int row, int column)
{
	double result;
	Matrix tmp(obj.get_size().rows - 1, obj.get_size().columns - 1);

	for (int i = 1, _i = 1; i <= obj.get_size().rows; i++, _i++)
	{
		if (row == i)
		{
			--_i;
			continue;
		}

		for (int j = 1, _j = 1; j <= obj.get_size().columns; j++, _j++)
		{
			if (column == j)
			{
				--_j;
				continue;
			}

			tmp.set_elem(obj.get_elem(i, j), _i, _j);
		}
	}

	result = std::pow(-1, row + column) * det(tmp);

	return result;
}

Matrix Matrix::adj(const Matrix& obj)
{
	if (!obj.is_square())
	{
		throw ERROR_OF_CALCULATING_ADJUGATE_MATRIX;
	}

	Matrix result(obj.get_size());

	for (int i = 1; i <= obj.get_size().rows; i++)
	{
		for (int j = 1; j <= obj.get_size().rows; j++)
		{
			result.set_elem(A(obj, i, j), i, j);
		}
	}

	result = t(result);

	return result;
}

Matrix Matrix::inv(const Matrix& obj)
{
	if (!obj.is_square() || det(obj) == 0)
	{
		throw ERROR_OF_CALCULATING_INVERSE_MATRIX;
	}

	return (adj(obj) / det(obj));
}

Matrix Matrix::Convert::ToIdentity(const Matrix& obj)
{
	if (obj.get_size().rows != obj.get_size().columns)
	{
		throw ERROR_OF_CONVERTING_TO_IDENTITY_MATRIX;
	}

	Matrix result(obj.get_size().rows, obj.get_size().columns);

	for (int i = 1; i <= result.get_size().rows; i++)
	{
		for (int j = 1; j <= result.get_size().columns; j++)
		{
			if (i == j)
			{
				result.set_elem(1, i, j);
			}
			else
			{
				result.set_elem(0, i, j);
			}
		}
	}

	return result;
}

Matrix Matrix::Convert::ToZeros(const Matrix& obj)
{
	Matrix result(obj.get_size().rows, obj.get_size().columns);

	for (int i = 1; i <= result.get_size().rows; i++)
	{
		for (int j = 1; j <= result.get_size().columns; j++)
		{
			result.set_elem(0, i, j);
		}
	}

	return result;
}

Matrix Matrix::Zeros(int rows, int columns)
{
	Matrix result(rows, columns);

	for (int i = 1; i <= rows; i++)
	{
		for (int j = 1; j <= columns; j++)
		{
			result.set_elem(0, i, j);
		}
	}

	return result;
}

Matrix Matrix::Identity(int rows, int columns)
{
	if (rows != columns)
	{
		throw ERROR_OF_CREATING_IDENTITY_MATRIX;
	}

	Matrix result(rows, columns);

	for (int i = 1; i <= rows; i++)
	{
		for (int j = 1; j <= columns; j++)
		{
			if (i == j)
			{
				result.set_elem(1, i, j);
			}
			else
			{
				result.set_elem(0, i, j);
			}
		}
	}

	return result;
}