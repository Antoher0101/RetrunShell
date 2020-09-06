#include "Matrix.h"

mx::Matrix::Matrix()
{
	matrix_ = glm::mat4(1.f);
}

glm::mat4 mx::Matrix::getMatrix()
{
	return matrix_;
}

mx::Matrix::~Matrix()
{
}