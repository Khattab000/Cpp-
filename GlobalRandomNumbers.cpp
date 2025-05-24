// used with Random.h file
#include "Random.h" //used for Random::mt, Random::get() and Random::generate()
#include <iostream>  
#include <cstddef> // used for std::size_t


// Here's how to use a PRNG in multiple files without passing it everywhere or hurting randomness by making new ones each time:
// we'll create a single global PRNG inside a namespace in a header file and include it where needed.


int main()
{
	//after finishing Random.h here are some examples
	std::cout << Random::get(1, 6) << '\n'; // returns int between 1 and 6
	std::cout << Random::get(1u, 6u) << '\n'; // returns unsigned int between 1 and 6
	
	std::cout << Random::get<std::size_t>(1, 6u) << '\n'; // returns std::size_t between 1 and 6
	// floats dont work we gotta modify Random.h to accommodate them

	//We can also create our random number generator with custom distribution by accessing Random::mt directly e.g
	
	std::uniform_int_distribution die9{ 1,9 };
	for (int count{ 1 }; count <= 10; ++count)
	{
		std::cout << die9(Random::mt) << '\t'; // generate a roll of the die here
	}
	std::cout << '\n';

	return 0;
}