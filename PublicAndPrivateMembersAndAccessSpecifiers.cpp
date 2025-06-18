#include <iostream>
#include <string>
#include <string_view>

// In this lesson we cover public and private member and the access specifiers 


struct Date
{
	//struct members are all puplic by default 
	int day{};             //public by default
	int month{};           //public by default
	int year{};            //public by default

	void printDate() const //public by default
	{
		//public member can be accessed in member function of the class type
		std::cout << day << "/" << month << "/" << year;
	}
};

//now lets see the difference by using a class instead of struct 
class Datum 
{
	//class member are all private by default 
	int m_day{};         //private by default
	int m_month{};       //private by default
	int m_year{};        //private by default
	/*
	Btw the reason why we use m_prefix for private data members is first its easiert to distinguish to other local variables like when passed in a function
	making it clear that a data member is being modified and it avoids naming collisions to other local variables especially in fucntions where data members stay even after 
	the function unlike passed arguments.
	This naming convention is mostly used with classes bc they tend to have member functions but you can also apply it to structs
	*/
	void printDatum() const //private by default
	{
		//private members can be accessed in member functions so this still works
		std::cout << m_day << "/" << m_month << "/" << m_year;
	}
	//no more an aggregate bc it has private members so also no aggregat initialization for that class (if either static or private is included you lose aggregate status)
};



class Dato
{
	//any member defined here would be private by default so no need for private: specifier but some still put it there just to make it clear that the following members are private


public:
	//any member defined from here on out is gonna be public bc of the public: specifier
	void printDato() const
	{
		//public member can access private members /dont forget for functions the order doesnt matter so its fine to access them before they are defined 
		std::cout << m_day << "/" << m_month << "/" << m_year;
	}

private:
	//any member defined from here on out is gonna be private bc of the private: specifier 
	int m_day{14};    // private
	int m_month{9};   // private
	int m_year{2005}; // private

	//there is also a protected: specifier but we will cover that in the future but its similar to private where it doesnt have public access but the difference being that it has Derived class access (which public also has)
};
//try to avoid using access specifiers with structs bc we want it to stay public by default so it stays being an aggregate with the ability to be aggregate initialized 
//and classes should generally make there member variables private or protected and their member functions public



class Person
{
private:  // private: redundant, its just here for clarification bc we gonna use both public and private in this class
	std::string m_name{};

public:
	void hugs(const Person& p) const
	{
		std::cout << m_name << " hugs " << p.m_name; 
		/*
		the access is on a class basis not object basis so bc of that this member function can access its own private members of the implicitly passed object 
		and also can access the private members of the explicitly passed object bc both are the same type 
		*/ 
	}

	void setName(std::string_view name) // we use that to change or give m_name a name otherwise we couldnt access it the convetional way bc m_name is private but can be accessed via member functions
	{
		m_name = name;
	}
};

class Point3d
{
private: // again private: not needed just for clarification here 
	int m_x{};
	int m_y{};
	int m_z{};

public:
	void setValues(int x,int y,int z)
	{
		m_x = x;
		m_y = y;
		m_z = z;
	}

	void printPoint() const
	{
		std::cout << "<" << m_x << ", " << m_y << ", " << m_z << ">";
	}

	bool isEqual(const Point3d& p2) const
	{
		return (m_x == p2.m_x) && (m_y == p2.m_y) && (m_z == p2.m_z);
	}
};



// main is part of the public
int main()
{
	Date today{ 18,6,2025 };

	today.day = 16;    //member data can be accessed by the public
	today.printDate(); //okay bc print() is a public member function
	std::cout << '\n';

#if 0
	//Datum is a class is its members data and functions are private by default
	Datum heute{ 18,6,2025 }; // compile error can no longer use aggregate initialization bc of private members / so we cant aggregate initialize our class with private members we show in a future lesson tho how to initialize it another way
	heute.m_day = 16;         // compile error private member cannot be accessed by the public
	heute.printDatum();       // compile error private member functions cannot be accessed by the public
#endif

	Dato past{};  // this is fine bc we dont aggregate initialize anything 
	past.printDato();  // this is fine bc printDato() is a public member and this is still fine even if this public member function accesses private member data 
	std::cout << '\n';

	Person joe{};
	joe.setName("Joe");
	Person chloe{};
	chloe.setName("Chloe");
	joe.hugs(chloe);


	/*
	Conclusion: Only difference between structs and classes is that structs are public by default and classes are private by default, so use struct when:
	1. simple collection of data with no need of restriction
	2. aggregate initialization is sufficient
	3. you have no class invariants or setup need or cleanup needs 

	so if keep your struct aggregate if thats not possible use class
	*/
	std::cout << '\n';

	Point3d point{};
	point.setValues(1, 2, 3);
	point.printPoint();
	std::cout << '\n';

	Point3d point2{};
	point2.setValues(4, 5, 6);

	std::cout << "point and point are " << (point.isEqual(point) ? "equal\n" : "not equal\n");
	std::cout << "point and point2 are " << (point.isEqual(point2) ? "equal\n" : "not equal\n");

	return 0;
}