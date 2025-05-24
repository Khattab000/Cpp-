#include <iostream>


int main()
{

	int x{ 5 };
	{
		int y{ 4 };

		std::cout << x << y << '\n';   // even tho x was defined outside of the nested block its still in scope in the nested bloch
	}
	//std::cout << x << y << '\n';  this tho would be an error bc the y was defined in the nested block and is out of scope for the outer block

	// there is no linkage (linkage being checking if something has the same name or refers to the same variable or function) between outer block and the nested block e.g

	/*
	{
		[[maybe_unused]] int x { 2 }; // this x is entirely diffrent from the x we defined at first
		// we go into detail later what happens if both are used in the same nested block
	}
	*/ 

	std::cout << "Enter an integer: ";
	int smaller{};
	std::cin >> smaller;
	std::cout << "Enter a larger integer";
	int larger{};
	std::cin >> larger;

		
		if (larger < smaller)
		{
			int temp{ larger };
			larger = smaller;
			smaller = temp;          // in future you could just use std::swap(larger, smaller); to swap values but you need to inclued <utility>
		}
		std::cout << "The smaller value is " << smaller << '\n';
		std::cout << "The larger value is " << larger << '\n';
	


	return 0;
}