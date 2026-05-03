#pragma once
#include <glad\glad.h>
#include "Texture.h"

class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();

	unsigned int fbo;

private:
	void Bind();
	void Unbind();

	Texture *textureColorbuffer;
};

