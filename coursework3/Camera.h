#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm/gtc/matrix_transform.hpp>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 1.0f;
const GLfloat SENSITIVTY = 0.5f;
const GLfloat ZOOM = 45.0f;
const GLfloat DELTATIME = 1.0f / 60.0f;

// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class SCamera
{
public:
	// Camera Attributes
	glm::vec3 Eangles;
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// Eular Angles
	GLfloat Yaw;
	GLfloat Pitch;
	// Camera options
	GLfloat MovementSpeed;
	GLfloat MouseSensitivity;
	GLfloat Zoom;

	SCamera(glm::vec3 euler = glm::vec3(0.f, 0.f, 0.f), glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);

	SCamera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);

	glm::mat4 GetViewMatrix();

	void ProcessKeyboard(Camera_Movement direction);

	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset);

	void ProcessMouseScroll(GLfloat fov);

	~SCamera();
private:
	void updateCameraVectors();
};