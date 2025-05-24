#include <iostream>

int g_x{ 5 };


int main()
{
	// we discussed earlier that a non const lvalue reference cant bind to an unmodifiable object in this case we just give the reference also the const keyword e.g:
	const int x{ 5 };     // x is an unmodifiable/non modifiable lvalue
	const int& ref{ x };  // reff is an const lvalue reference so this is fine / int& ref would be not valid we need the const

	std::cout << ref << '\n'; // no problems with accessing it
#if 0
	ref = 6; // error bc this is a const lvalue reference and const cant be modified
#endif
	// btw we can also bind a const lvalue reference to an modifiable object e.g:
	int y{ 8 };
	const int& ref2{ y };   // this is allowed even if the object isnt const
	std::cout << ref2 << '\n'; // as usual
#if 0
	ref2 = 9;  // still an error surprisingly even tho the object itself is modifiable it cant be modified through a const lvalue reference
#endif
	y = 9; // this is fine just not possible through the const reference
	/*
	In general you should prefer using lvalue refernces to const (const int&)to lvalue reference to non const (int&)unless the value needs to be changed 
	bc its much more versatile and can be used with rvalue, const value and non const values instead of just with only non const value
	*/

	//Lets see what happens when we use a const lvalue to reference an rvalue (this isnt possible with non const lvalue references)

	const int& ref3{ 5 };  // surprisingly it works in this case a temporary object is created and bound to ref3
	std::cout << ref3 << '\n'; // prints 5

	// Here some cases what happens when we use different types that dont quite match with const lvalue reference 
	const double& r1{ 5 }; // temporary double initialized with 5 
	std::cout << r1 << '\n';

	char c{ 'a' };
	const int& r2{ c }; // temporary int initialized with value 'a' / temporary bc the conversion results to an rvalue
	std::cout << r2 << '\n'; // prints 97 since r2 is a reference to an int
	/*
	BUT be careful on this regards there is smth very important bc in the cases where it references the temporary object changes to the original object dont reflect on the
	reference and changes made to the reference dont reflect on the original object bc the reference is merely referencing an temporary object e.g:
	*/

	short bombs{ 1 };    

	const int& you{ bombs };  //bc the type difference you is referencing a temporary object of the original object bombs
	--bombs;    // changes the original object but not the temporary one or the reference you

	if (you)  // this executes surprisingly bc as stated before the reference was not changed so its still 1 even tho the original object changed to 0 
	{
		std::cout << "Bombs away! Goodbye,cruel world.\n";
	}



	// Const references bound to temporary objects extend the lifetime of the temporary objects which normally are destroyed at the end of an expression now their liftime is matched the lifetime of the reference e.g;

	const int& refto5{ 5 };  // temporary object holding 5 has the same lifetime as the reference /only works tho bc the temporary object is BOUND to the reference otherwise no lifetime expansion
	std::cout << refto5 << '\n'; // so the temporary object holding 5 is usable here


	//now lastly lets talk about constexpr with lvalue reference which can only bind with static or global variables e.g: 
	constexpr int& refg{ g_x }; // okay can bind to gloabal
	static int s_x{ 6 };
	constexpr int& refs{ s_x }; // okay can bind to static
	static const int s_y{ 17 };
	constexpr const int& refsy {s_y };  // okay can bind to static const but it need constexpr and const bc constexpr applies to the reference saying that the reference is in compile time and const to the type of the reference

	int j{ 7 };
#if 0
	constexpr int& refi{ j };  // compile error cant bind to non static object /bc adress isnt known in compile time its is known in run time instead
#endif
	// The reason this works like this bc the compiler knows where static/global objects will be instantiated in memory so it can treat that adress as a compile time constants
	//but due to the limitations its not recommended to use constexpr references 
	
	return 0;
} // both refto5 and the temporary object holding 5 die here