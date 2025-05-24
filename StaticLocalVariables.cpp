#include <iostream>

/*
local variables have automatic duration by default meaning
they are created at point of definition and terminated
at the end of their block but if we put the "static" keyword
the duration changes to static duration meaning that variables
are created at the start of the program and terminated at the
end of the program regardless of their block. Unlike automatic
variables, static variables retain their value between function
calls. Note that "static" does not give local linkage when used
inside a function.
*/

void incrementAndPrint()
{
	int value{ 1 }; // automatic duration by default
	++value;
	std::cout << value << '\n';
} // value is destroyed here

void incrementAndPrintStatic()
{
	// recommended to name stativ varivables with  a s_ prefix like s_variable
	static int value{ 1 }; // staitc duration bc of static keyword
	// The initializer is only executed once
	++value;
	std::cout << value << '\n';
} // value not destroyed here bc its static so it remains it value until the end of program where it then is destroyed

int generateID()
{
	// most common way of using static is for ID generation with that each item gets its own unique ID everytime the function is called
	static int s_itemID{ 0 };
	return s_itemID++; // makes copy of s_itemID then increments s_itemID and returns the copy
}



/*
It's not recommended to use static local variables to alter
control flow (e.g., making decisions with if statements in a function)
because of their static duration. A static variable retains its value
between function calls, meaning it only affects the first iteration as expected,
but if the function is called again elsewhere, it may not work as intended.

In the example below, the first call works properly, but when we call it again
later, it still starts with "Enter another integer: " because the static bool
is still set to false from the first call.
*/

int getInteger()
{
	static bool s_isFirstCall{ true };

	if (s_isFirstCall)
	{
		std::cout << "Enter an integer: ";
		s_isFirstCall = false;
	}
	else
	{
		std::cout << "Enter another integer: ";
	}

	int i{};
	std::cin >> i;
	return i;
} // bad way of implementing that instead pass the bool the function e.g:

constexpr bool g_firstCall{ true }; // user can just pass this global variable for true or false and then its clear what its usage is

int getIntegerBetter(bool bFirstCall)
{
	if (bFirstCall)
	{
		std::cout << "Enter an integer: ";
	}
	else
	{
		std::cout << "Enter another integer: ";
	}

	int i{};
	std::cin >> i;
	return i;
}




int main()
{
	incrementAndPrint();  // prints 2
	incrementAndPrint();  // prints 2
	incrementAndPrint();  // prints 2

	incrementAndPrintStatic();  // prints 2
	incrementAndPrintStatic();  // prints 3
	incrementAndPrintStatic();  // prints 4

	incrementAndPrint();  // still prints 2 bc the value from this function is not the same variable as the other function regardless of their name and both values go out of scope once outside of the function regardless of static or not 
	incrementAndPrintStatic(); // prints 5

	// You can also make a static local variable const/constexpr but thats mainly used when you just wanna access/read the value and its too expensive to initialize every time the function is called
    

	// Works as intended
	std::cout << "Addition\n";
	int a{ getInteger() };
	int b{ getInteger() };
	std::cout << a << " + " << b << " = " << (a + b) << '\n';

	// Getting the number works but it doesnt start with Enter an integer, so it doesnt work as intended
	std::cout << "Subtraction\n";
	int c{ getInteger() };
	int d{ getInteger() };
	std::cout << c << " - " << d << " = " << (c - d) << '\n';

	// with that function the getInteger Function was improved and works as often as we want and works as intended
	int k{ getIntegerBetter(g_firstCall) };
	int l{ getIntegerBetter(!g_firstCall) };
	std::cout << k << " - " << l << " = " << (k - l) << '\n';
	
	// In conclusion const static local variables are fine to use but be aware of non const static local variables and if used makes sure that there is no reason to reset their value to make it work properly

	// small tip for for the getInteger function you also could have used std::string_view as a parameter instead of bool to make the user decide the next prompt making it even more reusable

	return 0;
}