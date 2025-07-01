#include <iostream>
#include "Date.h"
//used with ClassesAndHeaderFiles.cpp

Date::Date(int day, int month, int year) //Date:: needed to show the compiler that we are defining a member function for the class Date
	:m_day{ day }
	, m_month{ month }
	, m_year{ year }
{
}

void Date::printDate() const //the type (void) before Date::
{
	std::cout << m_day << "/" << m_month << "/" << m_year << '\n';
}