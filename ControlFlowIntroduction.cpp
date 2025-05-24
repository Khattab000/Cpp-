#include <iostream>

// this is called straight line program 
int main()
{
	std::cout << "Enter an integer: ";

	int x{};
	std::cin >> x;

	std::cout << "You entered " << x << '\n';
	return 0;
}

/*
There are multiple ways to alter the flow of the program called control flow
e.g
Conditional statements (only executes if condition is met);
Jumps (tells the cpu to start the execution at another point then the beginning)
Function calls (jump to some other location to execute the code there and then jump back)
Loops (keep executing a set code until the condition isnt met anymore or the condition to quit is met)
Halts (Terminate the program)
Exceptions( A special kind of flow control structure for error handling)
*/