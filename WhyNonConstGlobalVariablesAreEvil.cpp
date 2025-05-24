#include <iostream>


// main reason why you should avoid non const global variables is that their values can be changed

int g_mode; 

void doSomething()
{
	g_mode = 2;
}

void someFunction()
{
	//some code 
	if (g_mode == 4)     // another reason to avoid non const global variables bc now you need to check everywhere where g_mode might have changed to make sure the function works properly
	{
		std::cout << "Averted!\n";
	}
}


// There are also issues with the initialization order for global nonconst variables e.g

int init()
{
	return 5;
}

int g_something(init()); // non constexpr initialization 

int initX(); //Forward Declaration 
int initY();

int g_x{ initX() }; // g_x is initialized first
int g_y{ initY() };

int initX()
{
	return g_y; // g_y isn't initialized when this is called
}

int initY()
{

	return 5;
}



int main()
{
	g_mode = 1; // changed g_mode to 1 

	doSomething(); // changed g_mode to 2 even tho the programmer might not know  that and still expects g_mode to be 1

	if (g_mode == 1)
	{
		std::cout << "No threat detected.\n";
	}
	else
	{
		std::cout << "Launching nuclear missiles...\n";
	}

	// with that in mind local variables are a bit safer bc they cant be affected directly by the function


	std::cout << g_x << ' ' << g_y << '\n';  // this prints 0 and 5 bc g_y wasnt initialized until later so keep in mind in what order its initialized in and avoid once where it might be ambigious like when its between two files where each of them could be initialized first

	return 0;
}

/*
Ways to help you in case you still wanna use non const global variables (these are ofc also things you can use for all global variables even the const ones and are also recommended) :

constexpr double gravity {9.8}; // risk of naming collision and if used unclear if its a global or local variable

FIRST either use a g_ or g prefix or put it in a namespace :

namespace constants
{
    constexpr double gravity {9.8};
}
int main()
{
  std::cout << constants::gravity << '\n';  // no risk for naming collisions anymore and its clear that its global bc namespaces are global
}


SECOND instead of allowing direct access to the variable try to encapsulate it like making the variable static but providing a external global function to work with the variable e.g:

constants.cpp

namespace constants
{
   constexpr double gravity {9.8}; // has internal linkage only so no way for other files to access it directly
}

double getGravity()
{
   return constants::gravity;  // this way you got access to the variable without directly accessing it if you wanna use it in other files
}

main.cpp

double getGravity()

int main()
{
  std::cout << getGravity() << '\n';
}


THIRD don't put the global variable in a stand alone function rather pass the value to the function so you are way more flexible e.g:

namespace constants
{
     constexpr double gravity {9.8};
}

double instantVelocity(int time, double gravity)
{
   return gravity * time;       //instead of putting constants::gravity in the function body do that and just pass it to the function
}

int main()
{
   std::cout << instantVelocity(5, constants::gravity) << '\n'; // pass the constant to  the function as a parameter
}

*/