#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <sstream>
#include <fstream>
#include "Mesh.h"


void Mesh::mesh_load_textures() {
    //std::cout << mesh_material.texs.size() << " " << std::endl;
    use_tex = mesh_material.texs.size() > 0;
    if (use_tex)
    {
        for (unsigned int i = 0; i < mesh_material.texs.size(); i++)
        {
            //std::cout << mesh_material.name << ": " <<mesh_material.texs[i].tex_type << " " << i << std::endl;
            if (tex_map.count(mesh_material.texs[i].tex_path))
            {
                mesh_material.texs[i].id = tex_map[mesh_material.texs[i].tex_path];
            }
            else {
                mesh_material.texs[i].id = setup_texture(mesh_material.texs[i].tex_path.c_str());
                tex_map[mesh_material.texs[i].tex_path] = mesh_material.texs[i].id;
            }

        }
    }
}

void Mesh::mesh_setup(Shader* shader) {
      //std::cout << mesh_material_name << ": ";
      //std::cout << "Kd: " << mesh_material.Kd.x << ", " << mesh_material.Kd.y << ", " << mesh_material.Kd.z << ", " << std::endl;
      glGenVertexArrays(1, &VAO);
      glBindVertexArray(VAO);
      glGenBuffers(1, &VBO);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, mesh_vertices.size() * sizeof(Vertex), &mesh_vertices[0], GL_STATIC_DRAW);

      // set the vertex attribute pointers
      // vertex Positions
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
      // vertex normals
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, v_tex));
      // vertex texture coords
      glEnableVertexAttribArray(2);
      glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, v_nor));

      glBindVertexArray(0);
      //shader->Use();
      this->mesh_load_textures();
      shader->Use();
      if (mesh_material.texs.size() > 0)
      {
          //std::cout << shader->shaderProgram << std::endl;
          unsigned int ambientNr = 1;
          unsigned int diffuseNr = 1;
          unsigned int specularNr = 1;
          unsigned int normalNr = 1;
          unsigned int heightNr = 1;
          for (unsigned int i = 0; i < mesh_material.texs.size(); i++)
          {
              glActiveTexture(GL_TEXTURE0 + i);
              //mesh_material.texs[i].id = setup_texture((mesh_material.texs[i].tex_path).c_str());
              std::string name = mesh_material.texs[i].tex_type;
              std::string number;
              if (name == "tex_amb")
                  number = std::to_string(ambientNr++);
              else if (name == "tex_dif")
                  number = std::to_string(diffuseNr++); // transfer unsigned int to stream
              else if (name == "tex_spec")
                  number = std::to_string(specularNr++); // transfer unsigned int to stream
              else if (name == "tex_d")
                  number = std::to_string(normalNr++); // transfer unsigned int to stream
              else if (name == "tex_bump")
                  number = std::to_string(heightNr++);
              shader->setInt((name + number).c_str(), i);
              glBindTexture(GL_TEXTURE_2D, mesh_material.texs[i].id);
          }
      }
      shader->setVec3("material.ambient", mesh_material.Ka);
      shader->setVec3("material.diffuse", mesh_material.Kd);
      shader->setVec3("material.specular", mesh_material.Ks);
      shader->setFloat("material.shininess", mesh_material.Ns);
      
}

void Mesh::mesh_draw(Shader* shader)
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, mesh_vertices.size());
    glBindVertexArray(0);
    if (mesh_material.texs.size() > 0)
    {
        glActiveTexture(GL_TEXTURE0);
    }
}