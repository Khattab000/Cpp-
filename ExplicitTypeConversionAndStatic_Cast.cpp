#include <iostream>

/*
We usually use static_cast<>() but there are some other similar ones:
static_cast          Performs compile time type conversion of similar types
dynamic_cast         Performs run time type conversion on pointers or references
const_cast           Adds or removes const // should be avoided
reinterpret_cast     Reinterprets the bit level representation as it where another typed //should be avoided
C-style cast         Performs a combonation of static,const and reinterpret_cast
*/




int main()
{
	//C-style cast is done by (type)variable e.g

	int x{10};
	int y{4};
	std::cout << x / y << '\n';
	std::cout << (double)x / y << '\n'; // C-style cast of x to double /prints 2.5
	// we can also do:
	std::cout << double(x) / y << '\n'; // function style cast of x to double and does the same as above / prints 2.5
	//Avoid using C-Style cast bc it has multiple usages and its not clear sometimes what exactly what kind of cast is being done

	//The cast you should mostly use is static_cast e.g:
	char a{ 'a' };
	std::cout << static_cast<int>(a) << '\n';

	std::cout << static_cast<double>(x) / y << '\n';

	//This conversions happens at compile time so if you try smth invalid you get an compilation error
#if 0
	int p{ static_cast<int>("Hello") }; //Int cant be converted to C-Style string so compilation error
#endif
	// static cast is also intentionally less powerful then C-Style to avoid doing dangerous conversions


	int i1{ 48 };
	char ch1 = i1; // implicit narrowing conversion might issue a warning

	char ch2{ static_cast<char>(i1) }; // explicit conversion so the compiler knows its intentional

	// another example
	int k{ 100 };
	k = k / 2.5;  // warning is issued

	int k2{ 100 };
	k2 = static_cast<int>(k2 / 2.5); // no warning issued


	/*
	Casting vs initializing a temporary object.
	There is static_cast<int>(x) and int{x} which creates a temporary object.
	3 main diffrences:
	
	1.
	int {x} uses list initialization so no narrowing conversions are allowed
	this is great for initializing variables where we dont wanna lose any data
	but ofc if you dont mind or you want to do narrowing conversion use 
	stati_cast e.g
	*/
#if 0
	std::cout << double{ x } / y << '\n'; // this is okey if int is 32 bit but narrowing if x is 64 bit so in this case its an error
#endif

	/*
	2.
	static_cast even tho maybe a bit stricter
	makes it easier and clearer that we intending to do a 
	conversion and also makes it easier to find the conversion in the code

	3.
	One big issue direct list initialization int{x} has that it only 
	works with single word types e.g int {x} is okey but unsigned int{x} 
	doesnt work for some reason e.g:
	*/

	unsigned char c5{ 'a' };
	std::cout << unsigned int{ c5 } << '\n'; // compiler error but for some reason it works on this context but keep it in mind that it normally doesnt work
	//if you wanna make sure that there is no error we can do a work around for it e.g
	using uint = unsigned int;
	std::cout << uint{ c5 } << '\n'; // no error bc technically the type is a single word type now

	//Conclusion : Just use static_cast
	return 0;
}