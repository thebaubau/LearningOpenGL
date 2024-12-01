#include "VertexArray.h"
#include <glad\glad.h>

VertexArray::VertexArray() {
	// Generate and store VAO in ID
	glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_RendererID);
}

// Link vertex attributes -> Setup attrib pointer for firstTriangle at index 0 (location = 0 in Shader)
void VertexArray::AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout) {
	Bind();
	vbo.Bind();

	const auto& elements = layout.GetElements();
	unsigned int offset{ 0 };

	for (unsigned int i{ 0 }; i < elements.size(); i++) {
		const auto& element = elements[i];

		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type,
			element.normalized, layout.GetStride(), (const void*)offset);

		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

// Binds VAO. Any calls after this will be stored in the VAO specified.
void VertexArray::Bind() const {
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const {
	glBindVertexArray(0);

}
