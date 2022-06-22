#include <iostream>
#include "Matrix.h"
#include "Hopfield.h"

using namespace std;

int main(int argc, char* argv[])
{
	try
	{
		Matrix A = {
			{1},
			{3}
		};

		Matrix B = {
			{2, 4}
		};

		A *= B;

		cout << A << endl;

	}
	catch (const char* exception)
	{
		std::cout << exception << std::endl;
	}

	return 0;
}