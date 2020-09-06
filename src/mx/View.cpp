#include "View.h"

mx::View::View()
{
	matrix_ = glm::mat4(1.f);
}

void mx::View::lookAt(glm::vec3 vec1, glm::vec3 vec2, glm::vec3 vec3)
{
	matrix_ = glm::lookAt(vec1, vec2, vec3);
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
