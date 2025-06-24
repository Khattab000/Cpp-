#include <iostream>
#include <string>
#include <string_view>
#include "printString.h"

//In this lesson we talk about temporary class objects 

class IntPair
{
	int m_x{};
	int m_y{};
public:
	IntPair(int x, int y)
		:m_x{ x }
		, m_y{ y }
	{}

	int getX() const
	{
		return m_x;
	}
	int getY() const
	{
		return m_y;
	}
};

void printIntPair(const IntPair& p)
{
	std::cout << "(" << p.getX() << ", " << p.getY() << ")\n";
}

//now lets look at different way of returning a temporary class object
//Case1: create a named variable and return
IntPair ret1()
{
	IntPair p{ 3,4 };
	return p;
}
//Case2: Create a temporary IntPair and return
IntPair ret2()
{
	return IntPair{ 3,4 };
}
//Case3: Implicitly convert a temporary object to IntPair and return
IntPair ret3()
{
	return { 3,4 };
}

int main()
{
	//Case 1 pass variable
	IntPair p1{ 3,4 }; //creatgin the variable p1 only so its used once is kinda redundand if the function also takes rvalues so lets try to pass a temporary class object to the function
	printIntPair(p1);

	//Case 2 construct temporary IntPair and pass to function
	printIntPair(IntPair{ 3,4 }); // temporary object by using type{} this only exist for the duration of one expression

	//Case 3 Implicitly convert a temporary object by passing it to the function
	printIntPair({ 3,4 }); //implicitly converts {3,4} to the IntPair class type depending on the function parameter 

	printIntPair(ret1());
	printIntPair(ret3());
	printIntPair(ret2());


	/*
	In case we want to convert a value from one type to another where no narrowing conversions are invovlved, we can use static cast or 
	explicit instantation of a temporary object e.g:
	*/
	char c{ 'a'};
	std::cout << static_cast<int>(c) << '\n'; //used static_cast<int>() to create a temporary int object through direct initialization with the value of c
	std::cout << int{ c } << '\n';            //explicitly creates a temporary int list initialized with value of c
	//now a bit of a harder example 
	std::string_view sv{ "Hello" };
#if 0
	printString(sv); //compile error bc string_view wont implicitly convert to string
#endif
	printString(static_cast<std::string>(sv)); // this works with static_cast creating a temporary std::string object direct initialized
	printString(std::string{ sv });            // this works explicitly creates a temporary std::string object list initialized
	printString(std::string(sv));              // C-Style cast return temporary std::string object direct initialized /avoid this method

	/*
	Conclusion: Prefer static_cast when converting fundemental type and list initialized temporary when converting class type.
	static_cast when:
	-we need narrowing conversion
	-make it rly obvious that we are converting to  a type that will result in some different behavior
	-we want to use direct initialization for some reason (e.g avoid list constructors taking precedence

	list initialized temporary when:
	-we want to use list initialization (e.g protection against narrowing conversion or we need to invoke a list constructor)
	-we need to provide additional arguments to a constructor to facilitate the conversion
	(btw list constructor is just a constructor that you can invoke by using list initialization but we will cover those in a later chapter)
	*/
	return 0;
}