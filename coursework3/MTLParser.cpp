#include "MTLParser.h"

std::map<std::string, Material> parseMTL(std::string mtl_file_name, std::string prefix) {
	std::map <std::string, Material> material_map;
	std::stringstream ss;
	std::ifstream input_file;
	std::string line;
	std::string attribute;
	std::string material_name;
	std::string temp_string;
	glm::vec3 temp_vec3;
	GLint temp_int;
	GLfloat temp_float;
	input_file.open(mtl_file_name, std::ios::in);
	if (!input_file)
	{
		throw "ERROR::MTLParser.cpp: Error in finding file.";
	}
	if (!input_file.is_open())
	{
		throw "ERROR::MTLParser.cpp: Cannot open mtl file.";
	}
	while (std::getline(input_file, line)) {
		attribute = "";
		ss.clear();
		ss.str(line);
		ss >> attribute;
		//std::cout << attribute.c_str() << std::endl;
		if (attribute == "newmtl")
		{
			ss >> material_name;
			//std::cout << material_name << std::endl;
			Material m;
			m.name = material_name;
			material_map.insert(std::map <std::string, Material>::value_type(material_name, m));
		}
		else if (attribute == "Ns") {
			ss >> temp_float;
			material_map[material_name].Ns = temp_float;
		}
		else if (attribute == "Ka") {
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			material_map[material_name].Ka = temp_vec3;
		}
		else if (attribute == "Kd") {
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			material_map[material_name].Kd = temp_vec3;
		}
		else if (attribute == "Ks") {
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			material_map[material_name].Ks = temp_vec3;
		}
		else if (attribute == "Ke") {
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			material_map[material_name].Ke = temp_vec3;
		}
		else if (attribute == "Ni") {
			ss >> temp_float;
			material_map[material_name].Ni = temp_float;
		}
		else if (attribute == "d") {
			ss >> temp_float;
			material_map[material_name].d = temp_float;
		}
		else if (attribute == "illum")
		{
			ss >> temp_int;
			material_map[material_name].illum = temp_int;
		}
		else if (attribute == "map_Ka") {
			ss >> temp_string;
			Texture t;
			t.id = -1;
			t.tex_type = "tex_amb";
			t.tex_path = prefix + temp_string;
			material_map[material_name].texs.push_back(t);
		}
		else if (attribute == "map_Kd") {
			ss >> temp_string;
			Texture t;
			t.id = -1;
			t.tex_type = "tex_dif";
			t.tex_path = prefix + temp_string;
			//std::cout << material_name << std::endl;
			//std::cout << temp_string << std::endl;
			material_map[material_name].texs.push_back(t);
		}
		else if (attribute == "map_Ks") {
			ss >> temp_string;
			Texture t;
			t.id = -1;
			t.tex_type = "tex_spec";
			t.tex_path = prefix + temp_string;
			material_map[material_name].texs.push_back(t);
		}
		else if (attribute == "map_d") {
			ss >> temp_string;
			Texture t;
			t.id = -1;
			t.tex_type = "tex_d";
			t.tex_path = prefix + temp_string;
			material_map[material_name].texs.push_back(t);
		}
		else if (attribute == "map_bump" || attribute == "bump") {
			ss >> temp_string;
			Texture t;
			t.id = -1;
			t.tex_type = "tex_bump";
			t.tex_path = prefix + temp_string;
			material_map[material_name].texs.push_back(t);
		}
		else {
			//throw "ERROR:: MTLParser.h: Unknown attribute, invalid .mtl file.\n";
		}
		//for (size_t i = 0; i < material_map[material_name].texs.size(); i++)
		//{
		//	material_map[material_name].texs[i].tex_path = prefix + material_map[material_name].texs[i].tex_path;
		//}
		//std::cout << material_name << ": " << material_map[material_name].texs.size() <<std::endl;
	}
	//std::cout << material_map.size();
	//for (auto c: material_map)
	//{
		//std::cout << c.first << ": Texture size: " << c.second.texs.size() << std::endl;
	//}
	return material_map;
	
}
