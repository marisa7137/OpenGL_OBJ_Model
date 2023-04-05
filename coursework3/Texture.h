#pragma once
#include <glad/glad.h> 
#include <iostream>
#include "bitmap.h"
#include <string>
#include <vector>

GLuint setup_texture(const char* filename);

GLuint setup_mipmaps(const char* filename[], int n);

GLuint setup_skybox(const char* filename[], int n);