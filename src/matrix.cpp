#include <iostream>
#include <string>

#include "matrix.hpp"
#include "vector.hpp"

Matrix matrixMultiplication(Matrix matrix1, Matrix matrix2)
{
	if(matrix1.size() != matrix2[0].size())
	{
		throw "Wrong amount of columns!";
		return {};
	}

	Matrix result;
	result.reserve(matrix1.size());
	
	for(unsigned int i = 0; i < matrix1.size(); i++)
	{
		result.push_back({});
		result[i].reserve(matrix2[i].size());
		for(unsigned int j = 0; j < matrix2[i].size(); j++)
		{
			result[i].push_back(0.f);
			
			for(unsigned int k = 0; k < matrix1.size(); k++)
			{
				result[i][j] += matrix1[k][j] * matrix2[i][k];
			}
		}
	}
	
	return result;
}

std::vector<float> matrixVectorMultiplication(Matrix matrix, Vector3 *v)
{
	if(matrix[0].size() != 3)
	{
		throw "Wrong amount of columns!";
		return {};
	}
	
	std::vector<float> result;
	result.resize(matrix.size());
	
	for(unsigned int i = 0; i < matrix.size(); i++)
	{
		result[i] = matrix[i][0] * v->x + matrix[i][1] * v->y + matrix[i][2] * v->z;
	}

	return result;
}

const char *matrixToString(Matrix m)
{
	std::string str = std::string("{\n");

	for(unsigned int i = 0; i < m.size(); i++)
	{
		str += "  { ";
		
		for(unsigned int j = 0; j < m[i].size(); j++)
		{
			str += std::to_string(m[i][j]) + ", ";
		}
		
		str += "  },\n";
	}
	str += "}";
	
	return str.c_str();
}