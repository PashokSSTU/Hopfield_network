#pragma once
#include <iostream>
#include "Matrix.h"

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

Matrix& Matrix::operator=(std::initializer_list<std::initializer_list<double>>& l)
{
	size.rows = l.size();
	//size.columns =

	auto ptr = std::data(l);

	unsigned int counter = 0;
	for (auto row : l)
		std::copy(row.begin(), row.end(), matrix[counter++].begin());

	return *this;
}