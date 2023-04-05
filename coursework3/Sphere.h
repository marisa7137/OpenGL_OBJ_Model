#pragma once
#include <glad/glad.h>
#include "Shader.h"
#include "Material.h"
#include "Camera.h"
class Sphere {
public:
	Sphere() {};
	void Init(Shader* shader);
	void sphere_draw(Shader* shader, SCamera* camera, Light light, SpotLight s_light);
    void setTranslation(glm::vec3 translate);
    void setRotation(glm::vec3 rotate);

private:
    Shader* m_shader;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> uv;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;
    std::vector<float> vertices;
    glm::vec3 translation;
    glm::vec3 rotation;
    glm::vec3 scale;
    const unsigned int X_SEGMENTS = 64;
    const unsigned int Y_SEGMENTS = 64;
    const float PI = 3.14159265359;
    unsigned int indexCount = 0;
    GLuint m_VAO, m_VBO, m_EBO;
};