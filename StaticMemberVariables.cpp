#include <iostream>
#include <string>
#include <string_view>
#include <utility> // for std::pair<T,U>



//On this lesson we learn about static member variables

int generateID()
{
	static int ID{ 0 }; // static local variable retains its value between calls
	return ++ID;
}

//static has two more uses with classes, one with member variables (we cover this in this lesson) and one for member function (we cover that in the next chapter)

//each object get their own value with the default value of 1 
struct Something
{
	int value{ 1 };
};


//each object gets the same value that they basically share and changes from one of the objects affect the others too bc its the same value
struct staticSomething
{
	static int s_value;  //declaration in the class body 
};
int staticSomething::s_value{ 1 }; 
/*
Initialization has to be outside of the class bc its a global variable and doesnt matter if you declared the static variable in private or public bc the static
variable is not subject to any access control (no static keyword needed here in the definition bc its on the declaration)
*/

/*
There is a difference tho between normal member variables and static member variables other than the fact that they are static, one huge difference is that they exist
independently so they already exist before any object is created unlike normal member variables. Knowing this static member variables are technically just global variables that 
live in the scope of a class so knowing this we can access the static member function directly with no object with staticSomething::s_value we show an example below in main.

Here some rules where to define the static member variable:

1. When the class defintion is in a cpp file then put the static defintion right below it. (never alone in a header file.

2. When the class defintion is in a header file put the static definition in the dedicated cpp file e.g foo.h (class defintion)   foo.cpp (static definition)
   (or you can make the static definition explicitly inline this way you can place it in the header file with the class definition)

3. When the template class definitiion is in a header file you put the static defintion right below it bc its a template so defintion like these are implicitly inline.
*/


/*
There are some exceptions or shorctuts tho for example if the static variable is a constant integral type(which included char and bool) or a const enum this way the static 
member variable can be completelty initialized inside e.g:
*/
class Whatever
{
	static const int s_value2{ 4 }; // a static const int can be defined and initialized directly so no explicit definition line outside of the class needed 
	// this shortcut is allowed bc these specific constants are compile time constants 

	static inline int s_value3{ 5 }; // preferred 
	/*
	A inline int can also be defined and intitialized directly with no explicit definition line needed / inline doesnt need to be constant and can be used for any types not only
	literal/integral types this is why this is the preferred method if initializing static member types. This is also useful when we put a the static definition inside the header.
	*/

	static constexpr double s_value4{ 8.2 };
	static constexpr std::string_view s_value5{ "Hello" }; //works even with types or classes that can be constexpr initialized
	//Constexpr also makes the member implicitly inline so you can also define and initialize it fully in the class

	/*
	So to conclude: prefer constexpr for static literals and integral types that you also want to be const and prefer inline for any other type and generally inline is the 
	preferred way to initialize static member variable. 
	(Both ways allow you to put the static member variable in a header file bc both eith implicitly or explictily make the member inline)
	*/
};

//Lets look at why you should use static member variables like for example a automatic id generator :
class Someone
{
	static inline int s_idGenerator{ 1 }; // generates id and get incremented in the constructor everytime called in the constructor
	int m_id{};  // each object has its own unique id

public:
	Someone()
		:m_id{s_idGenerator++}  // grab the next value from the id generator to intitialize the object and increment the static member variable
	{ }

	int getID() const
	{
		return m_id;
	}
	//giving each object unique ID can help when debugging as it can be used to  differentiate object that other have identical data especially with arrays of data which every object has instead of needing to copy it over and over again for every object
};

//static members are allowed to use auto or CTAD (type deduction) unlike non static members which  cant bc .... smth about ambiguity or non ituitive result
class Foo
{
#if 0
	auto m_x{ 5 }; // auto not allowed for non static members
	std::pair m_v{ 1,2.3 }; // CDAT not allowed for non static members / need deduction bc std::pair<T,U>
#endif

	static inline auto s_x{ 5 }; // auto allowed for static members 
	static inline std::pair s_v{ 1,2.3 }; // CDAT allowed for static members

};



int main()
{
	std::cout << generateID() << '\n';  // 1
	std::cout << generateID() << '\n';  // 2
	std::cout << generateID() << '\n';  // 3

	//Each get their own int value so first.value and second.value are not the same int and changes to the one doesnt change the other
	Something first{};
	Something second{};

	first.value = 2;

	std::cout << first.value << '\n';    // 2
	std::cout << second.value << '\n';   // 1   
	//only .value of first changed seconds .value stayed the same 

	staticSomething erster{};
	staticSomething zweiter{};
	erster.s_value = 2; //this changed the static member variable s_value to 2 which also affect zweiter.s_value bc its static
	std::cout << erster.s_value << '\n';  // 2
	std::cout << zweiter.s_value << '\n'; // 2
	//both .s_value changed

	staticSomething::s_value += 3; // for this to work it needs to be public tho
	std::cout << staticSomething::s_value << '\n'; // we can access the static member variable without using or ever creating an object bc its independent // needs to be public tho


	Someone one{};    // 1
	Someone two{};    // 2
	Someone three{};  // 3
	
	std::cout << one.getID() << " " << two.getID() << three.getID() << '\n'; // 1 2 3


	Foo foo{};

	return 0;
}