#include <vector>
#include <glm/glm/glm.hpp>
#include <glad/glad.h>
#include "Sphere.h"



void Sphere::Init(Shader* shader) {
    m_shader = shader;
    translation = glm::vec3(0.f, 0.f, 0.f);
    scale = glm::vec3(1.f, 1.f, 1.f);
    rotation = glm::vec3(0.f, 0.f, 0.f);
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    //Divide the sphere into 64 pieces
    for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
    {
        for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
        {
            float xSegment = (float)x / (float)X_SEGMENTS;
            float ySegment = (float)y / (float)Y_SEGMENTS;
            float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            //std::cout << xPos << ", " << yPos << ", " << zPos << std::endl;
            positions.push_back(glm::vec3(xPos, yPos, zPos));
            uv.push_back(glm::vec2(xSegment, ySegment));
            normals.push_back(glm::normalize(glm::vec3(xPos, yPos, zPos)));
        }
    }

    bool isOdd = false;
    for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
    {
        if (!isOdd)
        {
            for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
            {
                indices.push_back(y * (X_SEGMENTS + 1) + x);
                indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
            }
        }

        else
        {
            for (int x = X_SEGMENTS; x >= 0; --x)
            {
                indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                indices.push_back(y * (X_SEGMENTS + 1) + x);
            }
        }
        isOdd = !isOdd;
    }
    indexCount = indices.size();
    
    for (unsigned int i = 0; i < positions.size(); ++i)
    {
        vertices.push_back(positions[i].x);
        vertices.push_back(positions[i].y);
        vertices.push_back(positions[i].z);
        if (uv.size() > 0)
        {
            vertices.push_back(uv[i].x);
            vertices.push_back(uv[i].y);
        }
        if (normals.size() > 0)
        {
            vertices.push_back(normals[i].x);
            vertices.push_back(normals[i].y);
            vertices.push_back(normals[i].z);
        }
    }
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    float stride = (3 + 2 + 3) * sizeof(float);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(5 * sizeof(float)));
    
}
void Sphere::sphere_draw(Shader* shader, SCamera* camera, Light light, SpotLight s_light)
{
    shader->Use();
    glm::mat4 unit = glm::mat4(1.0f);
    glm::mat4 scale = glm::scale(unit, this->scale);
    glm::mat4 translate = glm::translate(unit, this->translation);
    glm::mat4 rotate = unit;
    rotate = glm::rotate(rotate, glm::radians(this->rotation.x), glm::vec3(1, 0, 0));
    rotate = glm::rotate(rotate, glm::radians(this->rotation.y), glm::vec3(0, 1, 0));
    rotate = glm::rotate(rotate, glm::radians(this->rotation.z), glm::vec3(0, 0, 1));
    glm::mat4 modelMatrix = translate * rotate * scale;
    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), 800.0f / 600.0f, 0.1f, 150.0f);
    shader->setMat4("model", modelMatrix);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);
    shader->setVec3("directionalLight.lightPos", light.lightPos);
    shader->setVec3("directionalLight.ambient", light.lightAmbient);
    shader->setVec3("directionalLight.diffuse", light.lightDiffuse);
    shader->setVec3("directionalLight.specular", light.lightSpecular);
    shader->setBool("isUsingSpotLight", s_light.isUsing);
    shader->setVec3("spotLight.lightPos", s_light.lightPos);
    shader->setVec3("spotLight.lightDir", s_light.lightDir);
    shader->setVec3("spotLight.ambient", s_light.lightAmbient);
    shader->setVec3("spotLight.diffuse", s_light.lightDiffuse);
    shader->setVec3("spotLight.specular", s_light.lightSpecular);
    shader->setFloat("spotLight.cutOff", s_light.cutOff);
    shader->setFloat("spotLight.outerCutOff", s_light.outerCutOff);
    shader->setFloat("spotLight.constant", s_light.constant);
    shader->setFloat("spotLight.linear", s_light.linear);
    shader->setFloat("spotLight.cutOff", s_light.quadratic);
    shader->setVec3("material.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
    shader->setVec3("material.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
    shader->setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    shader->setFloat("material.shininess", 200.0f);
    shader->setVec3("camPos", camera->Position);
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
}

void Sphere::setTranslation(glm::vec3 translate) {
    this->translation = translate;
}
void Sphere::setRotation(glm::vec3 rotate) {
    this->rotation = rotate;
}