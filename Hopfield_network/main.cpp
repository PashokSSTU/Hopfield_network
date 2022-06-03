#include <iostream>
#include "Matrix.h"

int main(int argc, char* argv[])
{
	try
	{
		Matrix matrix = { 
			{1, 2},
			{3, 4}
		};

		Matrix E = Matrix::Identity(2, 2);

		std::cout << det(E) << std::endl;

	}
	catch (const char* exception)
	{
		std::cout << exception << std::endl;
	}

	return 0;
}