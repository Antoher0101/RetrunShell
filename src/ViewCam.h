#pragma once
#include "glm/glm.hpp"

#define MOVE_FORWARD 0x01
#define MOVE_BACK 0x02
#define MOVE_LEFT 0x03
#define MOVE_RIGHT 0x04

typedef unsigned int CamDirection;

struct Euler
{
	float pitch;
	float yaw;
	float roll;
};
class ViewCam
{
	glm::vec2 mlastPos;
	glm::vec2 mPos;
	glm::vec2 offset;

	// Mouse sensitivity
	float sensitivity = 0.1;
	// Camera movement speed
	float motionSpeed = 0.1;

	// time for sync
	float time = 0.f;
	glm::vec3 front;
	// cameraFront is normalize is 'front'
	glm::vec3 cameraFront;
	glm::vec3 cameraPos;
	const glm::vec3 cameraUp = { 0.0f, 1.0f, 0.0f };
	// Pitch - along the Y axis
	// Yaw   - along the X axis
	// Roll  - along the Z axis
	Euler euler_;
	
public:
	ViewCam();
	void setMousePos(glm::vec2 mPos);
	void setMouseLastPos(glm::vec2 mPos);
	void calculateCam();
	void setsensitivity(float sens);
	void movementCam(CamDirection dir);
	glm::vec3 getCameraFront();
	glm::vec3 getCameraPos();
	glm::vec3 getCameraUp();

	void setElapsedTime(float t);
	~ViewCam();
};

