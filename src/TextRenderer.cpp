#include "TextRenderer.h"

TextRenderer::TextRenderer(const std::string& path, int width, int height)
    : m_Width(width), m_Height(height)
{
    SetupFont(path);

    m_TextShader = std::make_unique<Shader>("res\\Shaders\\TextVertexShader.glsl", "res\\Shaders\\TextFragShader.glsl");
    m_TextShader->Bind();
    m_TextShader->SetMat4("projection", glm::ortho(0.0f, (float)m_Width, (float)m_Height, 0.0f));

    m_VAO = std::make_unique<VertexArray>();
    m_VBO = std::make_unique<VertexBuffer>(nullptr, sizeof(float) * 6 * 4);

    VertexBufferLayout layout;
    layout.Push<float>(2, 0);
    layout.Push<float>(2, 0);

    m_VAO->AddBuffer(*m_VBO, layout);
}

TextRenderer::~TextRenderer()
{

}

void TextRenderer::SetupFont(const std::string& path)
{
    FT_Library m_Ft;
    FT_Face m_Face;

    if (FT_Init_FreeType(&m_Ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }

    if (FT_New_Face(m_Ft, path.c_str(), 0, &m_Face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }

    if (FT_Load_Char(m_Face, 'X', FT_LOAD_RENDER))
    {
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
    }

    FT_Set_Pixel_Sizes(m_Face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph 
        if (FT_Load_Char(m_Face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }

        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            m_Face->glyph->bitmap.width,
            m_Face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            m_Face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(m_Face->glyph->bitmap.width, m_Face->glyph->bitmap.rows),
            glm::ivec2(m_Face->glyph->bitmap_left, m_Face->glyph->bitmap_top),
            m_Face->glyph->advance.x
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }

    FT_Done_Face(m_Face);
    FT_Done_FreeType(m_Ft);
}

void TextRenderer::RenderText(std::string text, float x, float y, float scale, glm::vec3 color)
{
    // activate corresponding render state	
    m_TextShader->Bind();
    m_TextShader->SetVec3("textColor", glm::vec3(color.x, color.y, color.z));

    glActiveTexture(GL_TEXTURE0);
    
    m_VAO->Bind();

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y + (this->Characters['H'].Bearing.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f },
            { xpos,     ypos,       0.0f, 0.0f },

            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f }
        };

        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);

        // update content of VBO memory
        m_VBO->Bind();
        //glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        m_VBO->Unbind();
        //glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

float TextRenderer::GetTextWidth(const std::string& text, float scale)
{
    float width = 0.0f;
    for (auto c = text.begin(); c != text.end(); c++)
        width += (Characters[*c].Advance >> 6) * scale;
    return width;
}

