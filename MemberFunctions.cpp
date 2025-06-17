#include <iostream>
#include <string>
#include <string_view>


#if 0
struct Date
{
	int day{};
	int month{};
	int year{};
};

void printDate(const Date& d)
{
	std::cout << d.day << "/" << d.month << "/" << d.year;
}
#endif

//lets try to rewrite this but instead of the function and the struct being seperate we combine them making printData() a member function e.g:

struct Date
{
	int day{};
	int month{};
	int year{};

	void printData()  // no need to specify the argument parameter whatever variable calls the member function will be passed to printData() /so its implicitly passed 
	{
		std::cout << day << "/" << month << "/" << year;  //member are implicitly accessed through the object so no need for example fo today.day or today.month
	}

	//we can also overload member functions but the usual applies that they need to  be able to be differentiated (dont forget return type isnt important only arguments)
	void printData(std::string_view prefix) // so this has two arguments the implicitly passed one from the object calling it and an explicitly passed std::string:view variable
	{
		std::cout << prefix << day << "/" << month << "/" << year;
	}

};


struct Person
{
	std::string name{};
	int age{};
	void hug(const Person& person)  // in this case the function gets two arguments an implicitly passed Person that is using the member function and an explicitly passed Person
	{
		std::cout << name << " hugs " << person.name; //name is for the implicitly passed Person that called the function but we need to use person.name for the explicitly passed Person
	}
};



//normally if you want to call a function or a variable it needs to be defined already or at least declared otherwise you get an error, member functions and variables are exempted from that rule tho e.g:

struct Foo
{
	int z()
	{
		return m_data; // valid even tho m_data isnt defined yet
	}

	int x()
	{
		return y(); // also valid even tho y() isnt defined yet
	}

	int m_data{ y()}; // valid syntax, but may lead to undefined behavior if y() uses other members not yet initialized we will show an example below in struct Bad{};
	int y()   // the above all work but ofc it needs to be defined eventually even if its after the lines calling it 
	{
		return 5;
	}
};

/*
even tho we said that data member are exempt of that rule the rule still can bring undefined behavior bc data member variables are still initialized in order of declaration
so for that reason avoid using other member variables inside default member initialization
*/

struct Bad
{
	int m_bad1{ x_data }; //undefined behavior bc m_bad1 is initialized before x_data 
	int m_bad2{ fcn() };  //undefined behavior bc m_bad2 is initialized before x_data (accessed through fcn())

	int x_data{ 5 };
	int fcn()
	{
		return x_data;
	}
	//very bad and dangerous dont do that to much undefined behavior
};

/*
If your wondering why member functions and member variables are exempted of the rule of needing to be declared before use, its because the compiler has a neat trick that it 
applies to make it all work, lets take a slightly alternative struct Foo as an example e.g:

struct Foo
{
	int z()
	{
		return m_data;
	}

	int x()
	{
		return y(); 
	} 
	int y()   
	{
		return 5;
	}
	int m_data{};
};


basically the compiler goes through the struct does two things, first when he encounters a member function it implicitly forward declares it (and those forward declarations
of the member functions are at the and then transfers the definition basically outside of the struct so it will end up like this :
struct Foo
{
  int z(); // forward declaration of Foo::z()
  int x();
  int y();

  int m_data{}
}
int Foo::z()
{
  return m_data
}
int Foo::x()
{
  return y();
}
int Foo::y()
{
  return 5;
}


*/

#if 0 // deactivated for the same name Doo but not bc print() should work regardless bc the other print() is in a namespace Doo unless we use using namepace Doo 
//it is also possible to create a class type with no data members and only member functions for example and you can even instantiate objects of such type e.g:
struct Doo
{
	void print()
	{
		std::cout << "Hi!\n";
	}
};
#endif
//but this isnt rly recommended if the class type has no data members so using a class type is overkill, in this case use a namepace instead
namespace Doo
{
	void print()
	{
		std::cout << "Hi!\n";
	}
}


struct IntPair
{
	int first{};
	int second{};
	void printPair()
	{
		std::cout << "Pair(" << first << ", " << second << ")\n";
	}

	bool isEqual(IntPair p2)
	{
		return (first == p2.first) && (second == p2.second);
	}
};





int main()
{
	Date date{ 17,6,2025 };
#if 0
	printDate(date);
#endif
	date.day = 18;
	date.printData(); // we called the member function Date::printData() so dont forget () / we dont need to put anything in the () tho bc date is implicitly passed here 
	std::cout << '\n';
	Person joe{ "Joe",21 };
	Person chloe{ "Chloe",22 };

	joe.hug(chloe);  // joe is implicitly passed but chloe is explicitly passed bc the function requires another Person
	//this makes it clear what object is initiating the action and what object is support 
	std::cout << '\n';

	date.printData("Germany "); // called the overloaded function Date::printData(std::string_view)
	std::cout << '\n';
	
	// both structs and classes can use member functions bc structs wasnt able to in C and classes where added with C++
#if 0
	Doo d{};  //there is no data member variable in Doo only a member function print()
	d.print();
#endif 
	Doo::print(); // use namepace instead

	IntPair p1{ 4,5 };
	IntPair p2{ 8,0 };
	std::cout << "p1: ";
	p1.printPair();
	std::cout << "p2: ";
	p2.printPair();

	std::cout << "p1 and p1 " << (p1.isEqual(p1) ? "are equal\n" : "are not equal\n");
	std::cout << "p1 and p2 " << (p1.isEqual(p2) ? "are equal\n" : "are not equal\n");

	return 0;
}