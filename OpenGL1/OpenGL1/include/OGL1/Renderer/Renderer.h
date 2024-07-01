#pragma once

#include <GL/glew.h>

#include <OGL1/VertexArray/VertexArray.h>
#include <OGL1/IndexBuffer/IndexBuffer.h>
#include <OGL1/Shaders/Shaders.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);


class Renderer 
{
private:

public:
	void Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shaders& shader) const;
	void Clear() const;

};