#pragma once

#include "Matrix.h"

namespace mx
{
	
	class View : public mx::Matrix
	{
		glm::vec3 eye;
		glm::vec3 center;
		glm::vec3 up;
	public:
		View();
		glm::vec3 getPosition() const;
		void lookAt(glm::vec3 vec1, glm::vec3 vec2, glm::vec3 vec3);
		
		void mTranslate(glm::vec3 cords) override;
		void mScale(glm::vec3 cords) override;
		void mRotate(float angle, glm::vec3 cords) override;
	};
	
}