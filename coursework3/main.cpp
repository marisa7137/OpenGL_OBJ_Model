#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include "Model.h"
#include "GLFWWindow.h"
#include "Sphere.h"
#include "Skybox.h"

double lastX = 300.0;
double lastY = 300.0;
double xoffset = 0.0;
double yoffset = 0.0;

float fov = 45.0f;
bool firstMouse = true;

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    //
    //std::cout << "xpos:" << xpos << "   ypos:" << ypos << std::endl;
    if (firstMouse) 
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    xoffset = xpos - lastX;
    yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
}

void scroll_callback(GLFWwindow* window, double x, double y)
{
	fov -= (float)y;
	if (fov < 1.0f)
	{
		fov = 1.0f;
	}
	if (fov > 45.0f)
	{
		fov = 45.0f;
	}
}

Light l1 = {
	glm::vec3(0.f, 10.f, 5.f),
	glm::vec3(0.3f, 0.3f, 0.3f),
	glm::vec3(1.f, 1.f, 1.f),
	glm::vec3(1.f, 1.f, 1.f)
};

Light l2 = {
	glm::vec3(0.f, -10.f, 5.f),
	glm::vec3(0.5f, 0.5f, 0.5f),
	glm::vec3(0.f, 1.f, 1.f),
	glm::vec3(1.f, 1.f, 1.f)
};

int main()
{
	float yRotate = 0.f;
	bool cam_change = false;
	bool space_pressed = false;
	bool light_change = false;
	bool q_pressed = false;
	bool e_pressed = false;
	GLFWwindow* window = CreateGLFWWindow(800, 600, "Lighting");
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
	Model* m = new Model();
	Model* m2 = new Model();
	Model* m3 = new Model();
	Sphere* s = new Sphere();
	SCamera* c1 = new SCamera(0.f, 0.f, 20.f, 0.f, 1.f, 0.f, -90.f, 0.f);
	SCamera* c2 = new SCamera(0.f, 0.f, -20.f, 0.f, 1.f, 0.f, 90.f, 0.f);
	SCamera* c = c1;
	glfwSetScrollCallback(window, scroll_callback);
	Shader* s1 = new Shader("Resources/shader/phongTextureless.vert", "Resources/shader/phongTextureless.frag");
	Shader* s2 = new Shader("Resources/shader/phongTextureless.vert", "Resources/shader/phongTextureless.frag");
	Shader* s3 = new Shader("Resources/shader/phong.vert", "Resources/shader/phong.frag");
	Shader* s4 = new Shader("Resources/shader/phongTextureless.vert", "Resources/shader/phongTextureless.frag");
	Skybox* sky = new Skybox();
	sky->Init();
	m->load_obj_file("Resources/models/mig/mig29.obj");
	m->load_mtl_file("Resources/models/mig/mig29.mtl", "./src/models/mig29/");
	m->model_setup(s1);
	m->model_set_translate(glm::vec3(0.0f, 0.0f, 7.0f));
	m2->load_obj_file("Resources/models/s90/S90.obj");
	m2->load_mtl_file("Resources/models/s90/S90.mtl", "Resources/models/s90/");
	m2->model_setup(s2);
	m3->load_obj_file("Resources/models/scout/Fventure.obj");
	m3->load_mtl_file("Resources/models/scout/Fventure.mtl", "Resources/models/scout/");
	m3->model_setup(s3);
	m3->model_set_translate(glm::vec3(0.f, -2.f, 0.f));
	s->Init(s4);
	s->setTranslation(glm::vec3(0.0f, 8.0f, 10.0f));
	Light l = l1;
	SpotLight s_light = {
		true,
		c->Position,
		c->Front,
		1.0f,
		0.09f,
		0.032f,
		glm::radians(5.f),
		glm::radians(7.5f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.4f, 0.4f, 0.4f),
		glm::vec3(1.f, 1.f, 1.f),
	};
	glEnable(GL_MULTISAMPLE);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		processKeyboard(window, c);
		pressToMoveModel(window, m);
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !space_pressed)
		{
			space_pressed = true;
			if (!cam_change)
			{
				c = c2;
				cam_change = true;
			}
			else {
				c = c1;
				cam_change = false;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
		{
			space_pressed = false;
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS && !q_pressed)
		{
			q_pressed = true;
			if (!light_change)
			{
				l = l2;
				light_change = true;
			}
			else {
				l = l1;
				light_change = false;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE)
		{
			q_pressed = false;
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && !e_pressed)
		{
			e_pressed = true;
			s_light.isUsing = !s_light.isUsing;
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE)
		{
			e_pressed = false;
		}
		s_light.lightPos = c->Position;
		s_light.lightDir = c->Front;
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE)
		{
			q_pressed = false;
		}
        c->ProcessMouseMovement(xoffset, yoffset);
		c->ProcessMouseScroll(fov);
		xoffset = 0.f;
		yoffset = 0.f;
		glClearColor(.2f, .3f, .3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		m->model_draw(c, l, s_light);
		m2->model_draw(c, l, s_light);
		m3->model_draw(c, l, s_light);
		s->sphere_draw(s4, c, l, s_light);
		s->setRotation(glm::vec3(0.0f, yRotate, 0.0f));
		yRotate += 0.1f;
		if (yRotate >= 360.0f)
		{
			yRotate = 0.f;
		}
		sky->Draw(c);
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	delete m;
	delete m2;
	delete m3;
	delete s;
	delete c1;
	delete c2;
	delete s1;
	delete s2;
	delete s3;
	delete s4;
	delete sky;
	return 0;
}
