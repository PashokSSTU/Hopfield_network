#include <iostream>
#include "Matrix.h"

using namespace std;

int main(int argc, char* argv[])
{
	try
	{
		Matrix A = {
			{1, 2}
		};

		Matrix B = {
			{1},
			{2}
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