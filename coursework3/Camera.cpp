#include "Camera.h"
#include <glm/glm/glm.hpp>
#include <iostream>

SCamera::SCamera(glm::vec3 euler, glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
{
	this->Eangles = euler;
	this->Position = position;
	this->WorldUp = up;
	this->Yaw = yaw;
	this->Pitch = pitch;
	this->updateCameraVectors();
}

SCamera::SCamera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
{
	this->Position = glm::vec3(posX, posY, posZ);
	this->WorldUp = glm::vec3(upX, upY, upZ);
	this->Yaw = yaw;
	this->Pitch = pitch;
	this->updateCameraVectors();
}

glm::mat4 SCamera::GetViewMatrix()
{
	return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
}

void SCamera::ProcessKeyboard(Camera_Movement direction)
{
	
	GLfloat velocity = this->MovementSpeed * DELTATIME;
	if (direction == FORWARD)
		this->Position += this->Front * velocity;
	    //std::cout << Position.x << Position.y << Position.z << std::endl;
	if (direction == BACKWARD)
		this->Position -= this->Front * velocity;
	    //std::cout << Position.x << Position.y << Position.z << std::endl;
	if (direction == LEFT)
		this->Position -= this->Right * velocity;
	    //std::cout << Position.x << Position.y << Position.z << std::endl;
	if (direction == RIGHT)
		this->Position += this->Right * velocity;
	    //std::cout << Position.x << Position.y << Position.z << std::endl;
}

void SCamera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset)
{
	xoffset *= this->MouseSensitivity;
	yoffset *= this->MouseSensitivity;

	this->Yaw += xoffset;
	this->Pitch += yoffset;

	if (this->Pitch > 89.0f) {
		this->Pitch = 89.0f;
	}
	if (this->Pitch < -89.0f) {
		this->Pitch = -89.0f;
	}
		

	this->updateCameraVectors();
}

void SCamera::ProcessMouseScroll(GLfloat fov)
{
	GLfloat zoom = fov;
	if (zoom < 1.0f) {
		zoom = 1.0f;
	}
		
	if (zoom > 45.0f) {
		zoom = 45.0f;
	}
	this->Zoom = zoom;
}

SCamera::~SCamera(){};

void SCamera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
	front.y = sin(glm::radians(this->Pitch));
	front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
	this->Front = glm::normalize(front);
	this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp)); 
	this->Up = glm::normalize(glm::cross(this->Right, this->Front));
}
