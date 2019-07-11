#include "Vec3.h"

#include <math.h>

Vec3::Vec3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;

}

Vec3::Vec3(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3 Vec3::operator+(Vec3 other)
{
	Vec3 result;
	result.x = this->x + other.x;
	result.y = this->y + other.y;
	result.z = this->z + other.z;

	return result;
}

Vec3 Vec3::operator-(Vec3 other)
{
	Vec3 result;
	result.x = this->x - other.x;
	result.y = this->y - other.y;
	result.z = this->z - other.z;

	return result;
}

Vec3 Vec3::operator*(double value)
{
	Vec3 result;
	result.x = this->x * value;
	result.y = this->y * value;
	result.z = this->z * value;

	return result;
}

double Vec3::magn()
{
	return sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));
}

// a = Vec3()
// b = -a
Vec3 operator-(Vec3 other)
{
	return other * (-1);
}

Vec3 operator*(double v, Vec3 vec)
{
	return vec * v;
}
