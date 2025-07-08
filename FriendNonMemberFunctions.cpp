#include <iostream>




//On this chapter we learn about friendship and how magical friendship can be

/*
friendship works by declaring a certain function or class a friend with the friend keyword inside the class giving this function/class additional access to your private and 
protected members this way we can decide by a case to case basis who get access instead of making a member of a access function puplic and giving everyone access e.g:
*/
class Accumulator
{
	/*
	Conclusion of the lesson: Just like we said to prefer non member functions to member functions just in case the implementation changes the same holds true to friend 
	functions, prefer non friend functions to friend functions if possible in case the implementation changes will show with comments what needs to be changed when the 
	implementation changes
	*/
	int m_value{ 0 };  //Lets say we change this name so the implementation changed 
public:
	void  add(int value) //we need to modify this when the implementation changes like the name change of m_value
	{
		m_value += value;
	}

	friend void print(const Accumulator& a); // we declared void print() a friend now it has access to our private and protected members
};

void print(const Accumulator& a) // just a normal function thats why we need to pass a Accumulator object bc its not a member function so it doesnt have the "this" pointer 
{
	std::cout << a.m_value << '\n'; // can access .m_value just like that bc its a friend /we need to modify this when the implementation changes like the name change of m_value
}

//to circumvent those issues with the implementation changeds we could make void print() not a friend but add an access function that print can use
class Accumulator3
{

	int m_value{ 0 };  //Lets say we change this name so the implementation changed 
public:
	void  add(int value) //we only need modify this when the implementation changes like the name change of m_value
	{
		m_value += value;
	}

	int getValue() const
	{
		return m_value;
	}
};

void print3(const Accumulator3& a)  // regardless of implementation changes we dont need to change print3() anymore bc its not a friend anymore and uses a public access function
{
	std::cout << a.getValue() << '\n'; 
}

//You could also declare and define the friend function inside the class (but the friend function would still not be part of the class it would count a seperate normal function)
class Accumulator2
{
	int m_value{ 0 };
public:
	void  add(int value)
	{
		m_value += value;
	}

friend void print2(const Accumulator2& a) // just a normal function thats why we need to pass a Accumulator2 object bc its still not a member function even tho its defined in the class 
{
	std::cout << a.m_value << '\n'; // can access .m_value just like that bc its a friend
}
//this would be the same as above so print() still just a normal seperate function which is just a friend of the class 
};

// A small case why you should use friendship where a non member function can be a better choice than its member counterpart 
class Value
{
	int m_value{};

public:
	explicit Value(int v)
		:m_value{v}
	{ }

	bool isEqaulToMember(const Value& v2)
	{
		return m_value == v2.m_value;
	}

	friend bool isEqualToNonMember(const Value& v1, const Value& v2);
};

bool isEqualToNonMember(const Value& v1, const Value& v2)
{
	return v1.m_value == v2.m_value;
}


//ofc a function can be friends with multiple classes at the same time e.g:

class Humidity; // forward declaration of class Humidity 

class Temperature
{
	int m_temp{ 0 };
public:
	explicit Temperature(int temp)
		:m_temp{temp}
	{ }

	friend void printWeather(const Temperature& temp, const Humidity& hum); // we needed the forward declaration above for const Humidity& hum
};

class Humidity
{
	int m_hum{ 0 };
public:
	explicit Humidity(int hum)
		:m_hum{hum}
	{ }

	friend void printWeather(const Temperature& temp, const Humidity& hum);
};

void printWeather(const Temperature& temp, const Humidity& hum) // printWeather now the friend of class Temperature and class Humidity at the same time
{
	std::cout << "The Temperature is " << temp.m_temp << "'C and the Humdity is " << hum.m_hum << "%.\n";  // \u00B0 is unicode for ° we need to use that instead of just °
}

/*
You might think that a friendship might be a violation of the principle of data hiding bc , which  isnt rly the case bc access is granted by the class to another function with the
intent of it accessing the private members so you should see friends more as an extension of the class itself. But keep in mind bc of that unlike normal function that have no 
access to the implementation of the functions and are also uneffected when those change , friends are different bc in most cases these changes also affects them bc they have the
access to these implementation possibly startign a ripple effect of changes. So when using friends prefer using the public interface over direct access to circumvent these issues
of the implementation changing later and you needing to retest them later.
*/

int main()
{
	Accumulator ac{};
	ac.add(80);
	print(ac);

	Accumulator2 ac2{};
	ac2.add(81);
	print2(ac2);

	Value v1{ 2 };
	Value v2{ 7 };

	// depending on the case the latter (friend function) is a bit clearer
	std::cout << v1.isEqaulToMember(v2) << '\n';
	std::cout << isEqualToNonMember(v1, v2) << '\n';

	

	Temperature tem{ 20 };
	Humidity hum{ 7 };
	printWeather(tem, hum);

	//The code also doesnt need changes with the implementation change
	Accumulator3 ac3{};
	ac3.add(87);
	print3(ac3);

	/*
	Conclusion: Prefer to implement a function as a non friend when possible and reasonable(the same goes for non members and member functions and preferring non member).
	Ofc keep in mind sometimes its is preferred to use friendship if adding extra member functions adds additional complexity or clutter to the class interface.
	*/

	return 0;
}