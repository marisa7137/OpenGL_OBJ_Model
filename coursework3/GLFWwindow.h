#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "Model.h"
#include "Material.h"
void framebuffer_size_callback(GLFWwindow* window, int w, int h);

GLFWwindow* CreateGLFWWindow(int w, int h, const char* title);

void processKeyboard(GLFWwindow* window, SCamera* camera);

void pressToMoveModel(GLFWwindow* window, Model* m);
