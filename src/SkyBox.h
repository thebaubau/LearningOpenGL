#include <string>
#include <array>
#include <stb_image.h>
#include <iostream>
#include <glad/glad.h>

struct CubeFaces {
    std::string right;
    std::string left;
    std::string top;
    std::string bottom;
    std::string front;
    std::string back;
};

class SkyBox {
public:
	SkyBox(const CubeFaces& faces);
	~SkyBox();

	void Bind(unsigned int slot = 0);
	void Unbind();
private:
	unsigned int m_TextureId;
};