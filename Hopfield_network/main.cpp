#include <iostream>
#include "Matrix.h"

int main(int argc, char* argv[])
{
	Matrix mat{
		{1, 2}, 
		{3, 4}, 
		{5, 6} 
	};

	mat = +mat;

	std::cout << mat << std::endl;

	return 0;
}