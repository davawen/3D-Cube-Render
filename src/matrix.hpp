//=======================================================
//Include guard
#ifndef MATRIX_H
#define MATRIX_H
//=======================================================

class Vector3;

#include <vector>

typedef std::vector<std::vector<float>> Matrix;

Matrix             matrixMultiplication(Matrix matrix1, Matrix matrix2);
std::vector<float> matrixVectorMultiplication(Matrix matrix, Vector3 *v);

char const *matrixToString(Matrix m);

#endif