#include <iostream>
#include <string>
#include <string_view>

// as we discussed in the lesson before passing to  function with a reference to non const (int&) parameter ís highly restricted bc you only can pass modifiable lvalues lets see a way to circumvent that

void printRefI(const int& x)  // this time we are using a referencing to const
{
	std::cout << x << '\n';
}

// for example tho this wouldnt be allowed bc reference to const isnt modifiable
#if 0
void addOne(const int& x)
{
	++x;   // not allowed bc ref is const
}
#endif

void printVal (double d)
{
	std::cout << d << '\n';
}

void printRefD(const double& d)
{
	std::cout << d << '\n';
}


void foo(int a, int& b, const std::string& c)  // we can even mix if we pass by value or by reference without any issues 
{

}

//dw about those two define and struck some of the stuff we didnt cover yet
#define isSmall(T)(sizeof(T)<= 2* sizeof(void*)) // 2 means it must be 2 or fewer pointer-sized memory units to be considered cheap / #define instead of a regular function so we can pass a type
struct S 
{
	double a;
	double b;
	double c;
};

void printSV(std::string_view s)
{
	std::cout << s << '\n';
}

void printS(const std::string& s)
{
	std::cout << s << '\n';
}


int main()
{
	int x{ 5 };
	printRefI(x);   // this works as usual 

	const int y{ 5 };  
	printRefI(y);   // this fine too now bc we are using a reference to const parameter instead of reference to non const

	printRefI(5);   //before we couldnt pass rvalues but now we can bc we are using pass by reference to const

	//In general favor passing by reference to const unless you rly wanna modify the the value

	// as we discussed earlier unlike reference to non const, reference to const allows type conversion which does make the passed value to an rvalue and create a temporary object and the same works with passing it to a function
	printVal(5);  // 5 converted to temporary double and copied to parameter d
	printRefD(5);  // 5 converted to temporary double and bound to parameter d  
	printRefD(x);  // x converted to a temporary double so its not an lvalue anymore and the temporary object is bound to parameter d 
	//but in general in pass by reference or even just in the normal reference try to avoid the type conversion bc that might lead to an expensive copy 
	 
	const std::string c{ "Hello" };
	foo(5, x, c); //mixing passing by value and passing by reference to non const and const without any issues


	/*
	So if your struggling to decide to either pass by reference or pass by value here is a rule of thumb, pass fundamental types by value bc copying them is cheap but classes or more
	expensive types by const reference to avoid the expensive copies and if your not sure just go with const reference.
	(but if you wanna change the value of the variable itself you wanna use pass by reference to non const)

	Here are some examples.

	Passed by value:
	- enumerated types
	- views and spans (std::string_view)
	- types that mimic references or non owning pointers (iterators, str::reference_wrapper)
	- cheap to copy class types that have value semantics (std::pair with elements of fundamental types, std::optional, std::expected

	Passed by reference:
	- Arguments that need to be modified by the function 
	- Types tht arent copyable (std::ostream
	- Types where copying them has ownership implications that we dont want (std::unique_ptr, std::shared_ptr)
	- Types that have virtual functions or are likely to be inherited from (we talk about object slicing in a future chapter)
	*/


	/*
	But maybe you ask yourself why we just dont pass everything by reference here is why :
	- For objects that are cheap to copy their cost is similar to binding but accessing the object is faster and the compiler is likely to optimize better

	but on the other hand
	- For objects that are expensive to copy the cost of copy outweighs the benefits of the better optimization so in this case we pss  by reference

	So a rule of thumb is an object is cheap to copy if it uses 2 or fewer words of memory  (word being the size of a memory address) like short, int or double and it doesnt do anything 
	fancy when copied like opening a file or allocating memory 

	Here is a program that determines if a type or object is cheap to copy accordingly :
	*/



	std::cout << std::boolalpha;
	std::cout << isSmall(int) << '\n'; //true  / passing type was only allowed bc we used #define and not a usual function 

	double z{};
	std::cout << isSmall(z) << '\n'; //true
	std::cout << isSmall(S) << '\n'; //false bc its a struct so its not cheap

	/*
	On the matter of if you should use const std::string& or std::string_view you should prefer std::string_view bc it has a wider range of use cases and already takes care of the expensive copy issue
	void doSmth(const std::string& c);
	void doSmth(std::string_view c ); // prefer this one

	only exception is when your function calls another function that takes C-Style string or std::string parameter you might wanna use cosnt std::string& bc std::string_view is not guaranteed to 
	null terminate which C-Stlye string functions expect and doesnt efficiently convert back to std::string


	Here is also an interesting comparison:
Argument type                std::string_view parameter            const std::string& parameter
-std::string                -Inexpensive conversion               -inexpensive reference binding
-std::string_view           -Inexpensive copy                     -expensive explicit conversion to std::string (implicit not possible bc compiler error we need to use static_cast)
-C-Style string/literal     -Inexpensive conversion               -expensive conversion

	showing that in most cases std::string_view is cheaper and dont forget to consider bc std::string_view is cheap to copy and is not a reference it also has 
	the benefit of being accessed much faster and generally being more optimized and you get the additional benefit of being able to produce sub strings 
	cheaply which are expensive with const std::string& bc it needs copy the substring into the string first that it binds to.
	
	Here is the comparison table in code form:
	*/

	std::string u{ "Hello World" };
	std::string_view e{ "Bye World" };
	//pass to std::string_view
	printSV(u);  // good cheap
	printSV(e);  // good cheap
	printSV("Hello again"); //good cheap

	//pass to std::string&
	printS(u);  // good cheap
	printS(static_cast<std::string>(e)); // compile error without static cast /bad expensive
	printS("Hello again");  //bad expensive

	//one last reminder string_view doesn't own the data — don’t use it if the original string might go out of scope will lead to undefined behaviour

	return 0;
}