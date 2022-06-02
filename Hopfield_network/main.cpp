#include <iostream>
#include "Matrix.h"

int main(int argc, char* argv[])
{
	Matrix mat1{ {1, 2}, {3, 4}, {5, 6} };
	Matrix mat2(3, 3);

	mat1 = { {5} };

	std::cout << mat1 << std::endl;

	return 0;
}