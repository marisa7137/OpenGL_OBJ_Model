#include "Model.h"

void Model::load_obj_file(std::string obj_file_name)
{
    std::stringstream ss;
    std::ifstream input_file;
    std::string line;
    std::string attribute;
    std::string material_name;
    glm::vec3 temp_vec3;
    glm::vec2 temp_vec2;
    GLint temp_int;
    int material_counter = 0;
    int face_counter = 0;
    input_file.open(obj_file_name, std::ios::in);
    if (!input_file)
    {
        throw "ERROR::Model.cpp: Error in finding file.";
    }
    if (!input_file.is_open())
    {
        throw "ERROR::Model.cpp: Cannot open obj file.";
    }

    while (std::getline(input_file, line))
    {
        attribute = "";
        ss.clear();
        ss.str(line);
        ss >> attribute;
        if (attribute == "v") //Vertex position with prefix v
        {
            ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
            model_v_pos.push_back(temp_vec3);
        }
        else if (attribute == "vt") //Vertex texture with prefix vt
        {
            ss >> temp_vec2.x >> temp_vec2.y;
            model_v_tex.push_back(temp_vec2);
        }
        else if (attribute == "vn") //Vertex normal with prefix vn
        {
            ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
            model_v_nor.push_back(temp_vec3);
        }
        else if (attribute == "usemtl")
        {

            ss >> material_name;
            Mesh ms;
            ms.mesh_material_name = material_name;
            meshes.push_back(ms);
            material_counter++;
        }
        else if (attribute == "f") //Face with prefix f
        {
            //std::cout << countInteger(line) << std::endl;
            
            unsigned int counter = 0;
            while (ss >> temp_int)
            {
                //std::cout << counter << std::endl;
                if (counter == 0)
                {
                    position_indicies.push_back(temp_int);
                }
                else if (counter == 1)
                {
                    texcoord_indicies.push_back(temp_int);
                }
                else if (counter == 2)
                {
                    normal_indicies.push_back(temp_int);
                }
                else {
                    throw "ERROR::Model: Error occurs when reading faces attributes.";
                }
                if (countInteger(line) == 9)
                {
                    if (ss.peek() == '/')
                    {
                        counter++;
                        ss.ignore(1);
                    }
                    else if (ss.peek() == ' ')
                    {
                        counter++;
                        ss.ignore(1);
                    }
                }
                else if (countInteger(line) == 6)
                {
                    if (ss.peek() == '/')
                    {
                        counter += 2;
                        ss.ignore(2);
                    }
                    else if (ss.peek() == ' ')
                    {
                        counter++;
                        ss.ignore(1);
                    }
                }
                else {
                    throw "ERROR::Model: Error occurs when reading faces attributes.";
                }

                if (counter > 2)
                {
                    counter = 0;
                }
            }
            Face f;
            size_t p_size = position_indicies.size();
            f.position_index = glm::vec3(position_indicies[p_size - 3], position_indicies[p_size - 2], position_indicies[p_size - 1]);
            //std::cout << "face: " << face_counter << " " << f.position_index.x << " " << f.position_index.y << " " << f.position_index.z << std::endl;
            size_t t_size = texcoord_indicies.size();
            face_counter++;
            if (t_size != 0)
            {
                f.texcoord_index = glm::vec3(texcoord_indicies[t_size - 3], texcoord_indicies[t_size - 2], texcoord_indicies[t_size - 1]);
            }
            size_t n_size = normal_indicies.size();
            if (n_size != 0)
            {
                f.normal_index = glm::vec3(normal_indicies[n_size - 3], normal_indicies[n_size - 2], normal_indicies[n_size - 1]);
            }
            meshes[meshes.size() - 1].mesh_faces.push_back(f);
        }
        else {
            //Ignore
        }
        //std::cout << meshes.size() << std::endl;

    }
    //std::cout << position_indicies.size() << std::endl;
    for (size_t i = 0; i < meshes.size(); i++)
    {
        meshes[i].mesh_vertices.resize(meshes[i].mesh_faces.size() * 3);
        //std::cout << meshes[i].mesh_faces.size() << std::endl;
        for (size_t j = 0; j < meshes[i].mesh_faces.size(); j++)
        {
            Vertex v1, v2, v3;
            v1.v_pos = model_v_pos[meshes[i].mesh_faces[j].position_index.x - 1];
            v2.v_pos = model_v_pos[meshes[i].mesh_faces[j].position_index.y - 1];
            v3.v_pos = model_v_pos[meshes[i].mesh_faces[j].position_index.z - 1];
            //std::cout << "Mesh: " << i << " " << "face: " << j << " ";
            //std::cout << model_v_pos[meshes[i].mesh_faces[j].position_index.x - 1].x << " ";
            //std::cout << model_v_pos[meshes[i].mesh_faces[j].position_index.x - 1].y << " ";
            //std::cout << model_v_pos[meshes[i].mesh_faces[j].position_index.x - 1].z << " " << std::endl;

            if (texcoord_indicies.size() > 0)
            {
                v1.v_tex = model_v_tex[meshes[i].mesh_faces[j].texcoord_index.x - 1];
                v2.v_tex = model_v_tex[meshes[i].mesh_faces[j].texcoord_index.y - 1];
                v3.v_tex = model_v_tex[meshes[i].mesh_faces[j].texcoord_index.z - 1];
            }
            else {
                v1.v_tex = { -1.f, -1.f };
                v2.v_tex = { -1.f, -1.f };
                v3.v_tex = { -1.f, -1.f };
            }

            if (normal_indicies.size() > 0)
            {
                v1.v_nor = model_v_nor[meshes[i].mesh_faces[j].normal_index.x - 1];
                v2.v_nor = model_v_nor[meshes[i].mesh_faces[j].normal_index.y - 1];
                v3.v_nor = model_v_nor[meshes[i].mesh_faces[j].normal_index.z - 1];
            }
            else {
                v1.v_nor = { -2.f, -2.f, -2.f };
                v2.v_nor = { -2.f, -2.f, -2.f };
                v3.v_nor = { -2.f, -2.f, -2.f };
            }

            meshes[i].mesh_vertices[j * 3] = v1;
            meshes[i].mesh_vertices[j * 3 + 1] = v2;
            meshes[i].mesh_vertices[j * 3 + 2] = v3;
        }
    }
}

