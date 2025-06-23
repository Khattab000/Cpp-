#include <iostream>
#include <string>
#include <string_view>


//In this lesson we talk about default constructors which are constructors that take no arguments e.g:
class Foo
{
public:
	Foo() //default constructor bc takes no arguments 
	{
		std::cout << "Foo default constructed\n";
	}

};


//You can also give the constructor default arguments e.g:
class Foo2
{
	int m_x{};
	int m_y{};

public:
	Foo2(int x = 0, int y = 0)  //constructor has default arguments this is also a default constructor 
		:m_x{ x }
		,m_y{ y }
	{
		std::cout << "Foo2(" << m_x << ", " << m_y << ") constructed\n";
 	}
};

//Bc Constructors are basically functions meaning they also can be overloaded e.g:
class Foo3
{
	int m_x{};
	int m_y{};
public:
	Foo3() // default constructor
	{
		std::cout << "Foo3() default constructed\n";
	}
	Foo3(int x, int y) //non default constructor can exist bc of overloading
		:m_x{ x }
		,m_y{ y }
	{
		std::cout << "Foo3(" << m_x << ", " << m_y << ") constructed\n";
	}

#if 0
	/*
	compile error when object is initialized bc you are not allowed to have two default constructors bc compiler is unable to disambiguate which constructor
	should be used in a default case
	*/
	Foo3(int x = 1, int y = 1)  //default arguments and bc all of the arguments are default this is a default constructor
		:m_x{x}
		,m_y{y}
	{
		std::cout << "Foo3(" << m_x << ", " << m_y << ") constructed\n";
	}
#endif

};


class Foo4
{
	int m_x{};
	int m_y{};

public:
	int getX() const
	{
		return m_x;
	}
	/*
	Note: No constructors, in this case the compiler implicitly creates a public default constructor so the object can be value or default initialized this would look like this
	(btw this only happens if there isnt any other constructor keep that in mind)
	Foo4() //implicitly generated constructor
	{
	}

	this is useful when we dont have any data members but if we do we normally want to be able to initialize them and make them possible to give other values other than the default
	*/
};

//There is also a keyword if you wanna create a default constructor which is the same as the implicitly default constructor so instead of having an empty body we can use =default e.g:
class Foo5
{
	int m_x{};
	int m_y{};
public:
	Foo5() = default; //generates and explicitly defaulted default constructor /preferred over default constructor with empty bodx

	Foo5(int x, int y)
		:m_x{ x }, m_y{ y }
	{
		std::cout << "Foo5(" << m_x << ", " << m_y << ") constructed\n";
	}
};


/*
There is a small difference between an explicitly defaulted default constructor (the implicitly added default constructor behaves the same)
and a user-defined default constructor with an empty body:

When an object is value-initialized using braces (e.g., `T obj{}`):
- The defaulted or implicit constructor causes members like `int` to be zero-initialized, then default-initialized.
- The user-defined default constructor skips zero-initialization and only default-initializes members.

This can lead to undefined behavior if a member (like `int m_a`) lacks a default initializer and remains uninitialized.
*/
class User
{
	
	int m_a;   // no default initialization value and will also NOT be zero initialized only default initialized through the user defined default constructor when the object is created and default initialized with braces which leads to undefined behavior
	int m_b{}; // default initialization

public: 
	User() // user defined empty constructor
	{}
	int a() const
	{
		return m_a;
	}
	int b() const
	{
		return m_b;
	}
};

class Default
{
	int m_a;   // no default initialization value but will BE zero initialized and default initialized when the object is created and default initialized with braces through explicitly defaulted defaul constructor
	int m_b{}; // default initialization

public:
	Default() = default;  // explicitly defaulted defaul constructor

	int a() const
	{
		return m_a;
	}
	int b() const
	{
		return m_b;
	}
};

class Implicit
{
	int m_a;   // no default initialization value but will BE zero initialized and default initialized when the object is created and default initialized with braces by the implicitly added default constructor
	int m_b{}; // default initialization

public:
	//no constructor so implicit default constructor
	int a() const
	{
		return m_a;
	}
	int b() const
	{
		return m_b;
	}
};
//one advantage of only default initializing like int x; instead of value initialization like intx{}; is that the first is more performant but less safe bc it skips the zero initialization



//only use default constructor when it makes sense that all members should be defaulted or can be defaulted for this class it makes sense:
class Fraction
{
	int m_nominator{ 0 };
	int m_denominator{ 1 };

public:
	Fraction() = default; //makes sense bc we should let the user make an default fraction with the values 0/1

	Fraction(int x, int y)
		:m_nominator{x},m_denominator{y}
	{ }

	void print() const
	{
		std::cout << m_nominator << "/" << m_denominator << '\n';
	}
};
//but using default constructor for this class below doesnt make sense e.g:
class Employee
{
	std::string m_name{};
	int m_id{};
public:
#if 0
	//so DONT put this default constructor in
	Employee() = default; //doesnt rly make sense to give a default for an employee bc if initiailized with that we will have nothing for m_name and 0 for m_id 
#endif
	Employee(std::string_view x,int y)
		:m_name{x}
		,m_id{y}
	{ }

	void print() const
	{
		std::cout << m_name << ", " << m_id << '\n';
	}
};

int main()
{
	Foo foo{}; //initializes foo and prints "Foo default constructed"

	Foo2 f2{};
	Foo2 f3{ 6,7 };

	Foo3 f4{};
	Foo3 f5{ 9,7 };

	Foo4 f6{};
	std::cout << f6.getX() << '\n'; // prints 0 bc of implicit public default constructor

	Foo5 f7{}; // calls Foo5() default constructor


	User user{};
	std::cout << "(" << user.a() << ", " << user.b() << ")\n"; //undefined behavior for a() and 0 for b() bc m_b is default initialized in the class 
	Default def{};
	std::cout << "(" << def.a() << ", " << def.b() << ")\n"; // (0,0)
	Implicit imp{};
	std::cout << "(" << imp.a() << ", " << imp.b() << ")\n"; // (0,0)

	Fraction bruch1{};
	bruch1.print();
	Fraction bruch2{ 7,8 };
	bruch2.print();


	Employee jeff{ "jeff",2 };
	jeff.print();
#if 0
	Employee missingno{}; // compilation error bc no matching constructor could be found bc we tried to initialize with a default constructor 
	missingno.print(); // if there were a default constructor this would return , 0   as you can see it returns nothing for m_name but 0 for the  m_id
#endif

	return 0;
}