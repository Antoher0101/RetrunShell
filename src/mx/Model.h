#pragma once

#include "Matrix.h"

namespace mx
{
	class Model : public Matrix
	{
	public:
		Model();
		
		void mRotate(float angle, glm::vec3 cords) override;
		void mTranslate(glm::vec3 cords) override;
		void mScale(glm::vec3 cords) override;
		
	};

}
