#pragma once
#include "Point3d.h" // the full definition needs to be here to declare Point3d::moveByVector() a friend 

class Vector3d
{
private:
	double m_x{};
	double m_y{};
	double m_z{};

public:
	Vector3d(double x, double y, double z);

	void print() const;

	friend void Point3d::moveByVector(const Vector3d& v);
};