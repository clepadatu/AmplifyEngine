#include "vec3.h"


		vec3::vec3()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}

		vec3::vec3(const float& x, const float& y,const float& z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		vec3& vec3::add(const vec3& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;

			return *this;
		}

		vec3& vec3::substract(const vec3& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			
			return *this;
		}

		vec3& vec3::multiply(const vec3& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;

			return *this;
		}

		vec3& vec3::divide(const vec3& other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;

			return *this;
		}

		vec3 operator+(vec3 left, const vec3& right)
		{
			return left.add(right);
		}
		
		vec3 operator-(vec3 left, const vec3& right)
		{
			return left.substract(right);
		}

		vec3 operator*(vec3 left, const vec3& right)
		{
			return left.multiply(right);
		}

		vec3 operator/(vec3 left, const vec3& right)
		{
			return left.divide(right);
		}
		
		vec3& vec3::operator+=(const vec3& other)
		{
			return add(other);
		}

		vec3& vec3::operator-=(const vec3& other)
		{
			return substract(other);
		}

		vec3& vec3::operator*=(const vec3& other)
		{
			return multiply(other);
		}

		vec3& vec3::operator/=(const vec3& other)
		{
			return divide(other);
		}

		bool vec3::operator==(const vec3& other)
		{
			return x == other.x && y == other.y && z==other.z;

		}

		bool vec3::operator!=(const vec3& other)
		{
			return !(*this==other);
			
		}

		std::ostream& operator<<(std::ostream& stream, const vec3& vector)
		{
			stream << "vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
			return stream;
		}

		vec3 cross( vec3 one,vec3 two)
		{
			vec3 result;
			result.x = one.y*two.z - one.z*two.y;
			result.y =one.z*two.x - one.x*two.z;
			result.z = one.x*two.y - one.y*two.x;
			return result;
		}

	/*	vec3& vec3::normalise( vec3 one)
		{
			
			
			float s;
			s = sqrt(int(one.x) ^ 2 + int(one.y) ^ 2 + int(one.z) ^ 2);
			this->x /= s;
			this->y /= s;
			this->z /= s;
			return *this;
		}
*/
		vec3 normalize(vec3 ceva)
		{
			float s=0.0f;
			s = sqrtf(ceva.x*ceva.x + ceva.y*ceva.y +ceva.z*ceva.z);
			std::cout << "sqrt= " << s << std::endl;
			ceva.x /= s;
			ceva.y /= s;
			ceva.z /= s;
			return ceva;
		}

		float dot(vec3 one, vec3 two)
		{
			float result;
			result = one.x*two.x + one.y*two.y+one.z*two.z;
			return result;
		}

