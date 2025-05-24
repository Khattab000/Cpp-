#include <iostream>
#include <bitset>
#include <cmath>  // for std::sqrt
#include <cassert>


/*
we learned about function templates and type template parameters that are placeholder to actual types now we will discuss non type template parameters,
there are parameters for a fixed type that serve as placeholder for constexpr values being passed down these types can be:
integral, enumeration, std::nullptr_t, floating, pointer/reference to object, pointer/reference to function, pointer/reference to member function, literal class type
*/

template<int N>  //declare a non type template parameter of type int named N /btw its recommended using capital N for int non type template parameter
void print()
{
	std::cout << N << '\n';  // Value of N used here
}



double getSqrt(double d)
{
	assert(d > 0.0 && "getSqrt(): d must be non-negative"); // this will only be caught on run time bc function parameters cant be constexpr but there is a way to make it constexpr 
	
	//assert will be probably compiled out in non debug builds thats why the if statement
	if (d >= 0)
	{
		return std::sqrt(d);
	}
	return 0.0;
}


template <double D>                                                                
double getSqrtConstexpr()
{
	static_assert(D > 0.0 && "getSqrt(): d must be non-negative");  // now this will be caught in compile time bc D is non type template parameter so it is a floating point constexpr (since C++20)
	//now that we have constexpr we can use static_assert() instead of assert()
	
	if constexpr (D >= 0)   // we will cover constexpr in the if statement in the future 
	{
		return std::sqrt(D); // surprisingly std::sqrt() isnt a constexpr function until C++26
	}
	return 0.0;
}


// You should generally avoid overloading template functions with non type template parameters bc it will often lead to an comiler error due to ambiguous matches (the matching algorithm isnt as sophisticated as in the normal function overload)
template <char C>
void print()
{
	std::cout << C << '\n';
}






template<auto N> // since C++17 we can use auto as type for non type template parameter / deduce non type template parameter from template argument
void printAU()
{
	std::cout << N << '\n';
} // this doesnt leads to error due to ambiguety like the overloaded variant bc compiler looks for ambiguety first and then instantiates the functions so its fine bc only one template function exists when he starts looking



template<int N>
constexpr int factorial()
{
	static_assert(N >= 0 && "The number needs to be bigger or equal to 0");
	int product{ 1 };
	for (int i{ 2 }; i <= N; ++i)
	{
		product *= i;
	}

	return product;
}



int main()
{
#if 0
	//example of a non type template parameter we used in the past
	std::bitset<8>bits{ 0b0000'0101 };   // The <8> is a non type parameter and in this case it tells the compiler how many bits we want stored

	print<5>(); // 5 is our non type template argument / prints 5


	std::cout << getSqrt(5.0) << '\n';
	std::cout << getSqrt(-5.0) << '\n';  //stops at runtime bc assert fails
#endif

	std::cout << getSqrtConstexpr<5.0>() << '\n';
#if 0
	std::cout << getSqrtConstexpr<-5.0>() << '\n';  //compile time error bc it gets caught by static assert
#endif

	// So in general we use non type template parameters when we want to pass down constexpr values to a function or class


	// certain non type template arguments can also implicitly convert in order to match a non type template of a different type 
#if 0
	print<5>();   // no conversion needed prints 5  /both those calls fail when we overload the template function with another template function taking a non type template parameter of the type char bc we alread have one of the type int 
	print<'c'>(); // conversion needed    prints 99 / this function can be used in char function or converted to int and vice verca for the call above it thats why the error due to ambiguety
#endif
	/*
	but only certain conversions are allowed in this case theser include:
	- integral promotions (e.g: char to int)
	- integral conversion (e.g: char to long or int to char)
	- user defined conversion (e.g some program defined class to int)
	- Lvalue to rvalue conversions (e.g: some variable x to the value of x)

	but these are much less then the normal implicit conversion rules like (e.g: a non type template constexpr int wont convert to an constexpr double)
	*/
	

	printAU<5>();    // N deduced as int 5
	printAU<'c'>();  // N deduced as char c


	static_assert(factorial<0>() == 1);
	static_assert(factorial<3>() == 6);
	static_assert(factorial<5>() == 120);
#if 0
	factorial<-3>(); // should fail to compile
#endif

	return 0;
}