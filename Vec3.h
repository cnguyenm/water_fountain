#pragma once
class Vec3
{
public:

	double x, y, z;
	Vec3();
	Vec3(double x, double y, double z);
	
	Vec3 operator + (Vec3 other);
	Vec3 operator - (Vec3 other);
	Vec3 operator * (double value);

	// get magnitude of vector
	double magn();
};

