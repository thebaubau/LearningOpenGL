#pragma once

#include <string>
#include <array>
#include <stb_image.h>
#include <iostream>
#include <glad/glad.h>

struct CubemapFaces {
    std::string right;
    std::string left;
    std::string top;
    std::string bottom;
    std::string front;
    std::string back;
};

class Cubemap {
public:
	Cubemap(const CubemapFaces& faces);
	~Cubemap();

	void Bind(unsigned int slot = 0);
	void Unbind();
private:
	unsigned int m_TextureId;
};