#include <iostream>

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