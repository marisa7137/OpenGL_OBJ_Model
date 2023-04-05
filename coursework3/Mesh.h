#pragma once
#include <string>
#include <vector>
#include <glad/glad.h> // holds all OpenGL type declarations
#include <glm/glm/glm.hpp>
#include <map>
#include <string>
#include "Shader.h"
#include "Material.h"
#include "Shader.h"
#include "Utilities.h"
#include "MTLParser.h"
#include "Texture.h"

struct Vertex {
	glm::vec3 v_pos;
	glm::vec2 v_tex;
	glm::vec3 v_nor;
};

struct Face {
	glm::vec3 position_index;
	glm::vec3 texcoord_index;
	glm::vec3 normal_index;
};

class Mesh {
public:
	Mesh() {}
	~Mesh(){}
	Material mesh_material;
	std::string mesh_material_name;
	std::vector <Face> mesh_faces;
	std::vector <Vertex> mesh_vertices; // Usable for OpenGL
	void mesh_load_textures();
	void mesh_setup(Shader* shader);
	void mesh_draw(Shader* shader);

private:
	GLuint VAO;
	GLuint VBO;
	bool use_tex;
	std::map <std::string, unsigned int> tex_map;
};

