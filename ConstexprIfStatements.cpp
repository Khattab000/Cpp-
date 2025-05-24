#include <iostream>

// normally the conditional of an if statement is evaluated in runtime but lets  consider using constexpr e.g
int main()
{
	constexpr double gravity{ 9.8 };

	if (gravity == 9.8) // reminder low precision floating point literals of the same type can be tested for equality
	{
		std::cout << "Gravity is normal\n";  // will always execute
	}
	else
	{
		std::cout << "We might have a slight problem...\n"; // will never execute
	}
	// doing that tho is useless and wastefull bc it always evaluates to the same so the if statement will never execute and it will only evaluate in run time

	// But there is smth called constexpr if statements which requires the conditional to be a constexpr and this conditional will be evaluated in compile time e.g

	if constexpr (gravity == 9.8)
	{
		std::cout << "Gravity is normal.\n";
	}
	else
	{
		std::cout << "We are not on earth.\n";
	}
	/*
	so with if constexpr the conditional is evaluated at compile time so if its true the whole statements is replace 
	by the true-statement and vice versa so it will compile like this:

	std::cout << "Gravity is normal.\n";  // this replaces the entire if statement

	So use if constexpr if the conditional is constexpr, some modern compilers might compile non if constexpr with
	constexpr conditional as if they where if constexpr or issue a warning to change it to if constexpr to be more 
	optimized and make sure its evaluated in compile time
	*/


	return 0;
}