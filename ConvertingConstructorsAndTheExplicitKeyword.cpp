#include <iostream>
#include <string>
#include <string_view>

using namespace std::literals; //so we can put sv after a C-Style literal to make it a std::string_view literal

void printDouble(double d)
{
	std::cout << d << '\n';
}

class Foo
{
	int m_x{};
public:
	Foo(int x)  // the compiler uses this to do a user defined conversion of int to Foo bc this constructor als shows how its done. By default all constructors are converting constructors
		:m_x{ x }
	{}
	
	int getX() const
	{
		return m_x;
	}
};

void printFoo(Foo f)  //has a Foo parameter 
{
	std::cout << f.getX() << '\n';
}


class Employee
{
	std::string m_name{};

public:
	Employee(std::string_view name)
		:m_name{name}
	{}

	const std::string& getName() const
	{
		return m_name;
	}
};

void printEmployee(Employee e)
{
	std::cout << e.getName() << '\n';
}



class Dollars
{
	int m_dollars{};
public:
#if 0
	Dollars(int d)
		:m_dollars{d}
	{ }
#endif
	/*
	We now made the constructor explicit which tells the compiler to not used as a converting constructor meaning : No implicit conversion and no copy or copy 
	list initialization which are needed for implicit conversion
	*/
	explicit Dollars(int d) // explicit keyword before class type name
		:m_dollars{ d }
	{
	}


	int getDollars() const
	{
		return m_dollars;
	}
};

void printDollars(Dollars d)
{
	std::cout << "$" << d.getDollars() << '\n';
}

#if 0
class Goo
{
public:
	explicit Goo() // explicit just for the sake of the example
	{ }
	explicit Goo(int x)
	{ }
};

Goo getGoo()
{
	//Explicit Goo() cases
	return Goo{}; //ok
	return {};   // error: cant implicitly convert initializer list to Goo

	//Explicit Goo(int) cases
	return 5; // error: cant implicitly convert int to Goo
	return Goo{ 5 }; //ok
	return { 5 };  // cant implicitly convert initializer list to Foo 
}
#endif 

int main()
{
	printDouble(5); //even tho we supplied an int its fine bc of implicit type conversion , converting it to double 

	printFoo(5); // passing an int argurmant
	/*
	So you might be wondering why printFoo(5) works bc the conversion is between a fundemental type to a program defined type and is not part of the built in conversion rules,
	in this case the compiler looks if we have defined some function (in this case our constructor) that it can use to perform such conversion we call that user defined conversion
	*/
#if 0
	printEmployee("Jeff"); //we pass a C-Literal /compile error bc two user defined conversion needed
	/*
	This doesnt work bc only one user defined conversion is allowed and in this case we need two, first conversion is C-Literal to std::string_view and then the second 
	conersion is std::string_view to Employee so this will lead to a compile error. There are two ways to make it work so only one conversion happens e.g:
	*/
#endif
	printEmployee("Jeff"sv); //with sv "Jeff" is a std::string_view literal and bc of that only one conversion needed std::string_view to Employee / dont forget: using namespace std::literals
	printEmployee(Employee{ "Jeff" }); //this also works bc explicitly are intitialize a temporary Employee object and only one conversion is needed from C-Literal to std::string_view

#if 0 
	printDollars(5); //this works but it might be not what we intended
	/*
	Even tho printDollars(5) works fine we may have not intended for the conversion of our int to Dollar and in some cases this can lead to issues so is there a way to make sure
	a constructor only takes a certain type without the possibility of conversion ? Yes there is by using the  explict keyword
	*/
	printDollars(5); //this and the above call both lead to a compilation error bc we made the constructor explicit so no implicit conversion anymore
#endif
	//But a explicit constructor can still be used for direct and list initialization:
	Dollars d1(5);
	Dollars d2{ 5 };
	//so with that we can make the above printDollars(5) work by initializing a temporary Dollars object e.g:
	printDollars(Dollars{ 5 }); // this works now with list initialized temporary Dollars object
	printDollars(static_cast<Dollars>(5)); // this also works bc static_cast  returns an object that is direct initialized so the explicit constructor will be considered

	/*
	Conclusion: So lets talk about when and when not use the explicit keyword:
	-make any constructor that accpets a single arguments explicit by default but if an implicit converison between types is both semantically equivalent and performant 
	 like C-Style string to a constructo that has  a std::string_view type then you can consider making the constructor non explicit (btw if the constructor had a std::string
	 type argument then we would make it explicit to avoid a expensive construction if we passed a std::string_view)

	-dont make a constructor explicit if the constructor is a copr or move constructor as these dont perform conversion or constructors that have multiple arguments
	*/


	return 0;
}