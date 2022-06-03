#include "Hopfield.h"

Matrix hopfield_sign(const Matrix& v)
{
	Matrix result(v.get_size());

	for (int i = 1; i <= result.get_size().rows; i++)
	{
		for (int j = 1; j <= result.get_size().columns; j++)
		{
			if (v.get_elem(i, j) > 0)
			{
				result.set_elem(1, i, j);
			}
			else if(v.get_elem(i, j) < 0)
			{
				result.set_elem(-1, i, j);
			}
		}
	}

	return result;
}