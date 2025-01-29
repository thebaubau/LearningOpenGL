#include "Renderer.h"

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << function <<
			" " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

// TODO: Add const IndexBuffer& ib later
void Renderer::Draw(const VertexArray& va, const Shader& shader) const {
	va.Bind();
	//ib.Bind();

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Renderer::Clear() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
