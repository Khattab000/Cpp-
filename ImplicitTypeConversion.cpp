#include <iostream>
#include <cstring>


float doSomething()
{
	return 3.0; // double 3.0 implicitly converted to float
}

void doSomethingElse(long l)
{

}

int main()
{
	float f{ 3 }; // initialize floating variable with int 3 /implicit conversion to float

	int n{3};
	float x{};
	std::memcpy(&x, &n, sizeof(float));
	/*
	unlike implicit conversion std::memcpy just copies 
	the raw bytes of memory so it technically doesnt change the type 
	of the destination variable this tho makes x = 4.2039e-45
	instead of 3 the parameters of std::memcpy(pointer to destination,
	pointer to the variable to copy from,amount of bytes being copied)
	*/
	std::cout << x << '\n';


	double division{ 4.0 / 3 }; // int 3 implicitly converted to double


	if(5) // int value 5 implicitly converted to bool
	{ }


	doSomethingElse(3); // int 3 implicitly converted to type long


	/*
	The way the compiler knows what and how to do the conversion is by the set
	rules called standard conversion these are split in 5:

	-Numeric Promotions (Conversion of small integral types)
	-Numeric conversion (Other integral or floating point conversions)
	-Qualification conversion (Conversion that add or remove const or volatile)
	-Value transformations (Conversion that change the value category of an expression)
	-Pointer conversions (conversion from std::nullptr to pointer types or pointer types to other pointer types)

	These dictate how and under what condition to do the conversion
	(more details will be covered in future chapters)
	*/

#if 0
	// Ofc conversion can fail too e.g:
	int u{ "14" };

	//or even
	int p{ 3.5 }; // brace initialization doesnt allow conversion that results in data loss

#endif

	return 0;
}