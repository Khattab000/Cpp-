#include <iostream>

void someFcn(int i)
{

}

void print(unsigned int u)
{
	std::cout << u << '\n';
}

int main()
{
	double d{ 5.0 };
	someFcn(d); // bad implicit narrowing conversion generates warning 
	someFcn(static_cast<int>(d)); // explicit conversion doesnt generate warning
	//try to always use explicit instead of implicit narrowing conversion 


	//brace initialization disallows narrowing conversion so you also need static_cast<>() e.g
#if 0
	int i{ 3.5 }; //this wont compile
#endif
	int i{ static_cast<int>(3.5) }; // this compiles
	std::cout << i << '\n';


	std::cout << "Enter an integral value: ";
	int n{};
	std::cin >> n; // compiler doesnt know yet if there is a narrowing conversion so for this case regardless of what happens it issues a warning
	print(n);


	/*
	in case of constexpr values its a bit diffrent the way it works
	is that if the compiler detects a narrowing conversion from an 
	constexpr value then it halts the compilation if no narrowing 
	is happening then its fine e.g
	*/

	constexpr int n1{ 5 };
	unsigned int u1{ n1 }; //no narrowing so this fine
#if 0
	constexpr int n2{ -5 };
	unsigned int u2{ n2 }; //narrowing conversion, compilation is halted
#endif

	//but floating point types to integral types are exluded of the special constexpr rule so regardless of data loss or not it is consideder narrowed conversion e.g:
#if 0
	int n{ 5.0 }; //compile error
#endif
	//but strangely enough conversion between floating point to another narrower floatin typ is not considered narrowing conversion even with a loss of precision
	constexpr double d1{ 0.1 };
	float f1{ d1 }; //compiles not considered narrowing conversion


	// All those constexpr rules help us use literals to avoid using literal suffixes and static_cast e.g:

	unsigned int u3{ 5 }; //we dont need 5u
	float f3{ 1.5 }; // we dont need 1.5f

	constexpr int n3{ 5 };
	double d3{ n3 }; // no need for static cast
	short s3{ 5 }; // there isnt a suffix for it and we dont need static_cast


	float f4{ 1.23456789 }; // even tho precision is lost here it wont emit an warning
	std::cout << f4 << '\n';
	return 0;
}