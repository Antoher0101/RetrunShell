#include "View.h"

mx::View::View()
{
	matrix_ = glm::mat4(1.f);
}

glm::vec3 mx::View::getPosition() const
{
	return eye;
}

void mx::View::lookAt(glm::vec3 vec1, glm::vec3 vec2, glm::vec3 vec3)
{
	eye = vec1; center = vec2; up = vec3;
	matrix_ = glm::lookAt(eye, center, up);
}

void mx::View::mRotate(float angle, glm::vec3 cords)
{
	matrix_ = rotate(matrix_, glm::radians(angle), cords);
}

void mx::View::mTranslate(glm::vec3 cords)
{
	matrix_ = translate(matrix_, cords);
}

void mx::View::mScale(glm::vec3 cords)
{
	matrix_ = scale(matrix_, cords);
}
