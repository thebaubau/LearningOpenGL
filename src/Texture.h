#pragma once
#include "Renderer.h"

class Texture {
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	std::string m_Type;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

public:
	Texture(const std::string& path, const std::string& type);
	~Texture();

	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

	Texture(Texture&& other) noexcept = default;
	Texture& operator=(Texture&& other) noexcept = default;

	void Bind(unsigned int slot = 0);
	void Unbind();

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline unsigned int GetRendererID() const { return m_RendererID; }
	inline const std::string& GetFilePath() const { return m_FilePath; }
	inline const std::string& GetType() const { return m_Type; }
};

