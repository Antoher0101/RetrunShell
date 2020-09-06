#include "Projection.h"

mx::Projection::Projection()
{
	matrix_ = glm::mat4(1.f);
}

void mx::Projection::setPerspective(float fov, float screenWidth, float screenHeight, float zNear, float zFar)
{
	matrix_ = glm::perspective(glm::radians(fov), screenWidth / screenHeight, zNear, zFar);
}

void mx::Projection::setOrtho(float screenWidth, float screenHeight, float zNear, float zFar)
{
	matrix_ = glm::ortho(0.f, screenWidth, 0.f, screenHeight, zNear, zFar);
}

void mx::Projection::mRotate(float angle, glm::vec3 cords)
{
	matrix_ = rotate(matrix_, glm::radians(angle), cords);
}

void mx::Projection::mTranslate(glm::vec3 cords)
{
	matrix_ = translate(matrix_, cords);
}

void mx::Projection::mScale(glm::vec3 cords)
{
	matrix_ = scale(matrix_, cords);
}
