#include <iostream>
#include "Matrix.h"

int main(int argc, char* argv[])
{
	Matrix mat1 {
		{2, 2, 14},
		{3, 6, 0},
		{2, 5, 1}
	};

	Matrix mat2 {
		{1, 2, 7, 1},
		{2, 4, 3, 1},
		{4, 2, 2, 3},
		{3, 1, 2, 1}
	};

	try
	{
		std::cout << det(mat2) << std::endl;
	}
	catch (const char* exception)
	{
		std::cout << exception << std::endl;
	}

	return 0;
}