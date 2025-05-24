#include <iostream>

void printInt(int x)
{
	std::cout << x << '\n';
}

void printDouble(double d)
{
	std::cout << d << '\n';
}

void printInt(int u)
{
	std::cout << u << '\n';
}

int main()
{
	// Through numeric promotion we can easily cover most integral types like int , double, short, or char
	printInt('2'); // prints 50 

	// The numeric promotions are divided in two subcategories integral promotion and floating point promotion

	//Floating point promotion is that a value of type float can be converted to a valueof type double:
	printDouble(5.0); //no conversion
	printDouble(4.0f); // numeric promotion of float to double

	
	/*
	Integral promotion rules:

	- signed char or signed short to int
	- unsigned char ,char8_t and unsigned short to int if int can hold the entirety of the range otherwise unsigned int
	- bool to int false = 0 and true = 1

	e.g:
	*/
	short s{3};
	printInt(s); // short to int
	 
	printInt('a'); // char to int

	printInt(true); // bool to int

	return 0;
}