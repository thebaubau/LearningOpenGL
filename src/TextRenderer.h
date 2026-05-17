#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Texture.h"
#include "VertexBufferLayout.h"

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

class TextRenderer
{
public:
	TextRenderer(const std::string& path, int width, int height);
    ~TextRenderer();

    void SetupFont(const std::string& path);
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);
    float GetTextWidth(const std::string& text, float scale);

    std::map<char, Character> Characters;

    std::unique_ptr<Shader> m_TextShader;
    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<VertexBuffer> m_VBO;

private:
    unsigned int m_Width = 1280;
    unsigned int m_Height = 920;
};

