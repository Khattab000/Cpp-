#include <iostream>
#include "Point3d.h"
#include "Vector3d.h"  // full definition needed to access the members of Vector3d like v.m_x

Point3d::Point3d(double x, double y, double z)
	: m_x{ x }, m_y{ y }, m_z{ z }
{
}

void Point3d::print() const
{
	std::cout << "Point(" << m_x << ", " << m_y << ", " << m_z << ")\n";
}

void Point3d::moveByVector(const Vector3d& v)
{
	m_x += v.m_x;
	m_y += v.m_y;
	m_z += v.m_z;
}