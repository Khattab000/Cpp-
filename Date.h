#pragma once
//used with file Date.cpp and ClassesAndHeaderFiles.cpp

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
/*
You might wonder why we the ODR isnt violated by the member functions and the answer is bc member functions inside the class are implicitly inline so they are exempted of this rule
but member functions defined outside of the class are not implicitly inline but if you want to add them to this header file you could by explicitly using the inline keyword
making those member functions also inline this additionally makes them eligible for inline expansion e.g:
*/

#if 0

	inline Date::Date(int day, int month, int year)
		:m_day{day}
		,m_month{month}
		,m_year{year}
	{ }

	inline void Date::Date printDate() const
	{
		std::cout << m_day << "/" << m_month << "/" << m_year << '\n';
	}

#endif

/*
So you might be inclined to just put all in one header file either inside or outside the class using inline but there are some issues:
1. Defining many members in the class clutters up your class definition
2. Any changes to the code in the header may lead to big parts of the code needing to be recompiled which can make even more parts needing to recompile
  (lets say you need to change smth in Data.cpp this way only Data.cpp needs to be recompiled not most of the program)

But there are also some points to the contrary:
1. If its a small class that you intend to use in one file you can just define it and its member function in the same source file as the code and if you change your mind you
   can just move it to a header file without much issues
2. If the class only has a small amount of non trivial member function and which are unlikely to change its not worth making a cpp file for them instead make them inline 
   put it below the class in the header file
3. Modern C++ libraries increasingly are becoming header only meaning that all the code for the class or library is placed in a header file this makes distributing those files easier
   by only needing to include them in file you want to use it in.
4. For Template classes, template functions defined outised of the class are almost always defined inside the header file beneath the class definition bc the compiler needs to see
   the full template member functions definition to instantiate 


In a prior lesson we talked about default arguments and the best practice where we said if the function is forward declared put the default argument in there 
otherwise in the definition. But for member functions its simpler always put the default argument inside the class defintion.
*/