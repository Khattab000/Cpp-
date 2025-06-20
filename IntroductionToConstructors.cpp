#include <iostream>

//In this lesson we talk about constructors which can help with the initialization of non aggregate class types 



class Foo //not an aggregate so no aggregate initialization bc of private members 
{
	int m_x{};
	int m_y{};

public:
	Foo(int x, int y) // thats a constructor which takes two arguments we give it the exact same name as the Class even the same capitalization but no return type 
	{
		std::cout << "Foo(" << x << ", " << y << ") constructed\n";
	}

	void print() const
	{
		std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
	}
};

class Something
{
	int m_x{};
public:
	/* 
	Dont make constructors ever const bc they should be able to modify and intialize objects and if your wondering what happens if we have a const object 
	which normally cant call any non const member function, its fine bc constructors have an exception bc the object doesnt get its const status until afert its 
	constructed 
	*/
	Something() // no const even if the constructor doesnt modify
	{
		m_x = 5;
	}
	int getX() const
	{
		return m_x;
	}

};
	


int main()
{
#if 0
	Foo f{ 3,4 }; // if it was a struct with no private members (or a class with only public) this would work and initialize the member by the order that they are defined in the struct
	//error message is that it couldnt find a constructor/missing constructor for this initialization
#endif
	Foo f{ 3,4 }; // now the same line works even tho its a non aggregate class bc we have a constructor now /prints 3,4
	f.print();    // prints 0,0 bc its not saved our constructor doesnt have that ability yet we will show how to do that in the next lesson and the different types of initialization


	Foo foo{'a',true}; //just like normal functions the constructor also does implicit conversion to initialize its arguments so this works too and will be converted to int,int
	//(ofc it only works if implicit conversion with the type is possible and no narrowing conversion bc brace initialization)
	foo.print();

	const Something s{}; // even tho its const object it still works implicitly with the (non const) constructor 
	std::cout << s.getX() << '\n'; // prints 5 bc thats what the constructor did



	//Conclusion: Constructor vs setter , constructor is here to initialize the object and setter is here to assigne a value to a single or multiple members of a an exisiting object

	return 0;
}