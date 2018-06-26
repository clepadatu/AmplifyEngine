#include "indexbuffer.h"

		IndexBuffer::IndexBuffer(GLushort* data, GLsizei count)
			: m_Count(count)
		{
			glGenBuffers(1, &m_BufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count *sizeof(GLushort), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		IndexBuffer::IndexBuffer()
		{
			glGenBuffers(1, &m_BufferID);
		}
	IndexBuffer::~IndexBuffer ()
		{}
		void IndexBuffer::bind()const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
		}


		void IndexBuffer::unbind()const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		void IndexBuffer::set_properties(GLushort* data, GLsizei count)
		{
			m_Count = count;
			
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count *sizeof(GLushort), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void IndexBuffer::set_properties_dynamic(GLushort* data, GLsizei count)
		{
			m_Count = count;

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count *sizeof(GLushort), data, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}