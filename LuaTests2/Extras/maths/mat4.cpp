#include "mat4.h"


		//TOOL-angle to radians
		float toRadians(float degrees)
		{
			return degrees * (M_PI / 180.0f);
		}


		mat4::mat4()
		{
			for (int i = 0; i < 4 * 4; i++)
				elements[i] = 0.0f;
		}

		mat4::mat4(float diagonal)
		{
			for (int i = 0; i < 4 * 4; i++)
				elements[i] = 0.0f;
			elements[0 + 0 * 4] = diagonal;
			elements[1 + 1 * 4] = diagonal;
			elements[2 + 2 * 4] = diagonal;
			elements[3 + 3 * 4] = diagonal;
		}

		mat4 mat4::identity()
		{
			return mat4(1.0f);
		}

		mat4& mat4::multiply(const mat4& other)
		{
			for (int y = 0; y < 4; y++)
			{	
				
				for (int x = 0; x < 4; x++)
				{
					float sum = 0.0f;
					for (int e = 0; e < 4; e++)
					{
						sum += elements[x + e * 4] * other.elements[e + y * 4];
					}
					elements[x + y * 4] = sum;

				}
			}
			return *this;
		}

		mat4 operator*(mat4 left, const mat4& right)
		{
			return left.multiply(right);
		}
		mat4& mat4::operator*=(const mat4& other)
		{
			return multiply(other);
		}

		mat4 mat4::ortographic(float left, float right, float top, float bottom, float near, float far)
		{
			mat4 result(1.0f);
			result.elements[0 + 0 * 4] = 2.0f / (right - left);
			result.elements[1 + 1 * 4] = 2.0f / (top-bottom);
			result.elements[2 + 2 * 4] = 2.0f / (near-far);

			result.elements[0 + 3 * 4] = (left+right)/(left-right);
			result.elements[1 + 3 * 4] = (bottom+top) / (bottom-top);
			result.elements[2 + 3 * 4] = (far+near) / (far-near);

			return result;


		}
		mat4 mat4::perspective(float fov, float aspectRatio, float near, float far)
		{
			mat4 result(1.0f);
			/*float q = 1.0f / tan(toRadians(0.5f*fov));
			float a = q / aspectRatio;
			float b = (near + far) / (near - far);
			float c = (2.0f*near*far) / (near - far);
			result.elements[0 + 0 * 4] = a;
			result.elements[1 + 1 * 4] = q;1
			result.elements[2 + 2 * 4] = b;
			result.elements[3 + 2 * 4] = -1.0f;
			result.elements[2 + 3 * 4] = c;
			*/
			float top = near*tan(toRadians(fov / 2));
			float bottom = -top;
			float right = top*aspectRatio;
			float left = -right;
		/*	result.elements[0 + 0 * 4] = (2 * near) / (right-left);
			result.elements[1 + 1 * 4] = (2 * near) / (top-bottom);
			result.elements[2 + 2 * 4] = -((far + near) / (far-near));
			result.elements[2 + 3 * 4] = -2*(far*near)/(far-near);
			result.elements[3 + 2 * 4] = 1;
			result.elements[3 + 3 * 4] = 0;
			result.elements[0 + 2 * 4] = (right + left) / (right - left);
			result.elements[1 + 2 * 4] = (top + bottom) / (top - bottom);
			*/
			/*result.elements[0 + 0 * 4] = (2 * near) / (right - left);
			result.elements[1 + 1 * 4] = (2 * near) / (top - bottom);
			result.elements[2 + 2 * 4] = ((far + near) / (far - near));
			result.elements[3 + 2 * 4] = -1;
			result.elements[3 + 3 * 4] = 0;
			result.elements[2 + 3 * 4] = -2*(far*near)/(far-near);*/
			result.elements[0 + 0 * 4] = 1/((tan(fov/2)*aspectRatio));
			result.elements[1 + 1 * 4] = 1 / (tan(fov / 2));
			result.elements[2 + 2 * 4] = (far+near)/(far-near);
			result.elements[3 + 2 * 4] = -1;
			result.elements[2 + 3 * 4] = -(2*near*far) / (far - near);
			result.elements[3 + 3 * 4] = 0;
			return result;
		}

		mat4 mat4::translation(const vec3& translation)
		{
			mat4 result(1.0f);
			result.elements[0 + 3 * 4] = translation.x;
			result.elements[1 + 3 * 4] = translation.y;
			result.elements[2 + 3 * 4] = translation.z;

			return result;
		}

		mat4 mat4::scale(const vec3& scale)
		{
			mat4 result(1.0f);
			result.elements[0 + 0 * 4] = scale.x;
			result.elements[1 + 1 * 4] = scale.z;
			result.elements[2 + 2 * 4] = scale.y;

			return result;
		}

		mat4 mat4::rotation(float angle, const vec3& axis)
		{
			mat4 result(1.0f);
			float r = toRadians(angle);
			float c = cos(r);
			float s = sin(r);
			float omc = 1.0f - c;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			result.elements[0 + 0 * 4] = x*omc + c;
			result.elements[1 + 0 * 4] = y*x*omc + z*s;
			result.elements[2 + 0 * 4] = x*z*omc - y*s;
			

			result.elements[0 + 1 * 4] = x*y*omc - z*s;
			result.elements[1 + 1 * 4] = y*omc + c;
			result.elements[2 + 1 * 4] = y*z*omc+x*s;

			result.elements[0 + 2 * 4] = x*z*omc + y*s;
			result.elements[1 + 2 * 4] = y*z*omc - x*s;
			result.elements[2 + 2 * 4] = z*omc+c;

			return result;
		}



		mat4 mat4::lookAt(const vec3& eye, const vec3& center, const vec3& up)
		{
			
			/*
			vec3 t1 = operator-(center, eye);
			std::cout << "lookat t1= " << t1 << std::endl;
			vec3 f = normalize(t1);
			std::cout << "lookat f= " << f << std::endl;


			vec3 u = normalize(up);
			std::cout << "lookat u1= " << u << std::endl;

			vec3 t2 = cross(f,u);
			std::cout << "lookat t2= " << t2 << std::endl;
			vec3 s = normalize(t2);
			std::cout << "lookat s= " << s << std::endl;


			
			u = cross(f,u);
			std::cout << "lookat u2= " << u << std::endl;
			*/

			vec3 f = normalize(operator-(center,eye));
			std::cout << "F= " << f << std::endl;
			vec3 s = normalize(cross(f,up));
			std::cout << "S= " << s << std::endl;
			vec3 u = cross(s, f);
			std::cout << "U= " << u << std::endl;
						
			mat4 result(0.0f);
			result.elements[0 + 0 * 4] = s.x;
			result.elements[0 + 1 * 4] = s.y;
			result.elements[0 + 2 * 4] = s.z;
			result.elements[1 + 0 * 4] = u.x;
			result.elements[1 + 1 * 4] = u.y;
			result.elements[1 + 2 * 4] = u.z;
			result.elements[2 + 0 * 4] = -f.x;
			result.elements[2 + 1 * 4] = -f.y;
			result.elements[2 + 2 * 4] = -f.z;
			result.elements[0 + 3 * 4] = -dot(s, eye);
			result.elements[1 + 3 * 4] = -dot(u, eye);
			result.elements[2 + 3 * 4] = dot(f, eye);
			/*result.elements[0 + 0 * 4] = s.x;
			result.elements[0 + 1 * 4] = s.y;
			result.elements[0 + 2 * 4] = s.z;
			result.elements[1 + 0 * 4] = u.x;
			result.elements[1 + 1 * 4] = u.y;
			result.elements[1 + 2 * 4] = u.z;
			result.elements[2 + 0 * 4] = -f.x;
			result.elements[2 + 1 * 4] = -f.y;
			result.elements[2 + 2 * 4] = -f.z;*/



			/*v2
			result.elements[0+0*4] = s.x;
			result.elements[1 + 0 * 4] = s.y;
			result.elements[2 + 0 * 4] = s.z;
			result.elements[0 + 1 * 4] = u.x;
			result.elements[1 + 1 * 4] = u.y;
			result.elements[2 + 1 * 4] = u.z;
			result.elements[0 + 2 * 4] = -f.x;
			result.elements[1 + 2 * 4] = -f.y;
			result.elements[2 + 2 * 4] = -f.z;*/
			return result;
		}


	


