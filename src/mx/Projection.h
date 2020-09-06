#pragma once

#include "Matrix.h"

#include <glm/gtx/transform.hpp>

namespace mx
{
	class Projection : public Matrix
	{
	public:
		Projection();
		// Sets the perspective projection
		// Gets field of view(in degrees), screen parameters and z-axis clipping distance
		void setPerspective(float fov, float screenWidth, float screenHeight, float zNear = 0.1f, float zFar = 100.f);
		
		// Not working yet
		void setOrtho(float screenWidth, float screenHeight, float zNear = 0.1f, float zFar = 100.f);
		
		void mRotate(float angle, glm::vec3 cords) override;
		void mTranslate(glm::vec3 cords) override;
		void mScale(glm::vec3 cords) override;
	};
}
