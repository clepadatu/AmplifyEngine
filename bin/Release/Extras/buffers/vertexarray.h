#pragma once

#include <GL\glew.h>
#include "buffer.h"
#include <vector>

		class VertexArray
		{
		private:
			GLuint m_ArrayID;
			std::vector<Buffer*> m_Buffers;
			Buffer* test;
		public:
			VertexArray();
			~VertexArray();
			void addBuffer(Buffer* buffer, GLuint index);
			void addBuffer_text(Buffer* buffer, GLuint index);
			void bind() const;
			void unbind() const;
			void testbind ();
			void testunbind ();
		};

