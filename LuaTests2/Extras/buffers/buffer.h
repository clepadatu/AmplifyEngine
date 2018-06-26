#pragma once
#include <GL\glew.h>


	class Buffer
{
private:
	GLuint m_BufferID;
	GLuint m_ComponentCount;

public:
	Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
	Buffer ( GLfloat* data, GLsizei count, GLuint componentCount, int text );
	Buffer();
	~Buffer ();
	void bind() const;
	void unbind() const;

	inline GLuint getComponentCount() const{ return m_ComponentCount; };

	void AddBuffer_text(GLfloat* data, GLsizei count, GLuint componentCount);
};

