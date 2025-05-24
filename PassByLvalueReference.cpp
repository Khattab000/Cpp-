#include <iostream>
#include <string>
// in this lesson we will show you why lvalue references are useful 

void printValue(int y)
{
	std::cout << y << '\n';
} // y is destroyed here


void printValue(std::string x)
{
	std::cout << x << '\n';
}

void printValueRef(std::string& c) // we changed the parameter so the argument is passed by reference 
{
	std::cout << c << '\n';

	//But be careful changes to the reference also change the original e.g
	c += "!!!";   // this changes the string to "Hello, world!!!!" and this affects both the reference c and the std::string s (the referant in main)
} // c destroyed here


void printAdresses(int val, int& ref)
{
	std::cout << "The adress of the value parameter is: " << &val << '\n';
	std::cout << "The adress of the reference parameter is: " << &ref << '\n';
}


int addOne(int x)
{
	return ++x;
}

int addOneRef(int& x)
{
	return ++x;
}


void printValueRef(int& y)  // passing by reference only works with modifiable lvalues so no const or constexpr
{
	std::cout << y << '\n';
}
int main()
{
	int x{ 5 };
	printValue(x);   // x is passed by value meaning copied into the parameter y and then this copy gets destroyed and bc its a fundemental type its pretty inexpensive and fine to do that

	// but lets say we have a type that is more complicated and expensive like a class type (std::string) e.g
	std::string s{ "Hello, world!" }; // s is a std::string
	printValue(s);  //s is passed by value (copied) into parameter x but this is pretty expensive unlike fundemental types
	//To avoid expensive copies we can use pass by reference, we do that by changing the functions parameter e.g int x to int& x or std::string c to std::string& c   e.g
	printValueRef(s); //s is passed by reference into parameter c (c basically bound to s) and this inexpensiv unlike passing by copy

	std::cout << s << '\n'; // prints "Hello, world!!!!" instead of "Hello, world!" bc unlike passing by copy , passing by reference also reflects its changes to the referant in this case std::string s
	

	//here is an example to show how the pass by copy and pass by reference are two different objects e.g:
	int b{ 7 };
	std::cout << "The adress of b is " << &b << '\n';   // & in front of an variable like &b gives you its adress
	printAdresses(b, b); // this shows that the b and the reference to b have the same adress but the copy of b doesnt 

	//Here is another example how the pass by reference also affects the referant

	int o{ 8 };
	std::cout << "value = " << o << '\n'; // prints 8
	addOne(o);
	std::cout << "value = " << o << '\n'; // also prints 8 bc we passed o as an copy so changes to the copy dont reflect on the original

	addOneRef(o); // this passed o by reference so the changes reflect on the variable o
	std::cout << "value = " << o << '\n'; //prints 9 now bc of passed by reference

	//So in general passing values by reference to non const allows us to modify variable the argument was passed on from


	//only modifiable lvalues can be passed by reference to non const to a function so no const or literals e.g:
	int i{ 5 };
	printValueRef(i); // okay   i is modifiable lvalue
#if 0
	const int l{ 5 };
	printValueRef(l); // error l is non modifiable lvalue
	
	printValueRef(5); // error 5 is an rvalue
#endif
	//But there is an easy work around to pass by const lvalue reference which we will cover in the next lesson


	return 0;
}