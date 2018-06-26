#pragma once
#include <vector>
#include <iostream>
#include "../fileutils.h"
#include <GL/glew.h>
#include "../maths/maths.h"

		class Shader
		{
		private:
			GLuint m_ShaderID;
			const char* m_VertPath, *m_FragPath;

		public: 
			//Shader(const char* vertPath, const char* fragPath);
			Shader();
			~Shader();


			void setUniform1f(const GLchar* name, float value);
			void setUniform1i(const GLchar* name, int value);
			void setUniform2f(const GLchar* name, const vec2& vector);
			void setUniform3f(const GLchar* name, const vec3& vector);
			void setUniform4f(const GLchar* name, const vec4& vector);
			void setUniformMat4(const GLchar* name, const mat4& matrix);




			void Initialise_shader(const char* vertPath, const char* fragPath);
			void enable() const;
			void disable() const;

		public:
			GLint getUniformLocation(const GLchar* name);
			GLuint load();
		};
