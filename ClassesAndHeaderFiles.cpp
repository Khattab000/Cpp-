#include <iostream>
#include "Date.h"

//used with files Date.h and Date.cpp

#if 0
class Date
{
	int m_day{};
	int m_month{};
	int m_year{};

public:
	Date(int day, int month, int year)
		:m_day{ day }
		, m_month{ month }
		, m_year{ year }
	{ }

	void printDate() const
	{
		std::cout << m_day << "/" << m_month << "/" << m_year << '\n';
	}
	
	int getDay() const
	{
		return m_day;
	}

	int getMonth() const
	{
		return m_month;
	}

	int getYear() const 
	{
		return m_year;
	}

};
#endif
/*
Looking at the Date class above it looks a bit cluttered and normally the most important thing is understanding the public interface, to make it less cluttered C++ allows us 
to forward declare member functions and write them ouside of the class e.g:
*/
#if 0 // we disabled this because we moved the class  Date to the file Date.h (we should name the file the same as the class) and included it here this way multiple files can use the class Date
class Date
{
	int m_day{};
	int m_month{};
	int m_year{};

public:
	Date(int day, int month, int year); //forward declared the constructor

	void printDate() const;

	int getDay() const
	{
		return m_day;
	}

	int getMonth() const
	{
		return m_month;
	}

	int getYear() const
	{
		return m_year;
	}

};
#endif
#if 0  //Disabled and moved to Date.cpp put non trivial functions that you want outside of class not in the same header file but in a cpp file with the same name (doesnt need to be included)
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
#endif
/*
Also as a quick reminder you can also add classes to a header files and include that header file to other files so you can use the class in multiple files but as we stated
already unlike normal functions where forward declaring is enough, this is not enough for a class we need the full definition to be visible to be used (and again classes dont need
to abide to ODR)
*/


int main()
{
	Date today{ 30,6,2025 };
	today.printDate(); //still works even tho the member function is defined outside of the class


	return 0;
}