#include "GLFWwindow.h"

void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}

GLFWwindow* CreateGLFWWindow(int w, int h, const char* title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(w, h, title, NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	return window;
}

void processKeyboard(GLFWwindow* window, SCamera* camera) {
	

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(FORWARD);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(BACKWARD);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(LEFT);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		camera->ProcessKeyboard(RIGHT);
	}
}

void pressToMoveModel(GLFWwindow* window, Model* m) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		//std::cout << "pressed w" << std::endl;
		glm::vec3 cur_translation = m->model_get_translate();
		cur_translation = cur_translation + glm::vec3(0.0f, 1.0f / 60, 0.0f);
		m->model_set_translate(cur_translation);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		//std::cout << "pressed s" << std::endl;
		glm::vec3 cur_translation = m->model_get_translate();
		cur_translation = cur_translation + glm::vec3(0.0f, -1.0f / 60, 0.0f);
		m->model_set_translate(cur_translation);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		//std::cout << "pressed a" << std::endl;
		glm::vec3 cur_translation = m->model_get_translate();
		cur_translation = cur_translation + glm::vec3(-1.0f / 60, 0.0f, 0.0f);
		m->model_set_translate(cur_translation);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		//std::cout << "pressed d" << std::endl;
		glm::vec3 cur_translation = m->model_get_translate();
		cur_translation = cur_translation + glm::vec3(1.0f / 60, 0.0f, 0.0f);
		m->model_set_translate(cur_translation);
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		glm::vec3 cur_translation = m->model_get_translate();
		cur_translation = cur_translation + glm::vec3(0.0f, 0.0f, 1.0f / 60);
		m->model_set_translate(cur_translation);
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		glm::vec3 cur_translation = m->model_get_translate();
		cur_translation = cur_translation + glm::vec3(0.0f, 0.0f, -1.0f / 60);
		m->model_set_translate(cur_translation);
	}
}
