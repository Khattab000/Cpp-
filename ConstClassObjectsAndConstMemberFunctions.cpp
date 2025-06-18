#include <iostream>

struct Date
{
	int day{};
	int month{};
	int year{};

	void incrementDay() // we cant make this const if we put the const keyword there we would get an compile error bc the fucntion modifies a member but they are allowed to 
	{                   
		++day;
	}
#if 0
	void printDate()
	{
		std::cout << day << "/" << month << "/" << year;
	}
#endif
	void printDate() const     //to make a member function const we just put const after the function prototype and ofc we need to make sure that its not modifying any member data
	{                          //const functions can modify non members tho or function parameters or call other non const functions  the const only applies to the member of the implict passed object
		std::cout << day << "/" << month << "/" << year;
		// so make your member function const if they dont modify member data so both const and non const objects cann call it 
	}
};

void doSmth(const Date& date)
{
	date.printDate(); //regardless if the passed object was a const or not this is a const bc the parameter is a reference to const treating the passed object as a const 
}


struct Something
{
	void print()
	{
		std::cout << "not const\n";
	}

	void print() const // we can overload functions with just const being the difference bc the const qualifier is part of the function signature 
	{
		std::cout << "const\n";
	}
};



int main()
{
	const Date today{ 18,6,2025 }; // class types can be made struct too 
#if 0
	today.day += 1;     // compile error bc of const
	today.incremntDay();// compile error bs of const
	// just like normal const variables the member data of a const object cant be modified

	//surprisingly so calling a printDate() also causes a compile error even tho its not modifying any data member so const object cant call non const member functions
	today.printDate(); //compile error bc of const even tho this doesnt even modify an data member 
#endif 
	// so if we wanted to call the member function printDate() we need to make it const and the way we do it is to put const after the function prototype e.g void printData() const
	today.printDate(); // this works now bc we made printDate() const
	std::cout << '\n';
	Date yesterday{ 17,6,2025 };
	yesterday.printDate(); // non const object can call const member functions too
	std::cout << '\n';
	
	
	doSmth(yesterday); 
	/*
	this works only bc printDate() is a const bc even tho yesterday isnt a const but bc doSmth() bound with yesterday with a reference to const the passed object became const
	and bc of that a const object can only call const functions even if the initial object wasnt a const
	*/ 


	std::cout << '\n';


	Something s1{};
	const Something s2{};
	s1.print(); // prints "not const" 
	s2.print(); // prints "const"
	//but this type of overloading is rarely used and is mostly used if the return type differs from const to non const


	return 0;
}