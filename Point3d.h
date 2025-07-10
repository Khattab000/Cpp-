#pragma once

class Vector3d; // only declaration needed for the reference of this class in the function parameter

class Point3d
{
private:
	double m_x{};
	double m_y{};
	double m_z{};

public:
	Point3d(double x, double y, double z);

	void print() const;


	void moveByVector(const Vector3d& v);
};