#include <iostream>

int value{ 7 }; // global variable

void foo()
{
	std::cout << "global variable value: " << value << '\n';  // global variable value isnt shadowed yet so this refers to 7 
}


// when there are two variables with the same name one being in the outer block and the other in the nested block the compiler performs smth we call variable shadowing so the one in the nested one get priority


int main()
{
	int apples { 5 };

	{
		std::cout << apples << '\n';  // apples from outer block is used 

		int apples{ 0 };      // this is fine bc its in a nested block and will be destroye by the end of it and isnt viewable in the outer block

		apples = 10;    // apples from the nested block is used here bc it got priority over the outer block one through variable shadowing / small note if it was the outer block one it would keep the value even after the nested block

		std::cout << apples << '\n';  // apples from nested block used here
	}

	std::cout << apples << '\n';    // apples from outer block used here

	// the same applies to global variables too e.g
	foo();  // this prints 7 bc it refers to the global variable

	int value{ 10 };  // this one got priority over the global variable

	foo(); // still prints 7 because functions outside of main access the global variable not the local one unless passed explicitly


	++value; // increments local variable

	std::cout << "local variable value: " << value << '\n';  // prints the local variable
	
	// but if you want to access the global variable you can bc its part of the global namespace so you can use :: to explicitly tell the compile to use the global one e.g
	--(::value); // decrements the global value

	std::cout << "global variable is: " << ::value << '\n'; // prints global variable bc of :: 


	return 0;
}  // local variable destroyed here

// Conclusion: try to avoid shadowing variables its prune to error