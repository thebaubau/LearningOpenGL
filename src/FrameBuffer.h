#pragma once
#include <glad\glad.h>
#include "Texture.h"

class FrameBuffer
{
public:
	FrameBuffer(unsigned int width, unsigned int height);
	~FrameBuffer();

	void Bind();
	void Unbind();
private:
	unsigned int fboID;
	unsigned int rboID;
	unsigned int m_Width, m_Height;
	Texture *m_TextureColorbuffer;
};

