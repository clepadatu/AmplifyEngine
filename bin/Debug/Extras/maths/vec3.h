#pragma once
#include <iostream>

		struct vec3
		{
			float x, y, z;

			vec3();
			vec3(const float& x, const float& y,const float &z);

			vec3& add(const vec3& other);
			vec3& substract(const vec3& other);
			vec3& multiply(const vec3& other);
			vec3& divide(const vec3& other);

			friend vec3 operator+(vec3 left, const vec3& right);
			friend vec3 operator-(vec3 left, const vec3& right);
			friend vec3 operator*(vec3 left, const vec3& right);
			friend vec3 operator/(vec3 left, const vec3& right);

			vec3& operator+=(const vec3& other);
			vec3& operator-=(const vec3& other);
			vec3& operator*=(const vec3& other);
			vec3& operator/=(const vec3& other);

			bool operator==(const vec3& other);
			bool operator!=(const vec3& other);

			friend vec3 cross(  vec3 one,vec3 two);
			//vec3& normalise( vec3 one);
			friend vec3 normalize(vec3 ceva);
			friend float dot(vec3 one,vec3 two);

			friend std::ostream& operator<<(std::ostream& stream, const vec3& vector);

		};



