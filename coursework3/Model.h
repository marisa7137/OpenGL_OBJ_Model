#pragma once
#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include "Utilities.h"
#include "Mesh.h"
#include "MTLParser.h"
#include "Camera.h"
#include "Shader.h"

class Model {
public:
	Model() {}
	~Model() {}
	void load_obj_file(std::string obj_file_name);
	void load_mtl_file(std::string mtl_file_name, std::string prefix);
	void model_setup(Shader* shader);
	void model_draw(SCamera* camera, Light light, SpotLight s_light);
	glm::vec3 model_get_scale();
	glm::vec3 model_get_translate();
	glm::vec3 model_get_rotate();
	void model_set_scale(glm::vec3 scale);
	void model_set_translate(glm::vec3 translate);
	void model_set_rotate(glm::vec3 rotate);
private:
	Shader* m_shader;
	glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	std::vector <glm::vec3> model_v_pos;
	std::vector <glm::vec2> model_v_tex;
	std::vector <glm::vec3> model_v_nor;

	std::vector <GLint> position_indicies;
	std::vector <GLint> texcoord_indicies;
	std::vector <GLint> normal_indicies;
	//std::vector <Face> faces;
	std::vector <Mesh> meshes;
	std::map <std::string, Material> material_map;
	
};