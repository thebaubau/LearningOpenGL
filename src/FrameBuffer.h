#pragma once
#include <glad\glad.h>
#include "Texture.h"

class FrameBuffer
{
public:
	FrameBuffer(unsigned int width, unsigned int height, int samples = 1);
	~FrameBuffer();

	void Bind(unsigned int target = GL_FRAMEBUFFER);
	void Unbind();
	Texture& GetBufferTexture();
private:
	unsigned int fboID;
	unsigned int rboID;
	unsigned int m_Width, m_Height;
	Texture *m_TextureColorbuffer;
};

