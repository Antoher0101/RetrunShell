#include "ViewCam.h"

ViewCam::ViewCam()
{
	mlastPos = { 640.f,480.f };
	mPos = { 0.f,0.f };
	front = { 0.f,0.f,0.f };
	euler_ = { 0.f,-90.f,0.f };

	cameraPos = { 0.0f, 0.0f, 0.0f };
	cameraFront = { 0.0f, 0.0f, -1.0f };
}

void ViewCam::setFirstMousePos(glm::vec2 mPos)
{
	this->mPos = mPos;
}

void ViewCam::setMouseLastPos(glm::vec2 mPos)
{
	mlastPos = mPos;
}

// Calculate offset and refresh pitch/raw value
void ViewCam::calculateCam()
{
	offset = { mPos.x - mlastPos.x,mlastPos.y - mPos.y };
	euler_.pitch += offset.y * sensitivity;
	euler_.yaw += offset.x * sensitivity;
	front.x = cos(glm::radians(euler_.yaw)) * cos(glm::radians(euler_.pitch));
	front.y = sin(glm::radians(euler_.pitch));
	front.z = sin(glm::radians(euler_.yaw)) * cos(glm::radians(euler_.pitch));
	cameraFront = glm::normalize(front);
	mlastPos = mPos;
}

void ViewCam::setsensitivity(float sens)
{
	sensitivity = sens;
}

void ViewCam::movementCam(CamDirection dir)
{
	if (dir == MOVE_FORWARD)
		cameraPos += motionSpeed * cameraFront* time;
	if (dir == MOVE_BACK)
		cameraPos -= motionSpeed * cameraFront* time;
	if (dir == MOVE_LEFT)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * motionSpeed*time;
	if (dir == MOVE_RIGHT)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * motionSpeed* time;
}

glm::vec3 ViewCam::getCameraFront()
{
	return cameraFront;
}

glm::vec3 ViewCam::getCameraPos()
{
	return cameraPos;
}

glm::vec3 ViewCam::getCameraUp()
{
	return cameraUp;
}

void ViewCam::setElapsedTime(float t)
{
	time = t;
}

ViewCam::~ViewCam()
{
}
