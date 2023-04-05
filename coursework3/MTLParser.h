#pragma once
#include <glm/glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "Material.h"
#include "MTLParser.h"
#include "Texture.h"

struct MTLFile {
	int id;
	std::string fileName;
	std::map <std::string, Material> material_list;
};

std::map<std::string, Material> parseMTL(std::string mtl_file_name, std::string prefix);