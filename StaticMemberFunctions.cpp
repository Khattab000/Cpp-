#include <iostream>
#include <chrono>
#include <random>

// On this lesson we learn about static member functions 

// we stated in an earlier chapter that static member can be directly accessed with no objects with the scope resolution operator as long as its public e.g:
class Something
{
public:
	static inline int s_i{ 2 };

// but what if the static member variable is private
private:
	static inline int s_b{ 9 };

/*
We could make a public member function to get the private static member variable but that would mean we need to instantiate/create an object first before having access to the
variable e.g:
*/
public:
	int getStatic()
	{
		return s_b;
	}

	/*
	But there is a much better way to gain access to private static member variable, by using a static member function which just like static members variable are independent,
	meaning you can call them without having to instantiate/create an object first e.g:
	*/

	//reminder member function inside the class are always implicitly inline thats why we dont need to add it here to have it be in the class 
	static int getStaticValue()  // static keyword makes the function static but doesnt mean it returns a static int //btw no need for inline or defintion outside of the class 
	{
		return s_b;
	}

	/*
	Two important facts for static member variables:
	First static member variables dont have the "this" pointer bc its not attached to the object, bc the "this" pointer always points to the object that the member function is 
	working on but static members do not work on an object so the this pointer is not needed. 

	Second static members functions can directly access other static member functions and variables but not non static members. This is bc non static members need to belong to 
	the class object and static member functiosn have no class object to work with.
	*/
};


class IDGenerator
{
	
	static inline int s_nextID{ 1 };

public:
	//If you want to you could also declare the static function inside the class and define it outside just like we intitially did with the static member variable e.g:
	static int getNextID();
};

int IDGenerator::getNextID() // no need for static here bc its on the declaration /bc outside of the class its not inline but make it inline if you want to use this in a header file
{
	return s_nextID++;
}


/*
A word to the wise about classes with only static members: while they can be useful, they also come with downsides.

First, if you want to have two independent instances (e.g. two separate ID generators), you can't since static members are shared across all uses of the class. 
You'd have to duplicate the class and rename it to have two versions.

Second, static members behave like global variables. Since they belong to the class, not any specific object, changes to them affect all parts of the program that use them. 
This can lead to hard-to-track bugs, similar to those caused by global variables.

To avoid these issues, prefer a design where:
- You use a mix of static and non-static members, or
- You create a normal class and instantiate a global variable of that class. This gives you global access (via the global instance),
but you can still create other local instances when needed.

This offers flexibility without the risks associated with fully static designs.
*/

/*
Pure static classes and namespaces are quite similar bc both let you define variables with static duration and functions within their scope. However main difference is that a 
class gives you access control which  a namespace doesnt
*/


//There are no static constructors in C++ so you just initialize the the static variable as they are defined
struct Chars
{
	char first{};
	char second{};
	char third{};
	char fourth{};
	char fifth{};
};

struct MyStruct
{
	static inline Chars s_myChars{ 'a','e','i','o','u' }; //initialize static variable at point of definition
};

//But if the initialization needs some type of logic you might wanna use a helper function which returns a value to initialize your stativ variable e.g:
class MyClass
{
	static Chars generate()
	{
		Chars c{}; // create an object
		// example for some logic
		c.first = 'a';
		c.second = 'e';
		c.third = 'i';
		c.fourth = 'o';
		c.fifth = 'u';

		return c;
	}

public:
	static inline Chars s_myClassChars{ generate() };  //initialized with helper function

	//Lambda can also be useful we talk about those in the future
};


//small Quiz:

class Random
{
private:
	static std::mt19937 generate()
	{
		std::random_device rd{};

		// Create seed_seq with high-res clock and 7 random numbers from std::random_device
		std::seed_seq ss{
			static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
				rd(), rd(), rd(), rd(), rd(), rd(), rd() };

		return std::mt19937{ ss };
	}
	static inline std::mt19937 s_mt{ generate() }; // generates a seeded std::mt19937 and copies it into our global object
public:
	

	// Generate a random int between [min, max] (inclusive)
	static int get(int min, int max)
	{
		return std::uniform_int_distribution{ min, max }(s_mt);
	}
};



int main()
{
	
	std::cout << Something::s_i << '\n'; // possible with the scope resolution operator bc the variable is public
#if 0
	std::cout <<  Something::s_b << '\n'; // error bc s_b is private
#endif
	Something temp1 {};  // we need to create an object first before getting access 
	std::cout << temp1.getStatic() << '\n';

 
	std::cout << Something::getStaticValue() << '\n'; 
	// bc getStaticValue() is a static member function we can use it independently with no need to create an object and also get access to the private static member variable this way
	

	for (int count{ 0 }; count < 5; ++count)
	{
		std::cout << "The next ID is: " << IDGenerator::getNextID() << '\n';
	}

	std::cout << MyClass::s_myClassChars.third << '\n'; // can directly access the struct members of our static member variable


	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 10; ++count)
		std::cout << Random::get(1, 6) << '\t';

	std::cout << '\n';

	return 0;
}