#include <iostream>

//In this lesson we talk about constexpr aggregates and classes

constexpr int greater(int x, int y) // we covered that constexpr functions may run in compile or run time 
{
	return (x > y ? x : y);
}

#if 0
struct Pair
{
	int m_first{};
	int m_second{};
#if 0
	int greater() const
	{
		return (m_first > m_second ? m_first : m_second);
	}
#endif
	constexpr int greater() const // can evealuate at either compile time or runtime 
	{
		return (m_first > m_second ? m_first : m_second);
	}
};
#endif

//So after making Pair have a constexpr function member and the object a constexpr lets see what happens when we change Pair to a class 
class Pair
{
	int m_first{};
	int m_second{};
public:
	
	constexpr Pair(int x, int y) // added constexpr to constructor so we can initialize constexpr object of the type Pair 
		:m_first{x}
		,m_second{y}
	{ }

	//IMPORTANT the constexpr keyword doesnt make your member functions implicitly const you need to specify it yourself with the const keyword
	constexpr int greater() const // can evealuate at either compile time or runtime  / we use const here bc constexpr doesnt make the function implicitly const
	{
		return (m_first > m_second ? m_first : m_second);
	}
};

constexpr int init()
{
	Pair p{ 5,6 }; //p itself doesnt need to be constexpr tho but the operation on it must be valid in a constexpr context 
	return p.greater();
	/*
	even tho p isnt constexpr the constructor and the member function we return MUST be constexpr bc this is a constexpr function so it needs to be able to evaluate at
	compile time and it can only call functions that are also able to be evaluated at compile time
	*/
}

class Group
{
	int m_x{};
	int m_y{};

public:
	constexpr Group(int x,int y)
		:m_x{x}
		,m_y{y}
	{ }

	constexpr int greater() const
	{
		return (m_x > m_y ? m_x : m_y);
	}

	constexpr void reset() //constexpr but non const
	{
		m_x = m_y = 0; //non const member functions can change members
	}

	constexpr const int& getX() const //const int is preferred over const int& bc int is a fundemental type  /btw a pointer version would look like this constexpr const int* getX() const
	{
		return m_x;
	}
};

constexpr Group zero()
{
	Group g{ 1,2 };
	g.reset();
	return g;
}

int main()
{
	std::cout << greater(5, 6) << '\n'; // greater(5,6) may be evaluated in compile or run time 

	constexpr int x{ greater(5,6) }; // greater(5,6) must be evaluated in compile time
	std::cout << x << '\n';


	constexpr Pair p{ 5,6 };  
	/*
	these inputs are constexpr values / now we made it constexpr bc aggregate implicitly supports constexpr we can do this without issue 
	/now after changing Pair to a class we got a compile error withc constexpr Pair p{5,6}, to fix that is pretty easy we just make our constructor
	constexpr this way the initialization can be evaluated at compile time
	*/

	std::cout << p.greater() << '\n'; 
	/*
	p.greater() evaluates at runtime /even after changing the member function to constexpr still runs at run time bc p is not a constexpr /aftter changing p to constexpr
	now it finally may evaluate either in compile or run time
	*/
#if 0
	constexpr int g{ p.greater() }; //compile error: greater() not not constexpr the way we solve this is making the member function constexpr
#endif
#if 0
	constexpr int g{ p.greater() }; //compile error: even tho we changed the member function to constexpr p itself isnt constexpr 
#endif
	constexpr int g{ p.greater() }; // ok finally works after making the member function and the object itself constepxr /and also works with class after making the constructor constexpr

	/*
	The reason why the initiali initialization had a compile error when we switched to class from struct was the fact that we had the constexpr keyword before it 
	which requires a literal type (literal types are type which are possible to create in an constant expression) which Pair wasnt before changing the constructor 
	to constexpr making it possible to evaluate in compile time. (btw a literal is ( different from literal type) a constexpr value inserted in the source code)
	Here are some literal types:
	-Scalar Types (those holding single value, such as fundamental types and pointers)
	-reference types
	-most aggregates 
	-classes that have constexpr constructor
	(btw implicitly defined constructors may be constexpr if possible but explicitly defaulted constructors must be explicitly defined as constexpr)
	*/

	constexpr int i{ init() }; // int i also needs to be constexpr bc its initialized with a constexpr function
	std::cout << i << '\n';

	Group g1{ 3,4 };
	g1.reset();  //okay to call  a non const member with a non const object 
	std::cout << g1.getX() << '\n'; // prints 0

	Group g2{ zero() }; // zero() will be evaluated at runtime
	g2.reset();         //okay to call  a non const member with a non const object 
	std::cout << g2.getX() << '\n'; // prints 0

	constexpr Group g3{ zero() }; // zero() will be evaluated at runtime / btw initialized with a non const object which is totally fine just confuses some people sometimes
#if 0
	g3.reset();        //compile error if calling  a non const member with a const object /.greater() would have worked and evaluated at compile time bc its a const member function
#endif
	std::cout << g3.getX() << '\n'; // prints 0 bc .getX() is a const fucntion
	return 0;
}
