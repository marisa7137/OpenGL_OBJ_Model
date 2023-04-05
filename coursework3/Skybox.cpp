#include "Skybox.h"
#include <vector>
#include <string>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "Texture.h"

void Skybox::Init() {
    m_shader = new Shader("Resources/shader/skybox.vert", "Resources/shader/skybox.frag");

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //Read skybox texture and bind
    const char* faces[6] =
    {
        "Resources/img/skybox/right.bmp",
        "Resources/img/skybox/left.bmp",
        "Resources/img/skybox/top.bmp",
        "Resources/img/skybox/bottom.bmp",
        "Resources/img/skybox/front.bmp",
        "Resources/img/skybox/back.bmp",
    };

    m_texture = setup_skybox(faces, 6);

}

void Skybox::Draw(SCamera* c) {
    glDepthFunc(GL_LEQUAL);  
    glm::mat4 unit = glm::mat4(1.f);
    this->translate = c->Position;
    glm::mat4 translate = glm::translate(unit, this->translate);
    m_shader->Use();
    m_shader->setMat4("model", translate);
    m_shader->setMat4("view", c->GetViewMatrix());
    m_shader->setMat4("projection", glm::perspective(glm::radians(c->Zoom), 800.0f / 600.0f, 0.1f, 150.0f));
    glBindVertexArray(m_VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}
