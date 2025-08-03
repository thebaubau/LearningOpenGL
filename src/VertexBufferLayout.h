#pragma once

#include "Renderer.h"
#include "Renderer.h"
#include <glad\glad.h>
#include <vector>

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type) {
		case GL_FLOAT:         return 4;
		case GL_UNSIGNED_INT:  return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
	unsigned int m_Offset; 

public:
	VertexBufferLayout() : m_Stride(0), m_Offset(0) {}
	~VertexBufferLayout() = default;

	template<typename T>
	void Push(unsigned int count, unsigned int offset) {
		std::runtime_error(false);
	}

	template<>
	void Push<float>(unsigned int count, unsigned int offset) {
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
		m_Offset = offset;
	}

	template<>
	void Push<unsigned int>(unsigned int count, unsigned int offset) {
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
		m_Offset = offset;
	}

	template<>
	void Push<unsigned char>(unsigned int count, unsigned int offset) {
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
		m_Offset = offset;
	}

	inline const std::vector<VertexBufferElement> GetElements() const& { return m_Elements; }

	inline unsigned int GetStride() const { return m_Stride; }
	inline unsigned int GetOffset() const { return m_Offset; }
};
