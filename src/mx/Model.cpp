#include "Model.h"

mx::Model::Model()
{
	matrix_ = glm::mat4(1.f);
}

void mx::Model::mRotate(float angle, glm::vec3 cords)
{
	matrix_ = rotate(matrix_, glm::radians(angle), cords);
}

void mx::Model::mTranslate(glm::vec3 cords)
{
	matrix_ = translate(matrix_, cords);
}

void mx::Model::mScale(glm::vec3 cords)
{
	matrix_ = scale(matrix_, cords);
}

