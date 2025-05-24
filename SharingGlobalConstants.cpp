#include <iostream>
#include "constants.h"
//this files is used with constants.cpp and constants.h



/*
There are multiple ways to share constants across files

First way is global constants as internal variables so we create
a header file with all the constants put in a namespace and then include that header file to use the namespace and make them constexpr
This Way is good if you wanna use constexpr but the disadvantage is changing anything in the header file mean recompiling everything that uses it and everyone gets their own copy which is not rly good

Second Way is making global constants as external variables in this case you put the constants in another .cpp file and forward declare them through a header file
in this case you can still have the the constants constexpr but need to use the "extern" keyword to make it visible outside of the file
and in the header file you need to the same bc if you forward declare a variable you need to use the extern keyword. But keep in mind
as we discussed in an earlier chapter you cant forward declare constexpr , but in this case you can const in the forward declaration 
this works with constexpr variables.
Advantage of that is that now not every file using it gets a copy and if you change smth they dont need to recompile only the .cpp file that has the variables does
but the the disadvantage of that outside of the file that got the variables everyone else only get the constant version not the constexpr version of the variables making it 
possibly less efficient and you need to keep source and header in sync


You should prefer the first way and just define your constants in a header file 
unless you know that you gonna change it a lot then in this case Way 2 might be smarter


There is a third way, its making your global constants as inline variables
this way is similar to the first way and is also recommended over the second way and the first way
basically you do the same as in way 1 define your constants in a header file but also give them the inline keyword infront of the constexpr
that makes it so that the variable can be defined multiple times in each file its used and with that the need of giving each and everyone their 
unique copy of the variable dissapears (btw constexpr functions dont need inline they are implicityl inline by default only constexpr variables need it)
only disadvantage of way 3 is that like in way 1 any change of the variables requires each file using it to recompile

Conclusion: Use Way 3 (Inline) and also keep in mind if using constexpr strings use std::string:view instead of std::string

*/

int main()
{
	std::cout << "Enter a radius: ";
	double radius{};
	std::cin >> radius;
	std::cout << "The circumference is: " << 2 * radius * constants::pi << '\n'; // constants::pi from constants.h


	return 0;
}