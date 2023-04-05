#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Shader.h"
#include <string>
#include "Camera.h"
class Camera;

class Skybox {

public:
    Skybox() {};
    void Init();
    void Draw(SCamera* c);

private:

    glm::vec3 translate = glm::vec3(0.0, 0.0, 0.0);
    GLuint m_VAO, m_VBO, m_texture;

    Shader* m_shader;

    float vertices[18 * 6]{
        
         1.0f, -1.0f, -1.0f, 
         1.0f,  1.0f, -1.0f, 
        -1.0f,  1.0f, -1.0f, 
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         
        -1.0f,  1.0f, -1.0f, 
        -1.0f,  1.0f,  1.0f, 
        -1.0f, -1.0f,  1.0f, 
        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

         1.0f, -1.0f, -1.0f, 
         1.0f, -1.0f,  1.0f, 
         1.0f,  1.0f,  1.0f, 
         1.0f,  1.0f,  1.0f, 
         1.0f,  1.0f, -1.0f, 
         1.0f, -1.0f, -1.0f, 

        -1.0f, -1.0f,  1.0f, 
        -1.0f,  1.0f,  1.0f, 
         1.0f,  1.0f,  1.0f, 
         1.0f,  1.0f,  1.0f, 
         1.0f, -1.0f,  1.0f, 
        -1.0f, -1.0f,  1.0f, 

        -1.0f,  1.0f, -1.0f, 
         1.0f,  1.0f, -1.0f, 
         1.0f,  1.0f,  1.0f, 
         1.0f,  1.0f,  1.0f, 
        -1.0f,  1.0f,  1.0f, 
        -1.0f,  1.0f, -1.0f, 

        -1.0f, -1.0f, -1.0f, 
        -1.0f, -1.0f,  1.0f, 
         1.0f, -1.0f, -1.0f, 
         1.0f, -1.0f, -1.0f, 
        -1.0f, -1.0f,  1.0f, 
         1.0f, -1.0f,  1.0f, 
    };
};