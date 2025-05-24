#include <iostream>

namespace constants
{
	constexpr int minRideHeightCM{ 140 };
}

// use this  if you only want the first true to be executed
void ifelse(bool a, bool b, bool c)
{
	if (a)  // always evaluates (doesnt mean it executes tho)
	{
		std::cout << "a";
	}
	else if (b) // only evaluates when prior statement is false
	{
		std::cout << "b";
	}
	else if (c) // only evaluates when prior statement is false
	{
		std::cout << "c";
	}
	std::cout << '\n';
}

// use this to check everything and every true be executed
void ifif(bool a, bool b, bool c)
{
	if (a)  // always evaluates
	{
		std::cout << "a";
	}
	if (b)  // always evaluates
	{
		std::cout << "b";
	}
	if (c)  // always evaluates
	{
		std::cout << "c";
	}
	std::cout << '\n';
}


char getFirstMatchingChar(bool a, bool b, bool c)
{
	/*
	even tho we want it to stop evaluating after the first true we 
	still use  if-if bc by adding return to each if statement else if becomes obsolete in this case
	*/
	if (a) // always evaluates
	{
		return 'a';
	}
	
	if (b)
	{
		return 'b';
	}
	if (c)
	{
		return 'c';
	}
}


// first category of control flow is conditional statements
int main()
{
	std::cout << "Enter your height (in cm): ";
	int height{};
	std::cin >> height;

	if (height >= constants::minRideHeightCM)
	{ 
		std::cout << "You are tall enough to ride.\n";
	}
	else
	{
		std::cout << "You are not tall enough to ride.\n";
		std::cout << "Too bad!\n";
	} // always use blocks to make sure that the statements arent always run only when condition is met
#if 0
	if (true)
	{
		int x{ 5 };
	} // x is destroyed here
	else
	{
		int x{ 6 };
	} // x is destroyed here
	std::cout << x << '\n'; // no x defined
	// wont compile bc x isnt defined so dont define variables in if statement if you need them outside
#endif

	ifelse(false, true, true);
	ifif(false, true, true);


	// In conlusion if you want all to evaluate then use if-if but if you want only the true one then use else if unless each if statement has a return then else if is not needed

	return 0;
}