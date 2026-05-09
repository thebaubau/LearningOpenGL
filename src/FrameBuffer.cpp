#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(unsigned int width, unsigned int height, int samples)
	: m_Width(width), m_Height(height)
{
	glGenFramebuffers(1, &fboID);
	glBindFramebuffer(GL_FRAMEBUFFER, fboID);
	glGenRenderbuffers(1, &rboID);
	glBindRenderbuffer(GL_RENDERBUFFER, rboID);

	if (samples > 1) {
		m_TextureColorbuffer = new Texture(m_Width, m_Height, samples);
		m_TextureColorbuffer->Unbind();

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_TextureColorbuffer->GetRendererID(), 0);

		glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH24_STENCIL8, width, height);
	}
	else {
		m_TextureColorbuffer = new Texture(m_Width, m_Height);
		m_TextureColorbuffer->Unbind();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureColorbuffer->GetRendererID(), 0);

		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
	}

	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboID);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &fboID);
	glDeleteRenderbuffers(1, &rboID);
	delete m_TextureColorbuffer;
}

void FrameBuffer::Bind(unsigned int target)
{
	glBindFramebuffer(target, fboID);
}

void FrameBuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

Texture& FrameBuffer::GetBufferTexture()
{
	return *m_TextureColorbuffer;
}
