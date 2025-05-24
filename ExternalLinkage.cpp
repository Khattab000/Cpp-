#include <iostream>
//this file is used with a.cpp


int g_x{ 2 }; // as stated earlier global non const variables have external linkage by default so no need for "extern"

// to make const/constexpr global variables have external linkage we use the "extern" keyword bc otherwise it defaults to internal linkage

extern const int g_y{ 3 }; // this now has external linkage 
extern constexpr int g_z{ 8 }; // this now has external linkage but this is pretty useless bc constexpr cant be forward declared bc the compiler needs to know the value at compile time othewise it leads to an error

// if you want to forward declare variables from another file with external linkage you need to use the "extern" keyword even for non const variables e.g

extern int g_j; // no value given bc its only a forward declaration / from a.cpp
extern const int g_l;

void sayHi(); // forward declaration can be used bc the function has external linkage

int main()
{

	sayHi();

	std::cout << g_j << ' ' << g_l << '\n';
	return 0;
}