#include <iostream>


/*
In this lesson we will cover access functions which are public member function which have one of the purposes, either get the information of a private member or set the information 
of a private member we also call them getter or setter
*/


class Date
{
	int m_day{ 13 };
	int m_month{ 6 };
	int m_year{ 2025 };

public:

	int getDay() const    // getter (or also called accesor) access function for m_day
	{
		return m_day;
	}
	void setDay(int x)   // setter (or also called mutator) access function for m_day
	{
		m_day = x;
	}

	int  getMonth() const
	{
		return m_month;
	}
	void setMonth(int x)
	{
		m_month = x;
	}

	int getYear() const
	{
		return m_year;
	}
	void setYear(int x)
	{
		m_year = x;
	}

	void printDate() const
	{
		std::cout << m_day << "/" << m_month << "/" << m_year << '\n';
	}
};

/*
When it comes to naming conventions of access functions you should prefer using a prefix like for the setter and the getter setDay or getDay respectively making it clear 
what it exactly is being done.

Also getters should return their information by either value (if inexpensive) or by const lvalue reference bc returning the data member with a getter should only provide 
a read only access so to not modify anything.
*/




int main()
{

	Date today{};
	today.printDate();

	today.setYear(2026);
	std::cout << "The year is " << today.getYear() << ".\n";

	return 0;
}