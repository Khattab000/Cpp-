#include <iostream>
// this file is used with a.cpp

//Linkage is there to check if an identifier was already defined somewhere else local variables don't have that bc they only exist on a certain scope but global variables do 
//There is internal and external linkage here we gonna cover internal which makes that this global variable cant be seen outside of its source file making it okey to use the same identifier in another source file 

//To make a global variable with internal linkage we use the "static" keyword e.g

static int g_x{};  // non const global variables have external linkage by default so we need to use static to make it internal linkage /only visbile in this file 
const int g_y{ 6 }; // const global variables have internal linkage by default so no need for static keyword
constexpr int g_z{ 9 }; // constexpr global variable also have internal linkage by default

int add(int x, int y); // forward declaration for function add but it wont link bc the function is an internal function

int main()
{
	std::cout << g_x << g_y << g_z << '\n'; 
	std::cout << add(6, 8) << '\n';    // wont link bc its internal
	return 0;
}

// Conclusion use static on variables/functions when you have an explicit reason to disallow access from other files