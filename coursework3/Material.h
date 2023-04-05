#pragma once
#include <glad/glad.h>
#include <glm/glm/glm.hpp>

struct Texture {
	int id;
	std::string tex_type;
	std::string tex_path;
};

struct Material {
	std::string name;
	GLfloat Ns;
	glm::vec3 Ka;
	glm::vec3 Kd;
	glm::vec3 Ks;
	glm::vec3 Ke;
	glm::vec3 Tf;
	GLfloat Ni;
	GLfloat d;
	GLfloat Tr;
	GLint illum;

	std::vector <Texture> texs;
};

struct Light {
	glm::vec3 lightPos;
	glm::vec3 lightAmbient;
	glm::vec3 lightDiffuse;
	glm::vec3 lightSpecular;
};

struct SpotLight {
	bool isUsing;
	glm::vec3 lightPos;
	glm::vec3 lightDir;
	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	glm::vec3 lightAmbient;
	glm::vec3 lightDiffuse;
	glm::vec3 lightSpecular;
};
