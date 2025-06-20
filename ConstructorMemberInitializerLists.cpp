#include <iostream>
#include <algorithm> // for std::max()
#include <optional>

//In this lesson we talk about constructor member initializer lists 
#if 0
class Foo
{
	int m_x{};
	int m_y{};

public:
	Foo(int x, int y)
		:m_x{ x }, m_y{ y } // that is our member intialization list its below the constructors signature and above the body with a : at th beginning and no ; at the end
	{
		std::cout << "Foo(" << x << ", " << y << ") constructed\n";
	}
	void print()
	{
		std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
	}

#if 0
	//C++ gives you a lot of freedom for the member initialization list formatting here are some alternatives e.g:
	Foo(int x, int y) : m_x{x}, m_y{y}
	{
	}

	//or which is also recommended:
	Foo(int x, int y):
		m_x{ x },
		m_y{ y }  // no need for , or ; after the last initialization
	{
	}

	//but there are many different more you are peretty much free to do what you want 
#endif 
};
#endif 


#if 0
/*
Aas we stated in an earlier lesson that class data members are initialized by the order that they are defined in NOT the the order of the 
member initialization list this can lead to some issues e.g:
*/
class Foo
{
	int m_x{};
	int m_y{};

public:
	Foo(int x, int y)
		:m_y{std::max(x,y)}  //issue on this line 
		,m_x{ m_y }
	{ 
	}// function body can be empty bc we only doing the initialization


	void print()
	{
		std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
	}

};
#endif

#if 0
class Foo
{
	int m_x{}; //default member initialization (will be ignored ) bc its intialized below through member initialization list
	int m_y{2};//default member initialization (will be used)
	int m_z;   //no initializer undefined behavior occurs bc it isnt and cant be initialized in main
public:
	Foo(int x)
		:m_x{ x } // member initialization list for m_x
	{
		std::cout << "Foo constructed\n";
	}
	void print()
	{
		std::cout << "Foo("<< m_x << ", " << m_y << ", " << m_z << ")\n";
	}
};
#endif


class Foo
{
	int m_x{ 0 };
	int m_y{ 1 };

public:
	Foo(int x, int y)
	{
		// a lot of times constructors have empty cosntructor bodies and only member initialization list bc they are only made to initialize members in these cases 

		m_x = x; // not recommended use member initialization list instead 
		m_y = y;
		/*
		Although you get the desired result in the below example its not recommended to use the body of the constructor to assign the values to the members 
		instead of initializing the member with member initialization list the reason being that this assignemnt wouldnt work where initialization is needed for example 
		for data members that are const or references.
		The object counts as initialized after the member initialization list is executed and after it executes the constructors body it counts as constructed
		*/
	}

	void print() const
	{
		std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
	}
};

#if 0
class Fraction
{
	/*
	the issue here is that we have the invariant of m_denominator not being allowed to be zero bc its a fraction we can try using the conditional operator ? : on the 
	initialization
	*/
	int m_nominator{};
	int m_denominator{};
public:
	Fraction(int x, int y)
		:m_nominator{ x }
		,m_denominator{ y } 
		/*
		we could do, m_denominator{y != 0.0 ? y : ? ? ? } but what should we do if its false what should the ? ? ? be so for that reason we dont do any validation in the
		member initialization list bc we dont have many options in here or a way to notify the user that there was an issue, so in this case we just initialize the member 
		with the value passed and then try to deal with the situation like we can use the constructor body that has more option like with assert and static_assert to tell that 
		the arguments passer are semantically incorrect but that doesnt handle runtime errors in production bc they are optimized out so instead we could throw an exception 
		(the best choice and we cover that in later chapters) or set an error state with a bool which is a bit complicated bc the constructor doesnt have a return value
		or halt the program all together with std::exit(1) (the 1 is the exit code and we usually just set it to 1).

		So the best thing to do when a constructor fails and cannot recover is throwing an exception.
		*/
	{
	}

};
#endif 
//in case you dont want to you excpetions there is another way with std::optional<> and friend functions (we cover friend functions in the future)
class Fraction
{
	int m_nominator{};
	int m_denominator{};

	Fraction(int x, int y)  // private constructor so cant be called by public
		:m_nominator{x}
		,m_denominator{y}
	{ }
public:
	friend std::optional<Fraction> createFraction(int numerator, int denominator); // forward declare this function and make it a friend so it has access to private members
};

std::optional<Fraction> createFraction(int numerator, int denominator) //publically available 
{
	if (denominator == 0)
	{
		return{};  // returns nothing (std::nullopt)
	}
	else
	{
		return Fraction{ numerator,denominator }; // returns a temporary initialized object of the type Fraction bc its allowed to do so bc its a friend function
	}
}

class Ball
{
	/*
	// we use std::string here instead of std::string_view bc we want our data members to be owners so that in case where a temporary object is passed to the member
	its fine if it goes out of scope  bc the value was copied to the data member
	*/
	std::string m_color{"none"}; 
	double m_radius{0.0};

public:
	Ball(std::string_view color, double radius)  //std::string_view is fine here bc just a parameter and bc m_color is still a std::string the contents will still be copied so its safe
		:m_color{ color }
		,m_radius{ radius }
	{
	}
	const std::string& getColor() const
	{
		return m_color;
	}

	double getRadius() const 
	{
		return m_radius;
	}
};

void print(const Ball& b)
{
	std::cout << "Ball(" << b.getColor() << ", " << b.getRadius() << ")\n";
}


int main()
{
#if 0
	Foo f{ 3,4 }; // prints 3, 4
	f.print();    // also prints 3, 4 bc now we added to the constructor that it actually initializes the memebers with the numbers wie passed 
#endif

#if 0
	Foo f{ 6,7 };
	f.print(); // this prints Foo(-858993460, 7)
	/*
	The issue here as we stated regardless what the member initialization list order is the members are always initialized by the order they are defined in in the class 
	so in the case of:
	Foo(int x, int y)
		:m_y{std::max(x,y)}
		,m_x{ m_y }
	{
	}

	m_x is initialized first with the value of m_y which doesnt have a value so it gets a garbage value and then m_y is initialized with the bigger value between the passed 
	x or y in this case its initialized with 7 so keep that always in mind and avoid that so try to always order the member initialization in the member intitialization 
	list after the order they are defined in the class and also avoid if possible to intialize members with another member just in case the member isnt initialized 
	yet or failed to be initialized bc if you avoid that it doesnt matter if you screwed up the order bc there are no dependencies here 
	*/
#endif

#if 0
	Foo foo{ 6 };
	foo.print(); //prints Foo(6, 2, -858993460) / m_z got undefined behavior bc it was left uninitialized
#endif 


	const Foo foo{ 6,7 }; //still works but as said not recommended use member list initialization instead 
	foo.print();

	//use auto for when you use std::optional<> so type can be deduced bc the type can be either the type insided std::optional<> or Null
	auto f1{ createFraction(1,6) }; //constructor not needed here bc we initialize it with an already temporary initialized object of the type Fraction
	if (f1)
	{
		std::cout << "Fraction created\n";
	}

	auto f2{ createFraction(3,0) }; // f2 should be std::nullopt so its empty 
	if (!f2)
	{
		std::cout << "Fraction invalid\n";
	}


	Ball blue{ "blue",10.0 };
	print(blue);

	Ball red{ "red",12.0 };
	print(red);




	return 0;
}