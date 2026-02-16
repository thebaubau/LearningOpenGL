#include "SkyBox.h"



Cubemap::Cubemap(const CubemapFaces& faces)
{
    glGenTextures(1, &m_TextureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureId);

    std::array<std::string, 6> faceArray = {
        faces.right, faces.left, faces.top,
        faces.bottom, faces.front, faces.back
    };

    int width, height, nrChannels;

    for (size_t i{ 0 }; i < faceArray.size(); i++) {
        unsigned char* data = stbi_load(faceArray[i].c_str(), &width, &height, &nrChannels, 0);

        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else {
            std::cout << "Cubemap texture failed to load: " << faceArray[i] << std::endl;
            stbi_image_free(data);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

Cubemap::~Cubemap() {
    glDeleteTextures(1, &m_TextureId);
}

void Cubemap::Bind(unsigned int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureId);
}

void Cubemap::Unbind() {
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}