void Model::load_mtl_file(std::string mtl_file_name, std::string prefix) {
    material_map = parseMTL(mtl_file_name, prefix);
    
    for (size_t i = 0; i < meshes.size(); i++)
    {
        meshes[i].mesh_material = material_map[meshes[i].mesh_material_name];
    }
}

void Model::model_setup(Shader* shader)
{
    this->m_shader = shader;
    for (unsigned int i = 0; i < meshes.size(); ++i)
        meshes[i].mesh_setup(shader);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_BLEND);
}

void Model::model_draw(SCamera* camera, Light light, SpotLight s_light)
{
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
    for (unsigned int i = 0; i < meshes.size(); ++i) {
        m_shader->Use();
        m_shader->setMat4("model", modelMatrix);
        m_shader->setMat4("view", view);
        m_shader->setMat4("projection", projection);
        m_shader->setVec3("directionalLight.lightPos", light.lightPos);
        m_shader->setVec3("direcitonalLight.ambient", light.lightAmbient);
        m_shader->setVec3("directionalLight.diffuse", light.lightDiffuse);
        m_shader->setVec3("directionalLight.specular", light.lightSpecular);
        m_shader->setBool("isUsingSpotLight", s_light.isUsing); //Using spot light or not
        m_shader->setVec3("spotLight.lightPos", s_light.lightPos);
        m_shader->setVec3("spotLight.lightDir", s_light.lightDir);
        m_shader->setVec3("spotLight.ambient", s_light.lightAmbient);
        m_shader->setVec3("spotLight.diffuse", s_light.lightDiffuse);
        m_shader->setVec3("spotLight.specular", s_light.lightSpecular);
        m_shader->setFloat("spotLight.cutOff", s_light.cutOff);
        m_shader->setFloat("spotLight.outerCutOff", s_light.outerCutOff);
        m_shader->setFloat("spotLight.constant", s_light.constant);
        m_shader->setFloat("spotLight.linear", s_light.linear);
        m_shader->setFloat("spotLight.cutOff", s_light.quadratic);
        m_shader->setVec3("camPos", camera->Position);
        meshes[i].mesh_draw(m_shader);
    }

}

void Model::model_set_scale(glm::vec3 scale) {
    this->scale = scale;
}

void Model::model_set_translate(glm::vec3 translate) {
    this->translation = translate;
}

void Model::model_set_rotate(glm::vec3 rotate) {
    this->rotation = rotate;
}

glm::vec3 Model::model_get_scale() {
    return this->scale;
}

glm::vec3 Model::model_get_translate() {
    return this->translation;
}

glm::vec3 Model::model_get_rotate() {
    return this->rotation;
}