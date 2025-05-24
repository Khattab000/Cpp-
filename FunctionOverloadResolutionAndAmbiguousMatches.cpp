#include <iostream>
#include <string> // std::string
//Normally when overloaded functions are used and fitting arguments are given its pretty straightforward but what if the arguments dont rly fit to any specific one so what happens then which one is called then :


void print(int x)
{
	std::cout << x << '\n';
}

void print(double x)
{
	std::cout << x << '\n';
}

#if 0 // had to bc foo(int) and foo (const int) had no differentiation and in theory if we had foo(const int&) then we also would need to remove it bc no differantion bc foo(1) could be an exact match to all three even with a trivial conversion

void foo(int x) // used in Step 1,2,4, and ambiguety example
{

}
#endif
#if 0
void foo(double x ) // used in Step 1,2,3,4 and ambigiuety example
{

}
#endif
#if 0
void foo(const int x) //used in Step 1 example
{

}
#endif
#if 0
void foo(const double& x)  // used in Step 1 example // double& is a reference to double 
{

}
#endif
#if 0
void foo(std::string sentence) // used in Step 3 example
{

}
#endif



class X //this defines a new type called X / we didnt cover classes yet and we only use it as an example for Step 4
{
public:
	operator int() { return 0; } // here is a user define conversion from X to int
};


void foo(unsigned int x)
{

}

void foo(float x)
{

}


void print(char a, int i)
{

}

void print(char a, double d)
{

}

void print(char a, float f)
{

}

int main()
{
#if 0
	print(5);    // calls add(int) pretty straight forward
	print(4.5);  // calls add(double ) pretty straight forward

#if 0 // bc 5L couldnt find a match or had to many matches
	print('a'); // well thats neither int or double
	print(5L);  // well thats neither int or double
#endif
	/*
	For cases like these where the arguments arent an exact match to the required type the compiler goes through several type conversion to see if it can find smth that fits the type
	at the end of each step/sequence its either: 
	1. No matching type was found so we move to the next step in the sequence
	2. One matching type found which is good with that we know what function to pick
	3. Multiple matching types found so compiler error

	And after going through all the steps/sequences and still not finding any matching type then we also get a compiler error

	There are 6 steps.
	*/

	// Step 1 Compiler tries to find an exact match or does trivial conversions (modify type without modifying value e.g: lvalue to rvalue,non const to const, non reference to reference) which also counts as exact match:
	foo(0);   // foo(int) exact match
	foo(3.2); // foo(double) exact match

	int x{ 1 };
	foo(x);           // trivial conversion of int x to const int
	double d{ 2.3 };  
	foo(d);           // trivial conversion of double d to const double&  (non reference to reference)

	

	// Step 2 Compiler tries to apply numeric promotion to certain smaller/narrower types to check if he finds a match then:

	foo('a');  // numeric promotion to fit for foo(int)
	foo(true); // numeric promotion to fit for foo(int)
	foo(4.5f); // numeric promotion to fit for foo(double)


	// Step 3 If no match through numeric promotion the compiler tries to apply numeric conversion to find a match then:

	foo('a');  // 'a' converts to double via standard conversion; foo(std::string) would require a user-defined conversion, so foo(double) is preferred


	// Step 4 If no match could be found through numeric conversion the compiler looks at user defined conversions

	X x; // here we created an object of tybe X named x
	foo(x); // x is converted to type int using user defined conversion from X to int so foo(int) is called
	// for example if our user defined conversion would have been X to char then the compiler still would have tried to find a match by promotion or conversion so in that case char would have been promoted to int



	// Step 5 If no match was found via user defined conversion then the compiler looks for a matching function using ellipsis (we will cover what that is in the future)


	// Step 6 If after all that nothing is found the compiler gives up and issues a compiler error


	

	//Now another way to get a compiler error is when the compiler finds multiple matching types (ambigious result) here to illustrate:
#if 0
	foo(5L); // 5L is type long b /bc there is no exact match or no promotion to be done , the compiler does the numeric conversion and it sees it can convert to int or double so thats why the compile error bc it cant decide which to chose foo(int) or foo(double)
#endif
	// here another example 

	foo(0); // int can be converted to unsigned int or float /compiler error
	foo(3.14159); // double can be converted to unsigned int or float /compiler error

	// but there are ways to fix that one way is just to write another overloaded function that takes the parameter your argument is using and the other is using static_cast beforehand to make sure it picks the write function e.g:
	int z{ 0 };
	foo(stati_cast<unsigned int>(z)); // calls foo(unsigned int) and compiles without issues
	// or use the literal suffix
	foo(0u); // calls foo(unsigned int) and compiles without issue / u suffix for unsigned

#endif


	//Now an example to matching for functions with multiple arguments e.g
	// in this case it checks all arguments and sees if one of them is better then the others so they gotta be at least the same with the the other arguments and better with one to be a match otherwise compile error
	print('x', 'a'); // calls print(char, int) bc only needs promotion on the second argument the other two need conversion



	return 0;
}