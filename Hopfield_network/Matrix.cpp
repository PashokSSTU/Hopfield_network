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

Matrix Matrix::operator+() const
{
	return *this;
}

Matrix Matrix::operator-() const
{
	Matrix mat;
	mat.resize(size);

	for (int i = 0; i < size.rows; i++)
	{
		for (int j = 0; j < size.columns; j++)
		{
			mat.matrix[i][j] = -1 * matrix[i][j];
		}
	}

	return mat;
}