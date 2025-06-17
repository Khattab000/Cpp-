#include <iostream>




/*
One big issues that structs have is that they dont have an effective way to enforce or document a class invariant which is a condition that must be true so that the object 
stays valid othewise it will lead to undefined behavior we normally use assert and static_assert to enforce those e.g:
*/

//first and second member can be independently set to any value so Pair has no invariant
struct Pair
{
	int first{};
	int second{};
};


struct Fraction
{
	int numerator{ 0 };
	int denominator{ 1 }; // class invariant bc denominator should never be 0 /making this default to 1 is a good start but i wont stop the user from making it 0 leading to an error
};


void printFractionValue(const Fraction& f)
{
	std::cout << f.numerator / f.denominator << '\n';
}


//to solve the invariant issues we use class which are similar to struct lets see how to define one :

class Employee
{
	int m_id{};  // we discuss in a later chapter their differences to structs and why we use m_ for their member names
	int m_age{};
	double m_wage{};
};
//now to show you how similar classes and structs are we gonna rewrite the date struct : e.g:
#if 0
struct Date
{
	int day{};
	int month{};
	int year{};
};
#endif 

class Date
{
public:  // we need the public so the members are in the global scope but we will cover public and private in a futrue lesson we call that access specifier
	int m_day{};  //added m_
	int m_month{};
	int m_year{};
};
//works basically the same as the version using struct we barely had to change the function
void printDate(const Date& d)
{
	std::cout << d.m_day << "/" << d.m_month << "/" << d.m_year << '\n';
}

int main()
{
	Date today{ 17,6,2025 };
	printDate(today);


#if 0
	Fraction frac{ 5,0 };
	printFractionValue(frac); // error bc divide by 0 
#endif 

	/*
	Question 1:
	struct minmax
	{
	  int min{};
	  int max{};
	};

	invariant here would be that min <= max but if it where to be initialized with a greater number than max that could lead to undefined behavior depending where its used 
	*/

	return 0;
}