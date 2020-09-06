#pragma once

#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace mx
{
	class Matrix
	{
	protected:
		glm::mat4 matrix_;
	public:
		glm::mat4 getMatrix();
		virtual void mRotate(float angle, glm::vec3 cords) = 0;
		virtual void mTranslate(glm::vec3 cords) = 0;
		virtual void mScale(glm::vec3 cords) = 0;
		Matrix();
		virtual ~Matrix();
	};
}

