#pragma once
#include <GL\glew.h>

		class IndexBuffer
		{
		private:
			GLuint m_BufferID;
			GLuint m_Count;

		public:
			IndexBuffer(GLushort* data, GLsizei count);
			IndexBuffer();
			~IndexBuffer ();
			void bind() const;
			void unbind() const;
			inline GLuint getCount() const{ return m_Count; };
			void set_properties(GLushort* data, GLsizei count);
			void set_properties_dynamic(GLushort* data, GLsizei count);
		};

