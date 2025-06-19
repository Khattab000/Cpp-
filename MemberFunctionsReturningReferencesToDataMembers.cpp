#include <iostream>
#include <string>
#include <string_view>

//in this lesson we talk about return by reference in member functions


//example of a function returning by reference:
const std::string& firstAlphabetical(const std::string& a, const std::string& b)
{
	return(a < b) ? a : b;
}


//lets see an example of a member function return by reference: 
class Employee
{
	std::string m_name{};

public:
	void setName(std::string_view name)
	{
		m_name = name;
	}
#if 0
	std::string getName()
	{
		return m_name; // expensive copy will be passed by value 
	}
#endif

	const std::string& getName() const  // getter returns by const reference 
	{
		return m_name;  // returns a reference to m_name and bc m_name has the same lifetime as the object containing them so its safe to use  
	}
	/*
	also important a member function returning a reference to a data member should return the same type so to avoid unneccessary conversions so no std::string_view as a
	return type (but as a parameter is fine tho)
	*/
#if 0
	//You can also use auto as a return type to make sure no conversions occur bc auto deduces the return type e.g:
	const auto& getName() const
	{
		return m_name; 
	}
	//but this is not preferred bc it obscurs for the documentation what string is being returned, if its a std::string, std::string_view or C-Style string 
#endif 


};


//so far we covered returning data member by Lvalue reference which is safe to do but which isnt safe other then in certain cases at all is returning it Rvalue reference e.g:
Employee createEmployee(std::string_view name) // creates an Employee by value so the returned  value is an Rvalue
{
	Employee e{};
	e.setName(name);
	return e;  
}



//Do not return a non const reference to a data member bc even if the data member is private that reference can give direct acces to that member which we dont want to 
class Foo
{
private:
	int m_value{ 4 }; //private member 

public:
	int& value() // bad: returns a non const reference to a private data member 
	{
		return m_value;
	}
};




int main()
{
	std::string hello{ "hello" };
	std::string bye{ "bye" };
	std::cout << firstAlphabetical(hello, bye) << '\n';

	Employee joshua{};
	joshua.setName("Joshua");
	std::cout << joshua.getName() << '\n'; // returns joshua.m_name by reference 


	//Cases 1 okay: of returning reference to data member of an rvalue object which is safe to do so bc its only used in the full expression where its called bc it would be destroyed after:
	std::cout << createEmployee("Mike").getName() << '\n'; // prints "mike" but then the returned object will be destroyed after this expression

	//Case 2 bad: saving the returned reference  to member of rvalue class object for use later 
	const std::string& ref{ createEmployee("Frank").getName() };
	std::cout << ref << '\n';  // ref is now ad dangling reference so undefined behavior

	//Case 3 okay: copy referenced value to local variable for use later 
	std::string val{ createEmployee("Hans").getName() }; // makes copy of a reference member 
	std::cout << val << '\n'; // okay val is independent of reference member bc it just copied its value 
	
	//So try using the member value that was returned by reference immediatly to make sure no undefined behaviour occured or at least make sure it returns an lvalue
	

	Foo f{};   // f.m_value initiailized with default value 4
	f.value() = 5; // the equivalent of m_value = 5 which we shouldnt be able to do bc its a private member 
	std::cout << f.value() << '\n'; // prints 5

	/*
	so avoid returning data members by non const reference, and as an aside const member functions cant return data members by non const reference and also cant call
	any functions that could modify the data member or lead to it being modified
	*/
	return 0;
}