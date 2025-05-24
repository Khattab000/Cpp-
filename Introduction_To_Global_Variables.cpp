#include <iostream>

// its recommended to use a g_ prefix for global variables to avoid naming collision
int g_x{};  // You can define an global variable that is visible everywhere
//global variables are zero initialized by default unless given a value
namespace Foo
{
	int g_y{};   // the same works with namespaces and their funtion if defined as global now g_y can be seen and used everywhere
}            //this way is preffered so  rather put global variables in namespaces

// global variables can be constant too BUT its important to give them a value otherwise this results to an error e.g

// const int g_x; // error
// constexpr int g_x; // error

const int g_f{ 1 };
constexpr int g_l{ 2 };


// global variables have static duration meaning they are created before main executes and destroyed when it ends they are called static variables for that reason
void doSomething()
{
	g_x = 3;  // g_x can be seen and used everywhere
	Foo::g_y = 1;
	std::cout << g_x << Foo::g_y << '\n';
}

int main()
{
	doSomething();
	std::cout << g_x << Foo:: g_y << '\n';
	Foo::g_y = 9;
	g_x = 5;
	std::cout << g_x << Foo::g_y << '\n';

	return 0;
}
//g_x goes out of scope here 

// try to avoid non constant global variables
