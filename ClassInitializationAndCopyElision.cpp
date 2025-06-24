#include <iostream>

//In this lesson we talk about Class initialization and copy elision

class Foo
{
public:
	Foo() //default constructor
	{
		std::cout << "Foo()\n";
	}
	Foo(int x) //normal constructor
	{
		std::cout << "Foo(int)\n";
	}
	Foo(const Foo& x) //copy constructor 
	{
		std::cout << "Foo(const Foo&)\n";
	}


};


class Something
{
	int m_x{};
public:
	Something (int x)
		:m_x{x}
	{ 
		std::cout << "normal constructor\n";
	}
	Something(const Something& x)
		:m_x{ x.m_x }
	{
		std::cout << "copy constructor\n";
	}
	void print() const
	{
		std::cout << "Something(" << m_x << ")\n";
	}
};


class Something2
{
public:
	Something2() = default;
	Something2(const Something2&) //if your wondering if we are missing the parameter name dw bc its allowed to emit it if its not used in the function body that works for constructors and functions
	{
		std::cout << "Copy constructor called\n";
	}
};

Something2 rvo()
{
	return Something2{}; // calls Something() and copy constructor
}

Something2 nrvo()
{
	Something2 s{}; // calls Something() constructor
	return s;  // calls copy constructor
}

int main()
{
	//we covered in one of the earliest chapters different ways to initialize which all also apply to class types e.g:
	//calls Foo() default constructor:
	Foo f;
	Foo f2{};
	//calls Foo(int) normal constructor:
	Foo f3 = 3;
	Foo f4(4);
	Foo f5{ 5 };
	Foo f6 = { 6 };
	//calls Foo(const Foo&) copy constructor
	Foo f7 = f3;
	Foo f8(f3);
	Foo f9{ f3 };
	Foo f10 = { f3 };
	/*
	direct list initializatio or value initialization like int x{8} and int int x{} is preferred we gonna cover some differences in the future similar to how brace 
	initialization prevents narrowing also there are cases where certain types of initialization is disallowed e.g member initializer list  only allows the use of direct forms
	of initialization not copy initialization
	*/

	Something s{ Something{5} };  
	/*
	You would assume this to print "Normal Constructor" and then "Copy Constructor" which it doesnt, as you can see this code is needlessly inefficient 
	and can be written much better by just writing Something s{5} which only calls the normal constructor. 
	
	So now why did our code above even for its inefficiency not call the copy constructor ? The reason being Copy elision. As we stated earlier the compiler is free 
	to optimize our code abnd rewrite statements to optimize them, this allows the compiler tho remove unecessary copying of objects and when the compiler optimizes out the 
	call to a copy constructor we call that the constructor has been elided. And unlike other types of optimization this doesnt abide by the "as if" rule (as if rule meaning 
	that the compiler can optimize as much as it wants as long as it doesnt change anything that affects the observable behavior of the program) and bc its exempted of this 
	rule we strongly advised against giving copy constructors side effects bc they wont execute if the call to the copy constructor is optimized out thats why you couldnt see
	the print statement of it. And since C++17 copy elision is mandatory in cases like these so the call to the  copy constructor in this case will be optimized out
	*/
	s.print();


	std::cout << "Initializing s1\n";
	Something2 s1{ rvo() };  // calls copy constructor
	std::cout << "Initializing s2\n";
	Something2 s2{ nrvo() }; // calls copy constructor
	//In the Something2 case these variables s1 and s2 would call the copy constructor 4 times but bc of copy elision its getting called zero times bc it get optimized out 

	//In mandatory copy elision cases the default copy constructor doesnt need to exist for the optimization but for optionaly copy elision cases it needs to exist for the optimization
	//We cover in later chapters what happens in cases where optional copy elision isnt performed and move semantics are used instead 


	return 0;
}