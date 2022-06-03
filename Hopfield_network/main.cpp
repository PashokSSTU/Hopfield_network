#include <iostream>
#include "Matrix.h"
#include "Hopfield.h"

int main(int argc, char* argv[])
{
	try
	{
		Matrix A1 = { {1, -1, 1, -1} };
		Matrix A2 = { {-1, 1, 1, -1} };
		Matrix A3 = { {-1, -1, 1, 1} };
		Matrix A4 = { {1, 1, -1, -1} };

		Matrix C = { {-1, 1, -1, -1} };

		Matrix W = 0.25 * ((Matrix::t(A1) * A1 - Matrix::Identity(4, 4)) + (Matrix::t(A2) * A2 - Matrix::Identity(4, 4)) +
			(Matrix::t(A3) * A3 - Matrix::Identity(4, 4)) + (Matrix::t(A4) * A4 - Matrix::Identity(4, 4)));

		Matrix tmp;

		while (C != A1 && C != A2 && C != A3 && C != A4)
		{
			C = C * W;
			C = hopfield_sign(C);
		}

		std::cout << C << std::endl;
	}
	catch (const char* exception)
	{
		std::cout << exception << std::endl;
	}

	return 0;
}