#pragma once

#include <OGL1/Renderer/Renderer.h>


class Textures
{
private:
	unsigned int  m_RendererID;
	unsigned char* m_LocalBuffer;

	std::string m_FilePath;

	int m_Width;
	int m_Height;
	int m_BPP;

public:
	Textures(const std::string& path);
	~Textures();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};